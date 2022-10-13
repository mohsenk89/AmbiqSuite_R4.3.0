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

#ifndef NEMA_SYS_DEFS_H__
#define NEMA_SYS_DEFS_H__

//Start of User Definitions
//-------------------------

#define DONT_SUPPORT_NEMATS
//#define NEMA_MULTI_PROCESS
//#define NEMA_MULTI_THREAD

//use multiple memory pools (implemented in nema_hal.c)
//#define NEMA_MULTI_MEM_POOLS

//if NEMA_MULTI_MEM_POOLS is defined, use NEMA_MULTI_MEM_POOLS_CNT pools
//must be equal or less than 4
#ifndef NEMA_MULTI_MEM_POOLS_CNT
#define NEMA_MULTI_MEM_POOLS_CNT	1
#endif

#define NEMA_MEM_POOL_CL     0
#define NEMA_MEM_POOL_FB 	 0
#define NEMA_MEM_POOL_ASSETS 0


//End of User Definitions
//-------------------------

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "am_hal_status.h"

#if defined(NEMA_MULTI_PROCESS) || defined(NEMA_MULTI_THREAD)

#endif

#ifdef NEMA_MULTI_THREAD

	#ifdef __STDC_NO_THREADS__
	#define TLS_VAR __thread
	#else
	// https://en.cppreference.com/w/c/thread
	// If the macro constant __STDC_NO_THREADS__(C11) is defined by the
	// compiler, the header <threads.h> and all of the names listed here
	// are not provided.
	// YE: Some compilers implementing C11 don't define __STDC_NO_THREADS__
	// but still don't provide <threads.h>
	#include <threads.h>
	#define TLS_VAR thread_local
	#endif

#else
#define TLS_VAR
#endif

// turn off printf, or map to am_util_stdio_printf
#define printf(...)

//*****************************************************************************
//
//! @brief nemadc_wait_te in blocking mode until NemaDC finished
//!
//!
//! @return None.
//
//*****************************************************************************
void nemadc_wait_te(void);

//*****************************************************************************
//
//! @brief nemadc_get_vsync
//!
//!
//! @return 32-bit am_hal_status_e status
//! @return AM_HAL_STATUS_IN_USE means NemaDC is still in processing
//! @return AM_HAL_STATUS_SUCCESS means NemaDC is complete all operation
//
//*****************************************************************************
am_hal_status_e nemadc_get_vsync(void);

//*****************************************************************************
//
//! @brief nemadc_get_te
//!
//!
//! @return 32-bit am_hal_status_e status
//! @return AM_HAL_STATUS_IN_USE means TE is not arrived
//! @return AM_HAL_STATUS_SUCCESS means TE is arrived
//
//*****************************************************************************
am_hal_status_e nemadc_get_te(void);

//*****************************************************************************
//
//! @brief nema_get_cl_status
//!
//!
//! @return 32-bit am_hal_status_e status
//! @return AM_HAL_STATUS_IN_USE means GPU still busy in processing
//! @return AM_HAL_STATUS_SUCCESS means GPU is complete all operation
//
//*****************************************************************************
am_hal_status_e nema_get_cl_status (int32_t cl_id);

//*****************************************************************************
//
//! @brief Suppress warning message for MDKv5.27 and later 
//!
//!
//! @note #61-D: integer operation result is out of range
//! @note #1295-D: Deprecated declaration nema_rand - give arg types
//! @note #1295-D: Deprecated declaration nema_rand - give arg types
//! @note waiting ThinkSilicon release the new Nema SDK
//
//*****************************************************************************
#if defined(__CC_ARM)
#pragma diag_suppress 61
#pragma diag_suppress 1295
#pragma diag_suppress 1
#endif

#endif
