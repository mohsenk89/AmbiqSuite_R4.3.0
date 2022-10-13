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
//  This file can be modified by OEMs as specified in the license agreement
//
//                    Think Silicon S.A.
//                    http://www.think-silicon.com
//                    Patras Science Park
//                    Rion Achaias 26504
//                    Greece
// -----------------------------------------------------------------------------

#ifndef BAREMETAL
#include "FreeRTOS.h"
#include "portable.h"
#include "timers.h"
#include "semphr.h"

#include "nema_dc_hal.h"
#include "nema_dc.h"
#include "nema_event.h"

#include "am_bsp.h"
#include "am_util_delay.h"
#include "am_util_stdio.h"
#include "string.h"
#include "am_util_debug.h"
#include "am_devices_tma525.h"

#ifdef USE_TOUCH
static int touch_init();

#if (AM_BSP_GPIO_TOUCH_INT >= 32 && AM_BSP_GPIO_TOUCH_INT < 64)
    #define TOUCH_IRQ   GPIO0_203F_IRQn
#elif (AM_BSP_GPIO_TOUCH_INT >= 64 && AM_BSP_GPIO_TOUCH_INT < 96)
    #define TOUCH_IRQ   GPIO0_405F_IRQn
#endif    

#endif

#define CLAMPX( x )  ( (x) < 0 ? 0 : (x) >= maxx ? maxx : (x) );
#define CLAMPY( y )  ( (y) < 0 ? 0 : (y) >= maxy ? maxy : (y) );

#define MAX_EVENTS 10

#define FB_GPU  0
#define FB_DC   1
#define FB_FREE 2

#define NUM_LAYERS 1U

static uintptr_t triple_fbs[NUM_LAYERS][3];

uintptr_t
nema_init_triple_fb(int layer, uintptr_t fb0_phys, uintptr_t fb1_phys, uintptr_t fb2_phys)
{
    //actually doing always 2 framebuffers
    //fb2_phys is ignored

    triple_fbs[layer][FB_GPU]  = fb0_phys;
    triple_fbs[layer][FB_DC]   = fb1_phys;
    // triple_fbs[layer][FB_FREE] = fb2_phys;

    return triple_fbs[layer][FB_GPU];
}

uintptr_t
nema_swap_fb(int layer)
{
    if (layer < 0) {
        layer = 0;
    }

    {
        uintptr_t tmp = triple_fbs[layer][FB_DC];
        triple_fbs[layer][FB_DC] = triple_fbs[layer][FB_GPU];
        triple_fbs[layer][FB_GPU]  = tmp;

        // nemadc_wait_vsync();
        nemadc_set_layer_addr(layer, triple_fbs[layer][FB_DC]);
    }
    return triple_fbs[layer][FB_GPU];
}

static int timer1_is_initialized = 0;

static SemaphoreHandle_t xSemaphore = NULL;

int
nema_event_init(int flags, int mouse_init_x, int mouse_init_y, int mouse_max_x, int mouse_max_y)
{
    timer1_is_initialized = 0;

    xSemaphore = xSemaphoreCreateMutex();

    if ( xSemaphore == NULL ) {
        return -1;
    }
	
#ifdef USE_TOUCH
    touch_init();
#endif
    
    return 0;
}

static void semaphore_take(void) {
    (void)xSemaphoreTake(xSemaphore, portMAX_DELAY);
}

static void semaphore_give(void) {
    (void)xSemaphoreGive( xSemaphore );
}

#define TIMER_1 1
static TimerHandle_t timer1_handle;
static UBaseType_t timer1_reload = pdTRUE;

static volatile uint32_t timer1_passed = 0;

static TaskHandle_t xHandlingTask = (TaskHandle_t) 0;

static void
wake_task(void) {
    if ( xHandlingTask != (TaskHandle_t) 0 )
    {
        (void)xTaskNotify( xHandlingTask,
                            0,
                            eNoAction);
    }
}

static void
timer1_handler(TimerHandle_t pxTimer)
{
    //Not allowed, DBG_print() is also working with interrupt, not possible to have
    //uart higher priority compared to timer (no nesting)
    //DBG_print("@@ Timer1\n\r");

    semaphore_take();
    timer1_passed++;
    semaphore_give();

    wake_task();
}

int
nema_timer_create(void)
{
    //we have only one timer
    if ( timer1_is_initialized != 0) {
        return -1;
    }

    timer1_handle = xTimerCreate(
            "timer1", /* name */
            pdMS_TO_TICKS(100), /* period/time */
            timer1_reload, /* auto reload */
            (void*)1, /* timer ID */
            timer1_handler); /* callback */

    if (timer1_handle==NULL) {
        // am_util_stdio_printf("failed to create timer 1Sec\r\n");
        return -1;
    }

    timer1_is_initialized = 1;

/*     xTimerStart(timer1_handle, 0); */

    return TIMER_1;
}

void
nema_timer_destroy(int timer_id)
{
    //If timer isn't initialized, we've nothing to destroy
    if ( timer1_is_initialized == 0) {
        return;
    }

    //Only TIMER_1 is available
    if (timer_id != TIMER_1) {
        return;
    }

    //stop current timer for safety
    nema_timer_stop(timer_id);
    (void)xTimerDelete(timer1_handle, 0);

    timer1_is_initialized = 0;
}

static int
timer_set(int timer1_id, uint32_t timeout_milisecs, UBaseType_t reload)
{
    if (timer1_is_initialized == 0) {
        return -1;
    }

    //Only TIMER_1 is available
    if (timer1_id != TIMER_1) {
        return -1;
    }

    if ( timer1_reload == reload) {
        //just change the timer period
        if (xTimerChangePeriod(timer1_handle, pdMS_TO_TICKS(timeout_milisecs), 0) != pdPASS) {
            return -1;
        }

        // No need to call xTimerStart()
        // xTimerChangePeriod() will cause the timer to start.
        //
        // if (xTimerStart(timer1_handle, 0) != pdPASS) {
        //     return -1;
        // }
    } else {
        if ( xTimerIsTimerActive(timer1_handle) == pdTRUE ) {
            //Timer is running.
            //Can't change reload mode
            return -2;
        }

        //delete previous timer
        if ( xTimerDelete(timer1_handle, 0) == pdFALSE ) {
            return -3;
        }

        timer1_reload = reload;

        timer1_handle = xTimerCreate(
                "timer1", /* name */
                pdMS_TO_TICKS(timeout_milisecs), /* period/time */
                timer1_reload, /* auto reload */
                (void*)1, /* timer ID */
                timer1_handler); /* callback */

        if (xTimerStart(timer1_handle, 0) != pdPASS) {
            return -4;
        }
    }

    return timer1_id;
}

int
nema_timer_set_oneshot(int timer_id, uint32_t timeout_milisecs)
{
    return timer_set(timer_id, timeout_milisecs, pdFALSE);
}

int
nema_timer_set_periodic(int timer_id, uint32_t timeout_milisecs)
{
    return timer_set(timer_id, timeout_milisecs, pdTRUE);
}

void
nema_timer_start(int timer_id)
{
    if (timer1_is_initialized == 0) {
        return;
    }
    
    if (timer_id != TIMER_1) {
        return;
    }

    xTimerStart(timer1_handle, 10);
}

void
nema_timer_stop(int timer_id)
{
    if (timer1_is_initialized == 0) {
        return;
    }

    //Only TIMER_1 is available
    if (timer_id != TIMER_1) {
        return;
    }

    if ( xTimerIsTimerActive(timer1_handle) == pdTRUE) {
        (void)xTimerStop(timer1_handle, 0);
    }
}

void *g_pIOMHandle_touch;

bool i2c_read_flag = false;
bool touch_release = false;

nema_event_t g_s_last_event;
nema_event_t g_s_buf_touch;

am_hal_iom_config_t     g_sIomCfg_touch =
{
    // Set up IOM
    // Initialize the Device
    .eInterfaceMode       = AM_HAL_IOM_I2C_MODE,
    .ui32ClockFreq        = AM_HAL_IOM_400KHZ,
    .ui32NBTxnBufLength = 0,
    .pNBTxnBuf = NULL
};

#ifdef USE_TOUCH
#if (AM_BSP_GPIO_TOUCH_INT >= 32 && AM_BSP_GPIO_TOUCH_INT < 64)
    void
    am_gpio0_203f_isr(void)
    {
        uint32_t    ui32IntStatus;
       
        am_hal_gpio_interrupt_irq_status_get(TOUCH_IRQ, false, &ui32IntStatus);
        am_hal_gpio_interrupt_irq_clear(TOUCH_IRQ, ui32IntStatus);
        am_hal_gpio_interrupt_service(TOUCH_IRQ, ui32IntStatus);

        if (am_devices_tma525_get_point((uint16_t*)(&g_s_buf_touch.mouse_x), 
                                   (uint16_t*)(&g_s_buf_touch.mouse_y), 
                                   &touch_release) == AM_DEVICES_TMA525_STATUS_SUCCESS)
        {
            if (touch_release == true)
                i2c_read_flag = false;
            else
                i2c_read_flag = true;                    
        } else {
            am_util_stdio_printf("touch read error\n");
        }                               
    }
#elif (AM_BSP_GPIO_TOUCH_INT >= 64 && AM_BSP_GPIO_TOUCH_INT < 96)
    void
    am_gpio0_405f_isr(void)
    {
        uint32_t    ui32IntStatus;
       
        am_hal_gpio_interrupt_irq_status_get(TOUCH_IRQ, false, &ui32IntStatus);
        am_hal_gpio_interrupt_irq_clear(TOUCH_IRQ, ui32IntStatus);
        am_hal_gpio_interrupt_service(TOUCH_IRQ, ui32IntStatus);

        if (am_devices_tma525_get_point((uint16_t*)(&g_s_buf_touch.mouse_x), 
                                   (uint16_t*)(&g_s_buf_touch.mouse_y), 
                                   &touch_release) == AM_DEVICES_TMA525_STATUS_SUCCESS)
        {
            if (touch_release == true)
                i2c_read_flag = false;
            else
                i2c_read_flag = true;                    
        } else {
            am_util_stdio_printf("touch read error\n");
        }                               
    }
#endif
#endif

#ifdef USE_TOUCH
static int touch_init()
{              
    uint32_t ui32IntStatus;
    uint32_t ui32IntNum = AM_BSP_GPIO_TOUCH_INT;

    am_devices_tma525_init(AM_BSP_TP_IOM_MODULE, &g_sIomCfg_touch, &g_pIOMHandle_touch);
    am_hal_gpio_interrupt_irq_status_get(TOUCH_IRQ, false, &ui32IntStatus);
    am_hal_gpio_interrupt_irq_clear(TOUCH_IRQ, ui32IntStatus);
    am_hal_gpio_interrupt_control(AM_HAL_GPIO_INT_CHANNEL_0,
                                  AM_HAL_GPIO_INT_CTRL_INDV_ENABLE,
                                  (void *)&ui32IntNum);
    NVIC_SetPriority(TOUCH_IRQ, AM_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(TOUCH_IRQ);

    am_hal_interrupt_master_enable();  
    am_bsp_itm_printf_enable();

    return 0;
}
#endif

static void
wait_for_timer(void)
{
    BaseType_t xResult;

    xHandlingTask = xTaskGetCurrentTaskHandle();

    /* If a task is in the Blocked state to wait for a notification when the
       notification arrives then the task immediately exits the Blocked state
       and the notification does not remain pending. If a task was not waiting
       for a notification when a notification arrives then the notification
       will remain pending until the receiving task reads its notification
       value. */

    /* Wait to be notified of an interrupt. */
    xResult = xTaskNotifyWait( 0,    /* Don't clear bits on entry. */
                       0,                  /* Don't clear bits on exit. */
                       NULL,               /* No nitification value */
                       portMAX_DELAY );    /* Block indefinitely. */

    (void)xResult;
}

int
nema_event_wait(nema_event_t *event, int block_until_event)
{
#ifdef USE_TOUCH
    event->mouse_event         = MOUSE_EVENT_NONE;
    g_s_last_event.mouse_event = MOUSE_EVENT_NONE;

    int new_event = 0;
    
    if(i2c_read_flag == true)
	{
	    // touched
        i2c_read_flag = false;
        new_event = 1;

        event->mouse_state = MOUSE_STATE_LEFT_CLICKED;
        event->mouse_x     = g_s_buf_touch.mouse_x;
        event->mouse_y     = g_s_buf_touch.mouse_y;                
        event->mouse_dx    = event->mouse_x - g_s_last_event.mouse_x;
        event->mouse_dy    = event->mouse_y - g_s_last_event.mouse_y;

        // if previous state is not CLICKED, CLICK now
        if ( (g_s_last_event.mouse_state & MOUSE_STATE_LEFT_CLICKED) == 0 )
        {
            event->mouse_event         = MOUSE_EVENT_LEFT_CLICK;
            g_s_last_event.mouse_event = MOUSE_EVENT_LEFT_CLICK;

            // it's a click, not a drag/swipe
            event->mouse_dx = 0;
            event->mouse_dy = 0;
        }
        g_s_last_event.mouse_state = MOUSE_STATE_LEFT_CLICKED;
        g_s_last_event.mouse_x     = event->mouse_x;
        g_s_last_event.mouse_y     = event->mouse_y;
	}
    else if (touch_release)
    {
        // released
        if ( (g_s_last_event.mouse_state & MOUSE_STATE_LEFT_CLICKED) != 0 )
        {
            event->mouse_event         = MOUSE_EVENT_LEFT_RELEASE;
            g_s_last_event.mouse_event = MOUSE_EVENT_LEFT_RELEASE;
            new_event = 1;
        }

        event->mouse_state = MOUSE_STATE_NONE;
        g_s_last_event.mouse_state = MOUSE_STATE_NONE;
        touch_release = false;
    }
    
    if ( timer1_passed > 0 ) {
        event->timer_id          = TIMER_1;
        event->timer_expirations = timer1_passed;
        timer1_passed = 0;
        new_event = 1;
    }

    return new_event;
#else
	int pending_events = 0;

    //Init event fields (to be updated later)
    event->mouse_event       = (int)MOUSE_EVENT_NONE;
    event->mouse_state       = (int)MOUSE_STATE_NONE;
    // event->mouse_dx          = 0;
    // event->mouse_dy          = 0;
    // event->mouse_x           = 0;
    // event->mouse_y           = 0;
    event->kb_event          = (int)KB_EVENT_NONE;
    // event->kb_key            = 0;
    event->timer_id          = 0;
    event->timer_expirations = 0;

    do {
        if ( timer1_passed != 0U ) {
            semaphore_take();
            uint32_t tmp_timer_passed = timer1_passed;
            timer1_passed = 0;
            semaphore_give();

            event->timer_id          = TIMER_1;
            event->timer_expirations = tmp_timer_passed;
            ++pending_events;
        }
        else {
            if ( block_until_event != 0 ) {
                wait_for_timer();
            }
        }
    } while ( (block_until_event != 0) && (pending_events <= 0) );

    if (pending_events > 0) {
        return 1;
    }
#endif
}

#endif // BAREMETAL
