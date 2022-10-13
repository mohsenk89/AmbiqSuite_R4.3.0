/*
 * Copyright (c) 2001-2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __DX_REG_BASE_HOST_H__
#define __DX_REG_BASE_HOST_H__

/* Identify platform: Apollo 4 */
#define DX_PLAT_APOLLO4

#define DX_BASE_CC         0x400C0000UL
//#define DX_BASE_CODE 0x50030000

#define DX_BASE_ENV_REGS   0x400C0000UL
// #define DX_BASE_ENV_NVM_LOW 0x5002A000
// #define DX_BASE_ENV_NVM_HI  0x5002B000
// #define DX_BASE_ENV_PERF_RAM 0x40009000

#define DX_BASE_HOST_RGF   0x0
#define DX_BASE_CRY_KERNEL 0x0
#define DX_BASE_RNG        0x0

#endif /*__DX_REG_BASE_HOST_H__*/
