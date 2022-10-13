/*******************************************************************************
 * Copyright (c) 2022 Think Silicon S.A.
 *
   Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this header file and/or associated documentation files to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the
 * Materials, and to permit persons to whom the Materials are furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Materials.
 *
 * MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS
 * NEMAGFX API. THE UNMODIFIED, NORMATIVE VERSIONS OF THINK-SILICON NEMAGFX
 * SPECIFICATIONS AND HEADER INFORMATION ARE LOCATED AT:
 *   https://think-silicon.com/products/software/nemagfx-api
 *
 *  The software is provided 'as is', without warranty of any kind, express or
 *  implied, including but not limited to the warranties of merchantability,
 *  fitness for a particular purpose and noninfringement. In no event shall
 *  Think Silicon S.A. be liable for any claim, damages or other liability, whether
 *  in an action of contract, tort or otherwise, arising from, out of or in
 *  connection with the software or the use or other dealings in the software.
 ******************************************************************************/

/**
 * @file
 * @brief Contains version number
 *
 */

#ifndef NEMA_VG_VERSION_H__
#define NEMA_VG_VERSION_H__

#ifdef __cplusplus
extern "C" {
#endif

#define NEMA_VG_MAJOR_VERSION    0x01U
#define NEMA_VG_MINOR_VERSION    0x00U
#define NEMA_VG_MINOR2_VERSION   0x00U
#define NEMA_VG_IMP_VERSION      0x00220300U

uint32_t nema_vg_get_api_version();
uint32_t nema_vg_get_imp_version();

// Returns Api version in format 0x00MMmmvv (M:major m:minor v:version if any)
uint32_t nema_vg_get_api_version(){
    return (NEMA_VG_MAJOR_VERSION << 16) + (NEMA_VG_MINOR_VERSION << 8) + (NEMA_VG_MINOR2_VERSION);
}

// Returns Imp version in format 0xIIIIIIII (I:imp)
uint32_t nema_vg_get_imp_version(){
    return  NEMA_VG_IMP_VERSION;
}

#ifdef __cplusplus
}
#endif

#endif //NEMA_VG_VERSION_H__
