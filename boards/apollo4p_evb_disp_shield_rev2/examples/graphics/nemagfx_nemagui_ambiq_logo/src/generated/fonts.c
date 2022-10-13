//*****************************************************************************
//
//  fonts.c
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

#include "nema_font.h"
#include "nema_utils.h"
#include "ng_utils.h"

#define NEMA_FONT_IMPLEMENTATION
    #if defined(SCENARIO_A)
        #include "assets/fonts/NotoSans_Regular70pt8b.h"
    #elif defined(SCENARIO_B)
        #include "assets/fonts/NotoSans_Regular70pt8b.h"
    #elif defined(SCENARIO_C)
        #include "assets/fonts/NotoSans_Regular80pt8b.h"
    #endif
#undef NEMA_FONT_IMPLEMENTATION

#include "fonts.h"

void load_font_assets(void)
{
#if 0
    NotoSans_Regular80pt8b.bo = nema_load_file("assets/fonts/NotoSans_Regular80pt8b.bin", -1, 0);
#else
    #if defined(SCENARIO_A)
        NotoSans_Regular70pt8b.bo = NG_LOAD_ARRAY(NotoSans_Regular70pt8bBitmaps);
    #elif defined(SCENARIO_B)
        NotoSans_Regular70pt8b.bo = NG_LOAD_ARRAY(NotoSans_Regular70pt8bBitmaps);
    #elif defined(SCENARIO_C)
        NotoSans_Regular80pt8b.bo = NG_LOAD_ARRAY(NotoSans_Regular80pt8bBitmaps);
    #endif
#endif
}

