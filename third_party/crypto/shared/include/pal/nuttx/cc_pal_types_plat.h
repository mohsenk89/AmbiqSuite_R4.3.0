/*
 * Copyright (c) 2001-2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause OR Arm’s non-OSI source license
 */

#ifndef _CC_PAL_TYPES_PLAT_H
#define _CC_PAL_TYPES_PLAT_H

/*! @file
@brief This file contains basic platform-dependent type definitions.
*/

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uintptr_t       CCVirtAddr_t;
typedef uint32_t            CCBool_t;
typedef uint32_t            CCStatus;

#define CCError_t           CCStatus
#define CC_INFINITE         0xFFFFFFFF

#define CEXPORT_C
#define CIMPORT_C

/* Define macros for host to SeP endianess conversion (for host wrappers) */
#if defined(AM_PART_APOLLO4) || defined(AM_PART_APOLLO4B)
#define cpu_to_le16(x) x
#define le16_to_cpu(x) x
#define cpu_to_le32(x) x
#define le32_to_cpu(x) x
#else /* DX_PLAT_APOLLO4 */
#include <endian.h>
#include <byteswap.h>
#if __BYTE_ORDER == __BIG_ENDIAN
#define cpu_to_le16(x) bswap_16(x)
#define le16_to_cpu(x) bswap_16(x)
#define cpu_to_le32(x) bswap_32(x)
#define le32_to_cpu(x) bswap_32(x)
#else /*__LITTLE_ENDIAN*/
#define cpu_to_le16(x) x
#define le16_to_cpu(x) x
#define cpu_to_le32(x) x
#define le32_to_cpu(x) x
#endif /*__BYTE_ORDER*/
#endif /* DX_PLAT_APOLLO4 */

#endif /*_CC_PAL_TYPES_PLAT_H*/
