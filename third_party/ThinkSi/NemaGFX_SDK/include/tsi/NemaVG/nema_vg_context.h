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
 * @brief General fuctions
 *
 * Contains error codes, fill rule and quality defines.
 */

#ifndef __NEMA_VG_CONTEXT_H__
#define __NEMA_VG_CONTEXT_H__

#include "nema_graphics.h"
#include "nema_matrix3x3.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifndef NEMA_VG_HANDLE
#define NEMA_VG_HANDLE void*
#endif

#define NEMA_VG_PATH_HANDLE NEMA_VG_HANDLE
#define NEMA_VG_PAINT_HANDLE NEMA_VG_HANDLE
#define NEMA_VG_GRAD_HANDLE NEMA_VG_HANDLE

typedef float nema_vg_float_t;

#define NEMA_VG_ERR_NO_ERROR                (0x00000000U)  /**< No Error */
#define NEMA_VG_ERR_BAD_HANDLE              (0x00000001U)  /**< Bad handle */
#define NEMA_VG_ERR_BAD_BUFFER              (0x00000002U)  /**< Bad buffer */
#define NEMA_VG_ERR_INVALID_FILL_RULE       (0x00000004U)  /**< Invalid fill rule*/
#define NEMA_VG_ERR_INVALID_PAINT_TYPE      (0x00000008U)  /**< Invalid paint type*/
#define NEMA_VG_ERR_INVALID_VERTEX_DATA     (0x00000010U)  /**< Invalid vertex data*/
#define NEMA_VG_ERR_NO_RADIAL_ENABLED       (0x00000020U)  /**< Radial not present in HW*/
#define NEMA_VG_ERR_NO_BOUND_CL             (0x00000040U)  /**< No bound CL*/
#define NEMA_VG_ERR_INVALID_ARGUMENTS       (0x00000080U)  /**< Invalid arguments*/
#define NEMA_VG_ERR_INVALID_ARC_DATA        (0x00000100U)  /**< reserved */
#define NEMA_VG_ERR_CL_FULL                 (0x00000200U)  /**< reserved */
#define NEMA_VG_ERR_DRAW_OUT_OF_BOUNDS      (0x00000400U)  /**< Path is out of the drawing area */
#define NEMA_VG_ERR_INVALID_MASKING_OBJ     (0x00000800U)  /**< Masking object was not set */
#define NEMA_VG_ERR_INVALID_MASKING_FORMAT  (0x00001000U)  /**< Invalid Masking object Format */
#define NEMA_VG_ERR_INVALID_LUT_IDX_FORMAT  (0x00002000U)  /**< Invalid LUT indices object Format */
#define NEMA_VG_ERR_COORDS_OUT_OF_RANGE     (0x00004000U)  /**< Path coordinates out of supported range */
#define NEMA_VG_ERR_EMPTY_TSVG              (0x00008000U)  /**< Tsvg has no geometries */

#define NEMA_VG_FILL_DRAW               (0x00U) /**< DEPRECATED Stroke fill rule */
#define NEMA_VG_STROKE                  (0x00U) /**< Stroke fill rule */
#define NEMA_VG_FILL_EVEN_ODD           (0x01U) /**< Evenodd fill rule */
#define NEMA_VG_FILL_NON_ZERO           (0x02U) /**< Non zero fill rule */

#define NEMA_VG_QUALITY_BETTER          (0x00U) /**< Better rendering quality */
#define NEMA_VG_QUALITY_FASTER          (0x01U) /**< Faster rendering quality */
#define NEMA_VG_QUALITY_NON_AA          (0x10U) /**< Rendering quality without AA*/


/** \brief Set the global transformation matrix
 *
 * \param m transformation matrix
 *
 * \return Error code
 */
uint32_t nema_vg_set_global_matrix(nema_matrix3x3_t m);


/** \brief Reset the global transformation matrix
 *
 * \return Error code
 */
uint32_t nema_vg_reset_global_matrix(void);

/** \brief Set Fill rule
 *
 * \param fill_rule fill rule
 *
 */
void nema_vg_set_fill_rule(uint8_t fill_rule);

/** \brief Enable/Disable Masking
 *
 * \param masking masking
 *
 */
void nema_vg_masking(uint8_t masking);

/** \brief Set Mask Object
 *
 * \param mask_obj mask_obj
 * \return Error code
 *
 */
uint32_t nema_vg_set_mask(nema_img_obj_t *mask_obj);

/** \brief Set Mask Translation
 *
 * \param x x
 * \param y y
 *
 */
void nema_vg_set_mask_translation(float x, float y);

/** \brief Set Quality
 *
 * \param quality quality
 *
 */
void nema_vg_set_quality(uint8_t quality);

/** \brief Set Blending mode for VG operations.
 *  Additional Blending Operations: only NEMA_BLOP_SRC_PREMULT is supported
 *
 * \param blend Blending mode
 * \see nema_blending_mode()
 *
 */
void nema_vg_set_blend(uint32_t blend);

/** \brief Get error code
 *
 * \return Error code
 */
uint32_t nema_vg_get_error(void);

#ifdef __cplusplus
}
#endif

#endif //__NEMA_VG_CONTEXT_H__
