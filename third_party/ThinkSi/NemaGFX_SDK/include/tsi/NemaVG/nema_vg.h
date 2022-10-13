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
 * @brief Basic vg operations
 *
 */

#ifndef __NEMA_VG_H__
#define __NEMA_VG_H__

#include "nema_core.h"
#include "nema_sys_defs.h"
#include "nema_vg_path.h"
#include "nema_vg_paint.h"
#include "nema_vg_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// -------------------------------------------------------------------------------
//                           SETUP
// -------------------------------------------------------------------------------

/** \brief Init NemaVG
 * \param width Framebuffer width
 * \param height Framebuffer height
 */
void nema_vg_init(int width, int height);

/** \brief Deinit NemaVG
 *
 *
 */
void nema_vg_deinit();

// -------------------------------------------------------------------------------
//                           PATH DRAW
// -------------------------------------------------------------------------------

/** \brief Draw stencil and then paint it
 *
 * \param path_in Pointer to path
 * \param paint_in Pointer to paint

 * \return Error code
 *
 */
uint32_t nema_vg_draw_path(NEMA_VG_PATH_HANDLE path, NEMA_VG_PAINT_HANDLE paint);

/** \brief Draw a line shape
 *
 *  \param x1 Upper left x coordinate
 *  \param y1 Upper left y coordinate
 *  \param x2 The width
 *  \param y2 The height
 *  \param m 3x3 affine transformation matrix
 *  \param paint The paint to draw

 * \return Error code
 *
 */
uint32_t nema_vg_draw_line(float x1, float y1, float x2, float y2,
                            nema_matrix3x3_t m,
                            NEMA_VG_PAINT_HANDLE paint);

/** \brief Draw a rectangle shape
 *
 *  \param x Upper left x coordinate
 *  \param y Upper left y coordinate
 *  \param width The width
 *  \param height The height
 *  \param m 3x3 affine transformation matrix
 *  \param paint The paint to draw

 * \return Error code
 *
 */
uint32_t nema_vg_draw_rect(float x, float y, float width, float height,
                            nema_matrix3x3_t m,
                            NEMA_VG_PAINT_HANDLE paint);

/** \brief Draw a rounded rectangle shape
 *
 *  \param x Upper left x coordinate
 *  \param y Upper left y coordinate
 *  \param width The width
 *  \param height The height
 *  \param rx Horizontal cornel radius
 *  \param ry Vertical cornel radius
 *  \param m 3x3 affine transformation matrix
 *  \param paint The paint to draw

 * \return Error code
 *
 */
uint32_t nema_vg_draw_rounded_rect(float x, float y, float width, float height,
                                float rx, float ry,
                                nema_matrix3x3_t m,
                                NEMA_VG_PAINT_HANDLE paint);

/** \brief Draw a ellipse shape
 *
 *  \param cx The x position of the ellipse
 *  \param cy The y position of the ellipse
 *  \param rx Radius on the x axis
 *  \param ry Radius on the y axis
 *  \param m 3x3 affine transformation matrix
 *  \param paint The paint to draw

 * \return Error code
 *
 */
uint32_t nema_vg_draw_ellipse(float cx, float cy, float rx, float ry,
                            nema_matrix3x3_t m,
                            NEMA_VG_PAINT_HANDLE paint);

/** \brief Draw a circle shape
 *
 *  \param cx The x center of the circle
 *  \param cy The y center of the circle
 *  \param r Radius of the circle
 *  \param m 3x3 affine transformation matrix
 *  \param paint The paint to draw

 * \return Error code
 *
 */
uint32_t nema_vg_draw_circle(float cx, float cy, float r,
                            nema_matrix3x3_t m,
                            NEMA_VG_PAINT_HANDLE paint);


/** \brief Draw a filled ring with rounded caps shape. In case of a conical gradient paint type,
 * the conical gradient center will always be at the center of the ring(cx, cy).
 * The ring width can be set with the paint's stroke_width.
 *
 *  \param cx The center x coordinate of the ring
 *  \param cy The center y coordinate of the ring
 *  \param ring_radius The radius of the ring
 *  \param angle_start The angle in degrees of the ring
 *  \param angle_end The angle in degrees that ends this ring
 *  \param paint The paint to draw

 * \return Error code
 *
 */
uint32_t nema_vg_draw_ring(float cx, float cy, float ring_radius, float angle_start, float angle_end,
                                            NEMA_VG_PAINT_HANDLE paint);


#ifdef __cplusplus
}
#endif

#endif //__NEMA_VG_H__
