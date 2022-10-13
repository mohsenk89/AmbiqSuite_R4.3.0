//*****************************************************************************
//
// @file ng_watchface.h
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

#ifndef NG_GITEM_WATCHFACE_H__
#define NG_GITEM_WATCHFACE_H__
#include "ng_gitem.h"

/** Watchface widget data struct */
typedef struct _gitem_watchface_t
{
    BASE_STRUCT;              /**< Inherited attributes from gitem_base_t data struct*/
    img_obj_t    *image;      /**< Pointer to image asset*/
    gitem_base_t *hour;       /**< Pointer to its hours hand child item (gitem_needle_t)*/
    gitem_base_t *minute;     /**< Pointer to its minutes hand child item (gitem_needle_t)*/
    gitem_base_t *sec;        /**< Pointer to its seconds hand child item (gitem_needle_t)*/
    uint16_t      pen_width;
} gitem_watchface_t;

/** \brief Draw function
 *
 * \param *git 	Pointer to watchface's base gitem (gitem_base_t data struct)
 * \param x_off Horizontal offset from its parent item
 * \param y_off Vertical offset from its parent item
 * \return void
 *
 */
DRAW_FUNC(ng_watchface_draw);

/** \brief Updates the watchface's hand angles according to the current time. System's wall time is used by default.
 *
 * In order to use a different time update method (not the system's wall time), the define WALL_TIME_CLOCKS (defined in the
 * compiler flags of the generated Makefile) needs to be undefined and the time needs to be updated inside the #else segment of this function.
 *
 * \param *git 	Pointer to target gitem (gitem_base_t data struct)
 * \return void
 *
 */
void ng_watchface_update(gitem_base_t *git);

/** Watchface gestures data struct (placeholder)*/
extern const gitem_gestures_t watchface_gestures;

#define NG_WATCHFACE(object) SAFE_CAST((object), gitem_base_t *, gitem_watchface_t *) /**< Type caster from  base gitem_base_t struct to derived gitem_watchface_t struct*/

#endif //NG_GITEM_SCREEN_H__
