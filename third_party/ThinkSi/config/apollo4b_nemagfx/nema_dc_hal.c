// -----------------------------------------------------------------------------
// Copyright (c) 2019 Think Silicon S.A.
// Think Silicon S.A. Confidential Proprietary
// -----------------------------------------------------------------------------
//     All Rights reserved - Unpublished -rights reserved under
//         the Copyright laws of the European Union
//
//  This file includes the Confidential information of Think Silicon S.A.
//  The receiver of this Confidential Information shall not disclose
//  it to any third party and shall protect its confidentiality by
//  using the same degree of care, but not less than a reasonable
//  degree of care, as the receiver uses to protect receiver's own
//  Confidential Information. The entire notice must be reproduced on all
//  authorised copies and copies may only be made to the extent permitted
//  by a licensing agreement from Think Silicon S.A..
//
//  The software is provided 'as is', without warranty of any kind, express or
//  implied, including but not limited to the warranties of merchantability,
//  fitness for a particular purpose and noninfringement. In no event shall
//  Think Silicon S.A. be liable for any claim, damages or other liability, whether
//  in an action of contract, tort or otherwise, arising from, out of or in
//  connection with the software or the use or other dealings in the software.
//
//
//                    Think Silicon S.A.
//                    http://www.think-silicon.com
//                    Patras Science Park
//                    Rion Achaias 26504
//                    Greece
// -----------------------------------------------------------------------------

#include "stdint.h"
#include "nema_dc_regs.h"
#include "nema_dc_hal.h"
#include "nema_dc_mipi.h"
#include "nema_ringbuffer.h"

#include "am_mcu_apollo.h"
#include "am_util_delay.h"

#ifdef BAREMETAL

#  ifndef WAIT_IRQ_POLL
#    define WAIT_IRQ_POLL              1
#  endif

#else  // BAREMETAL
#ifdef SYSTEM_VIEW
#  include "SEGGER_SYSVIEW_FreeRTOS.h"
#endif
#  include "FreeRTOS.h"
#  include "task.h"

#  ifndef WAIT_IRQ_POLL
#    define WAIT_IRQ_POLL               0
#  endif

#  ifndef WAIT_IRQ_BINARY_SEMAPHORE
#    define WAIT_IRQ_BINARY_SEMAPHORE   1
#  endif

#  if WAIT_IRQ_POLL == 1
     /* Nothing to declare */
#  elif WAIT_IRQ_BINARY_SEMAPHORE == 1
#    include "semphr.h"
     static SemaphoreHandle_t xSemaphore_vsync = NULL;
     static SemaphoreHandle_t xSemaphore_TE = NULL;
#  else
#     include "task.h"
      static TaskHandle_t xHandlingTask = 0;
#  endif

#endif // BAREMETAL

#ifndef NEMADC_BASEADDR
#include "apollo4b.h"
#define NEMADC_BASEADDR       DC_BASE
#endif

// IRQ number
#ifndef NEMADC_IRQ
#define NEMADC_IRQ           ((IRQn_Type)29U)
#endif

// IRQ handler
//#define prvVsyncInterruptHandler        am_dc_isr

static uintptr_t nemadc_regs = 0;

volatile int irq_count = 0;

void (*nema_dc_interrupt_callback)(void) = NULL;


static void prvVsyncInterruptHandler( void *pvUnused )
{
    ++irq_count;

    /* Clear the interrupt */
    nemadc_reg_write(NEMADC_REG_INTERRUPT, nemadc_reg_read(NEMADC_REG_INTERRUPT) & (~(1U << 4)));
#ifndef BAREMETAL
    #ifdef SYSTEM_VIEW
        traceISR_ENTER();
    #endif

    #if WAIT_IRQ_BINARY_SEMAPHORE == 1
        xSemaphoreGiveFromISR(xSemaphore_vsync, NULL);
    #else
        #if 1
        if ( xHandlingTask )
        {
            xTaskNotifyFromISR( xHandlingTask,
                                0,
                                eNoAction,
                                NULL );
        }
        /* If xHigherPriorityTaskWoken is now set to pdTRUE then a context switch
        should be performed to ensure the interrupt returns directly to the highest
        priority task.  The macro used for this purpose is dependent on the port in
        use and may be called portEND_SWITCHING_ISR(). */
        // portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
        #else
        if (xHandlingTask)
        {
          xTaskResumeFromISR( xHandlingTask );
          xHandlingTask = 0;
        }
        #endif
    #endif

    #ifdef SYSTEM_VIEW
        traceISR_EXIT();
    #endif
#endif

    if (nema_dc_interrupt_callback) nema_dc_interrupt_callback();
}

static void prvTEInterruptHandler( void *pvUnused )
{
    ++irq_count;

    /* Clear the interrupt */
    nemadc_reg_write(NEMADC_REG_INTERRUPT, nemadc_reg_read(NEMADC_REG_INTERRUPT) & (~(1U << 3)));
#ifndef BAREMETAL
    #ifdef SYSTEM_VIEW
        traceISR_ENTER();
    #endif

    #if WAIT_IRQ_BINARY_SEMAPHORE == 1
        xSemaphoreGiveFromISR(xSemaphore_TE, NULL);
    #else
        #if 1
            if ( xHandlingTask )
            {
                xTaskNotifyFromISR( xHandlingTask,
                                    0,
                                    eNoAction,
                                    NULL );
            }

            /* If xHigherPriorityTaskWoken is now set to pdTRUE then a context switch
            should be performed to ensure the interrupt returns directly to the highest
            priority task.  The macro used for this purpose is dependent on the port in
            use and may be called portEND_SWITCHING_ISR(). */
            // portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
        #else
            if (xHandlingTask)   
            {
              xTaskResumeFromISR( xHandlingTask );
              xHandlingTask = 0;
            }
        #endif
    #endif

    #ifdef SYSTEM_VIEW
        traceISR_EXIT();
    #endif
#endif

    if (nema_dc_interrupt_callback) nema_dc_interrupt_callback();
}

void am_disp_isr()
{
  if ((nemadc_reg_read(NEMADC_REG_INTERRUPT) & (1 << 4)) != 0)
  {
    prvVsyncInterruptHandler(NULL);
  }
  if  ((nemadc_reg_read(NEMADC_REG_INTERRUPT) & (1 << 3)) != 0)
  {
    prvTEInterruptHandler(NULL);
  }
}


int32_t nemadc_sys_init(void) {
    // xil_printf( "nemadc_sys_init()\r\n" );
    nemadc_regs = (uintptr_t)NEMADC_BASEADDR;


    /* Clear the interrupt */
    nemadc_reg_write(NEMADC_REG_INTERRUPT, 0);

    /* Install Interrupt Handler */
    NVIC_SetPriority(NEMADC_IRQ, AM_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(NEMADC_IRQ);

#if WAIT_IRQ_BINARY_SEMAPHORE
    if (xSemaphore_vsync == NULL)
    {
        xSemaphore_vsync = xSemaphoreCreateBinary();
    }
    if (xSemaphore_TE == NULL)
    {
        xSemaphore_TE = xSemaphoreCreateBinary();
    }
#endif

    return 0;
}

//@function nemadc_wait_vsync
//@brief Wait for VSync interrupt
//@param void
//-----------------------------------------------------------------------
void nemadc_wait_vsync(void)
{
#ifdef BAREMETAL
    /* Wait for the interrupt */
    #if WAIT_IRQ_POLL == 1
        uint32_t ui32usMaxDelay = 1000000; // 1 sec
        uint32_t ui32Status;
        //irq_handler sets NEMADC_REG_INTERRUPT to 0. Poll until this happens
        ui32Status = am_hal_delay_us_status_change(ui32usMaxDelay, (uint32_t)&DC->INTERRUPT, 1UL << 4, 0);
        if (ui32Status != AM_HAL_STATUS_SUCCESS)
        {
            return;
        }    
        //am_util_delay_ms(10);
    #else // WAIT_IRQ_POLL
        while (nemadc_reg_read(NEMADC_REG_INTERRUPT) != 0U)
        {
            AM_CRITICAL_BEGIN
            if (nemadc_reg_read(NEMADC_REG_INTERRUPT) != 0U )
            {
                am_hal_sysctrl_sleep(1);
            }
            AM_CRITICAL_END
        }
    #endif // WAIT_IRQ_POLL
#else /* BAREMETAL */
    #if WAIT_IRQ_BINARY_SEMAPHORE == 1
        xSemaphoreTake( xSemaphore_vsync, portMAX_DELAY );
    #else
        BaseType_t xResult;

        xHandlingTask = xTaskGetCurrentTaskHandle();

        /* If a task is in the Blocked state to wait for a notification when the
           notification arrives then the task immediately exits the Blocked state
           and the notification does not remain pending. If a task was not waiting
           for a notification when a notification arrives then the notification
           will remain pending until the receiving task reads its notification
           value. */

        /* Wait to be notified of an interrupt. */
        xResult = xTaskNotifyWait( pdFALSE,    /* Don't clear bits on entry. */
                           0,                  /* Don't clear bits on exit. */
                           NULL,               /* No nitification value */
                           portMAX_DELAY );    /* Block indefinitely. */

        (void)xResult;
    #endif // WAIT_IRQ_BINARY_SEMAPHORE    
#endif /* BAREMETAL */
    
    return;

    

    // xil_printf("irq_count after = %d\r\n", irq_count);
}

//@function nemadc_wait_te
//@brief Wait for TE interrupt
//@param void
//-----------------------------------------------------------------------
void nemadc_wait_te(void)
{
#ifdef BAREMETAL
    /* Wait for the interrupt */
    #if WAIT_IRQ_POLL == 1
        uint32_t ui32usMaxDelay = 100000;
        uint32_t ui32Status;
        //irq_handler sets NEMADC_REG_INTERRUPT to 0. Poll until this happens
        ui32Status = am_hal_delay_us_status_change(ui32usMaxDelay, (uint32_t)&DC->INTERRUPT, 1UL << 3, 0);
        if (ui32Status != AM_HAL_STATUS_SUCCESS)
        {
            return;
        }    
        
        //am_util_delay_ms(10);
    #else // WAIT_IRQ_POLL
            while (nemadc_reg_read(NEMADC_REG_INTERRUPT) != 0U)
            {
                AM_CRITICAL_BEGIN
                if (nemadc_reg_read(NEMADC_REG_INTERRUPT) != 0U )
                {
                    am_hal_sysctrl_sleep(1);
                }
                AM_CRITICAL_END
            }
    #endif // WAIT_IRQ_POLL
#else /* BAREMETAL */
    #if WAIT_IRQ_BINARY_SEMAPHORE == 1
        xSemaphoreTake( xSemaphore_TE, portMAX_DELAY );
    #else
        BaseType_t xResult;

        xHandlingTask = xTaskGetCurrentTaskHandle();

        /* If a task is in the Blocked state to wait for a notification when the
           notification arrives then the task immediately exits the Blocked state
           and the notification does not remain pending. If a task was not waiting
           for a notification when a notification arrives then the notification
           will remain pending until the receiving task reads its notification
           value. */

        /* Wait to be notified of an interrupt. */
        xResult = xTaskNotifyWait( pdFALSE,    /* Don't clear bits on entry. */
                           0,                  /* Don't clear bits on exit. */
                           NULL,               /* No nitification value */
                           portMAX_DELAY );    /* Block indefinitely. */

        (void)xResult;
    #endif // WAIT_IRQ_BINARY_SEMAPHORE    
#endif /* BAREMETAL */
    
    return;

    

    // xil_printf("irq_count after = %d\r\n", irq_count);
}

//@function nemadc_reg_read
//@brief Read NemaDC Hardware Register
//@param uint32_t desc:Register address
//@return uint32_t desc:Register Value
//-----------------------------------------------------------------------
uint32_t  nemadc_reg_read(uint32_t reg) {
    volatile uint32_t *ptr = (volatile uint32_t *)(nemadc_regs + reg);
    return *ptr;
}

//@function nemadc_reg_write
//@brief Write NemaDC Hardware Register
//@param uint32_t desc:Register address
//@param uint32_t desc:Register value
//-----------------------------------------------------------------------
void nemadc_reg_write(uint32_t reg, uint32_t value) {
    //am_util_stdio_printf("%08x = %08x\n", reg, value);
    volatile uint32_t *ptr = (volatile uint32_t *)(nemadc_regs + reg);
    *ptr = value;
}

am_hal_status_e 
nemadc_get_vsync(void)
{
    if (nemadc_reg_read(NEMADC_REG_INTERRUPT) & 1<<4)
    {
        return AM_HAL_STATUS_IN_USE;
    }
    else
    {
        return AM_HAL_STATUS_SUCCESS;
    }
}

am_hal_status_e 
nemadc_get_te(void)
{
    if (nemadc_reg_read(NEMADC_REG_INTERRUPT) & 1<<3)
    {
        return AM_HAL_STATUS_IN_USE;
    }
    else
    {
        return AM_HAL_STATUS_SUCCESS;
    }
}

