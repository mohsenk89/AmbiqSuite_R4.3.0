//*****************************************************************************
//
// @file ng_draw.h
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2022, Ambiq Micro, Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision release_sdk_4_3_0-0ca7d78a2b of the AmbiqSuite Development Package.
//
//*****************************************************************************

/*******************************************************************************
 * Copyright (c) 2021 Think Silicon S.A.
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
 * NEMAGUI API.
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
 * @brief High level drawing functions for performing hierarchical drawing of tree nodes (along with their children)
 *
 */

#ifndef __GITEM_DRAW_H__
#define __GITEM_DRAW_H__
#include "ng_gitem.h"
#include "ng_tree.h"

/**
 * @brief Draws a specific tree node (its graphics item) in the framebuffer.
 *
 * @param node The tree node whose graphics item needs to be drawn
 * @param x_off Horizontal offset whithin the framebuffer (absolute coordinate)
 * @param y_off Vertical offset whithin the framebuffer (absolute coordinate)
 * @param x_min Minimum x coordinate (needed for clipping)
 * @param y_min Minimum y coordinate (needed for clipping)
 * @param x_max Maximum x coordinate (needed for clipping)
 * @param y_max Maximum y coordinate (needed for clipping)
 */
void ng_draw_tree_node (tree_node_t *node, int x_off, int y_off, int x_min, int y_min, int x_max, int y_max);

/**
 * @brief  Reccursive function, similar to ng_draw_tree_node but draws recursively every child tree node of the initial \a node.
 *
 * @param node The initial tree node whose graphics item needs to be drawn (usually a tree node that contains a screen)
 * @param x_off Horizontal offset whithin the framebuffer (absolute coordinate)
 * @param y_off Vertical offset whithin the framebuffer (absolute coordinate)
 * @param x_min Minimum x coordinate (needed for clipping)
 * @param y_min Minimum y coordinate (needed for clipping)
 * @param x_max Maximum x coordinate (needed for clipping)
 * @param y_max Maximum y coordinate (needed for clipping)
 */
void ng_draw_tree (tree_node_t *node, int x_off, int y_off, int x_min, int y_min, int x_max, int y_max);

/**
 * @brief Draws a tree node and its children nodes inside the bound framebuffer (used by the animations module)
 *
 * @param node The initial tree node whose graphics item needs to be drawn
 * @param x_off Horizontal offset whithin the framebuffer (absolute coordinate)
 * @param y_off Vertical offset whithin the framebuffer (absolute coordinate)
 * @param x_min Minimum x coordinate (needed for clipping)
 * @param y_min Minimum y coordinate (needed for clipping)
 * @param x_max Maximum x coordinate (needed for clipping)
 * @param y_max Maximum y coordinate (needed for clipping)
 */
void ng_draw_to_buffer (tree_node_t *node, int x_off, int y_off, int x_min, int y_min, int x_max, int y_max);
#endif //GITEM_DRAW_H__