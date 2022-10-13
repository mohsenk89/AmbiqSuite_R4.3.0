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
 * @brief Vector font rendering
 *
 * This file includes the necessary structs and functions that are used for rendering text (strings and single characters),
 * using vector fonts. The accompanying vector font converter utility, converts truetype fonts (ttf files) to instances
 * of the structs defined here. A use case of this module is included in the respective examples (examples/NemaVG/render_vg_font).
 */

#ifndef NEMA_VG_FONT_H_
#define NEMA_VG_FONT_H_

#include "nema_matrix3x3.h"
#include "nema_vg.h"
#include "nema_vg_context.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NEMA_VG_ALIGNX_LEFT    (0x00U) /**< Align horizontally to the left */
#define NEMA_VG_ALIGNX_RIGHT   (0x01U) /**< Align horizontally to the right */
#define NEMA_VG_ALIGNX_CENTER  (0x02U) /**< Align horizontally centered */
#define NEMA_VG_ALIGNX_JUSTIFY (0x03U) /**< Justify horizontally */
#define NEMA_VG_ALIGNX_MASK    (0x03U) /**< Horizontal alignment mask */
#define NEMA_VG_ALIGNY_TOP     (0x00U) /**< Align vertically to the top */
#define NEMA_VG_ALIGNY_BOTTOM  (0x04U) /**< Align vertically to the bottom */
#define NEMA_VG_ALIGNY_CENTER  (0x08U) /**< Align vertically centered */
#define NEMA_VG_ALIGNY_JUSTIFY (0x0cU) /**< Justify vertically */
#define NEMA_VG_ALIGNY_MASK    (0x0cU) /**< Vertical alignment mask */
#define NEMA_VG_TEXT_WRAP      (0x10U) /**< Use text wrapping */

/** NemaVG Kerning pair information data struct */
typedef struct {
    uint32_t   left;  /**< Neighbor character to the left of the current one (Unicode value) */
    float   x_offset; /**< Kerning offset value (horizontally) */
} nema_vg_kern_pair_t;

/** NemaVG data struct of a glyph in vector format*/
typedef struct {
    uint32_t  data_offset;    /**< Offset value for the data of the glyph in the respective data array */
    size_t    data_length;    /**< Length of the data in the respective data array */
    uint32_t  segment_offset; /**< Offset value for the segments of the glyph in the respective segment array */
    size_t    segment_length; /**< Length of the segments in the respective segment array */
    float     xAdvance;       /**< Advance width*/
    uint32_t  kern_offset;    /**< Kerning offset  of the glyph in the respective kerning array */
    uint8_t   kern_length;    /**< Length of the kerning information of the glyph */
    int16_t   bbox_xmin;      /**< Minimum x of the glyph's bounding box */
    int16_t   bbox_ymin;      /**< Minimum y of the glyph's bounding box */
    int16_t   bbox_xmax;      /**< Maximum x of the glyph's bounding box */
    int16_t   bbox_ymax;      /**< Maximum y of the glyph's bounding box */
} nema_vg_glyph_t;

/** NemaVG vector font range data struct */
typedef struct {
    uint32_t first;                /**< Unicode value of the first value of the range */
    uint32_t last;                 /**< Unicode value of the last value of the range */
    const nema_vg_glyph_t *glyphs; /**< Pointer to the array of glyphs */
} nema_vg_font_range_t;

/** NemaVG vector font data struct*/
typedef struct {
    const nema_vg_font_range_t *ranges;          /**< Pointer to the array of ranges */
    const nema_vg_float_t      *data;            /**< Pointer to the data of the vector font */
    const size_t                data_length;     /**< Length of the vector font data*/
    const uint8_t              *segment;         /**< Pointer to the segments of the vector font */
    const size_t                segment_length;  /**< Length of the vector font segments */
    float                       size;            /**< Default font size (height) */
    float                       xAdvance;        /**< Default advance width. If the space character is included in the ranges, then its advance width is set */
    float                       ascender;        /**< Vertical distance from the baseline to the highest point of the font */
    float                       descender;       /**< Vertical distance from the baseline to the lowest point of the font */
    const nema_vg_kern_pair_t  *kern_pairs;      /**< Pointer to the array of the font's kerning pairs */
} nema_vg_font_t;

/** \brief Bind the font to use in future nema_vg_print() calls
 *
 * \param font Pointer to the vector font
 *
 */
void nema_vg_bind_font(nema_vg_font_t *font);

/** \brief Sets the size of the bound font. Future nema_vg_print() calls will print using the last set size.
 *
 * \param font Pointer to the vector font
 *
 */
void nema_vg_set_font_size(float size);


/** \brief Get the bounding box's width and height of a vector string.
 *
 * \param paint Pointer to the current paint object (contains the text color)
 * \param str Pointer to string
 * \param x X coordinate of text-area's top-left corner
 * \param y Y coordinate of text-area's top-left corner
 * \param w Max allowed width
 * \param h Max allowed height
 * \param align Alignment and wrapping mode
 * \param m Transformation matrix
 *
 */
void nema_vg_print(NEMA_VG_PAINT_HANDLE paint, const char *str, int x, int y, int w, int h, uint32_t align, nema_matrix3x3_t m);


/** \brief Get the bounding box's width and height of a vector string.
 *
 * \param str Pointer to string
 * \param w Pointer to variable where width should be written
 * \param h Pointer to variable where height should be written
 * \param max_w Max allowed width
 * \param size font size
 * \param wrap enable text wraping
 * \return Number of carriage returns
 *
 */
int  nema_vg_string_get_bbox(const char *str, int *w, int *h, int max_w, uint32_t wrap);


/** \brief Get the text ascender value in point units. Font size must be set pror to calling this function.
 *
 * \return Ascender pt
 *
 */
int nema_vg_get_ascender_pt();

#ifdef __cplusplus
}
#endif
#endif // NEMA_VG_FONT_H_
