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

#ifndef NEMA_REGS_H__
#define NEMA_REGS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define NEMA_HOLDCMD      (0xff000000U)

#ifndef NEMAP_HOLDCMD
#define NEMAP_HOLDCMD     (0xff000000U)
#endif

#define NEMAP_HOLDGPFLAG  ((uint32_t)1U << 27)

    // Texture Mapping and FB
    //-----------------------------
#define NEMA_TEX0_BASE        (0x000U)
#define NEMA_TEX0_BASE_H      (0x804U)
#define NEMA_TEX0_FSTRIDE     (0x004U)
#define NEMA_TEX0_RESXY       (0x008U)
    //-----------------------------
#define NEMA_TEX1_BASE        (0x010U)
#define NEMA_TEX1_BASE_H      (0x80cU)
#define NEMA_TEX1_FSTRIDE     (0x014U)
#define NEMA_TEX1_RESXY       (0x018U)
#define NEMA_TEX_COLOR        (0x01cU)
    //-----------------------------
#define NEMA_TEX2_BASE        (0x020U)
#define NEMA_TEX2_BASE_H      (0x814U)
#define NEMA_TEX2_FSTRIDE     (0x024U)
#define NEMA_TEX2_RESXY       (0x028U)
    //-----------------------------
#define NEMA_TEX3_BASE        (0x030U)
#define NEMA_TEX3_BASE_H      (0x81cU)
#define NEMA_TEX3_FSTRIDE     (0x034U)
#define NEMA_TEX3_RESXY       (0x038U)

    // Rasterizer
    //-----------------------------
#define NEMA_DRAW_CMD         (0x100U | NEMAP_HOLDCMD)
#define NEMA_DRAW_CMD_NOHOLD  (0x100U)
#define NEMA_DRAW_STARTXY     (0x104U)
#define NEMA_DRAW_ENDXY       (0x108U)
#define NEMA_CLIPMIN          (0x110U)
#define NEMA_CLIPMAX          (0x114U)
#define NEMA_MATMULT          (0x118U)
#define NEMA_CODEPTR          (0x11CU)
    //-----------------------------
#define NEMA_DRAW_PT0_X       (0x120U)
#define NEMA_DRAW_PT0_Y       (0x124U)
#define NEMA_DRAW_COLOR       (0x12cU)
     //-----------------------------
#define NEMA_DRAW_PT1_X       (0x130U)
#define NEMA_DRAW_PT1_Y       (0x134U)
     //-----------------------------
#define NEMA_DRAW_PT2_X       (0x140U)
#define NEMA_DRAW_PT2_Y       (0x144U)
     //-----------------------------
#define NEMA_DRAW_PT3_X       (0x150U)
#define NEMA_DRAW_PT3_Y       (0x154U)
    //-----------------------------
//NemaP specific -->
    //-----------------------------
#define NEMA_BYPASS_ADDR      (0x138U)
#define NEMA_BYPASS_DATA      (0x13cU)
    //-----------------------------
#define NEMA_MM00             (0x160U)
#define NEMA_MM01             (0x164U)
#define NEMA_MM02             (0x168U)
#define NEMA_MM10             (0x16cU)
#define NEMA_MM11             (0x170U)
#define NEMA_MM12             (0x174U)
#define NEMA_MM20             (0x178U)
#define NEMA_MM21             (0x17cU)
#define NEMA_MM22             (0x180U)
    //-----------------------------
#define NEMA_DEPTH_START_L    (0x184U)
#define NEMA_DEPTH_START_H    (0x188U)
#define NEMA_DEPTH_DX_L       (0x18cU)
#define NEMA_DEPTH_DX_H       (0x190U)
#define NEMA_DEPTH_DY_L       (0x194U)
#define NEMA_DEPTH_DY_H       (0x198U)
    //-----------------------------
#define NEMA_RED_DX           (0x1a0U)
#define NEMA_RED_DY           (0x1a4U)
#define NEMA_GRE_DX           (0x1a8U)
#define NEMA_GRE_DY           (0x1acU)
#define NEMA_BLU_DX           (0x1b0U)
#define NEMA_BLU_DY           (0x1b4U)
#define NEMA_ALF_DX           (0x1b8U)
#define NEMA_ALF_DY           (0x1bcU)
#define NEMA_RED_INIT         (0x1c0U)
#define NEMA_GRE_INIT         (0x1c4U)
#define NEMA_BLU_INIT         (0x1c8U)
#define NEMA_ALF_INIT         (0x1ccU)
//<--
//NemaT specific -->
    //-----------------------------
#define NEMA_VERTEX0_X       (0x160U)
#define NEMA_VERTEX0_Y       (0x164U)
#define NEMA_VERTEX0_Z       (0x168U)
#define NEMA_VERTEX0_W       (0x16cU)
    //-----------------------------
#define NEMA_VERTEX1_X       (0x170U)
#define NEMA_VERTEX1_Y       (0x174U)
#define NEMA_VERTEX1_Z       (0x178U)
#define NEMA_VERTEX1_W       (0x17cU)
    //-----------------------------
#define NEMA_VERTEX2_X       (0x180U)
#define NEMA_VERTEX2_Y       (0x184U)
#define NEMA_VERTEX2_Z       (0x188U)
#define NEMA_VERTEX2_W       (0x18cU)
    //-----------------------------
#define NEMA_VERTEX3_X       (0x190U)
#define NEMA_VERTEX3_Y       (0x194U)
#define NEMA_VERTEX3_Z       (0x198U)
#define NEMA_VERTEX3_W       (0x19cU)

    //-----------------------------
#define NEMA_ZFUNC            (0x1e0U)
#define NEMA_DEPTH_MIN        (0x1e4U)
#define NEMA_DEPTH_MAX        (0x1e8U)
    //-----------------------------

    // Varyings
    //-----------------------------
#define NEMA_VERTEX0_VAR0_F0  (0x320U)
#define NEMA_VERTEX0_VAR0_F1  (0x324U)
#define NEMA_VERTEX0_VAR0_F2  (0x328U)
#define NEMA_VERTEX0_VAR0_F3  (0x32cU)
#define NEMA_VERTEX0_VAR1_F0  (0x330U)
#define NEMA_VERTEX0_VAR1_F1  (0x334U)
#define NEMA_VERTEX0_VAR1_F2  (0x338U)
#define NEMA_VERTEX0_VAR1_F3  (0x33cU)
#define NEMA_VERTEX0_VAR2_F0  (0x340U)
#define NEMA_VERTEX0_VAR2_F1  (0x344U)
#define NEMA_VERTEX0_VAR2_F2  (0x348U)
#define NEMA_VERTEX0_VAR2_F3  (0x34cU)
#define NEMA_VERTEX0_VAR3_F0  (0x350U)
#define NEMA_VERTEX0_VAR3_F1  (0x354U)
#define NEMA_VERTEX0_VAR3_F2  (0x358U)
#define NEMA_VERTEX0_VAR3_F3  (0x35cU)
#define NEMA_VERTEX0_VAR4_F0  (0x360U)
#define NEMA_VERTEX0_VAR4_F1  (0x364U)
#define NEMA_VERTEX0_VAR4_F2  (0x368U)
#define NEMA_VERTEX0_VAR4_F3  (0x36cU)
#define NEMA_VERTEX0_VAR5_F0  (0x370U)
#define NEMA_VERTEX0_VAR5_F1  (0x374U)
#define NEMA_VERTEX0_VAR5_F2  (0x378U)
#define NEMA_VERTEX0_VAR5_F3  (0x37cU)
#define NEMA_VERTEX0_VAR6_F0  (0x380U)
#define NEMA_VERTEX0_VAR6_F1  (0x384U)
#define NEMA_VERTEX0_VAR6_F2  (0x388U)
#define NEMA_VERTEX0_VAR6_F3  (0x38cU)
#define NEMA_VERTEX0_VAR7_F0  (0x390U)
#define NEMA_VERTEX0_VAR7_F1  (0x394U)
#define NEMA_VERTEX0_VAR7_F2  (0x398U)
#define NEMA_VERTEX0_VAR7_F3  (0x39cU)
    //-----------------------------
#define NEMA_VERTEX1_VAR0_F0  (0x3a0U)
#define NEMA_VERTEX1_VAR0_F1  (0x3a4U)
#define NEMA_VERTEX1_VAR0_F2  (0x3a8U)
#define NEMA_VERTEX1_VAR0_F3  (0x3acU)
#define NEMA_VERTEX1_VAR1_F0  (0x3b0U)
#define NEMA_VERTEX1_VAR1_F1  (0x3b4U)
#define NEMA_VERTEX1_VAR1_F2  (0x3b8U)
#define NEMA_VERTEX1_VAR1_F3  (0x3bcU)
#define NEMA_VERTEX1_VAR2_F0  (0x3c0U)
#define NEMA_VERTEX1_VAR2_F1  (0x3c4U)
#define NEMA_VERTEX1_VAR2_F2  (0x3c8U)
#define NEMA_VERTEX1_VAR2_F3  (0x3ccU)
#define NEMA_VERTEX1_VAR3_F0  (0x3d0U)
#define NEMA_VERTEX1_VAR3_F1  (0x3d4U)
#define NEMA_VERTEX1_VAR3_F2  (0x3d8U)
#define NEMA_VERTEX1_VAR3_F3  (0x3dcU)
#define NEMA_VERTEX1_VAR4_F0  (0x3e0U)
#define NEMA_VERTEX1_VAR4_F1  (0x3e4U)
#define NEMA_VERTEX1_VAR4_F2  (0x3e8U)
#define NEMA_VERTEX1_VAR4_F3  (0x3ecU)
#define NEMA_VERTEX1_VAR5_F0  (0x3f0U)
#define NEMA_VERTEX1_VAR5_F1  (0x3f4U)
#define NEMA_VERTEX1_VAR5_F2  (0x3f8U)
#define NEMA_VERTEX1_VAR5_F3  (0x3fcU)
#define NEMA_VERTEX1_VAR6_F0  (0x400U)
#define NEMA_VERTEX1_VAR6_F1  (0x404U)
#define NEMA_VERTEX1_VAR6_F2  (0x408U)
#define NEMA_VERTEX1_VAR6_F3  (0x40cU)
#define NEMA_VERTEX1_VAR7_F0  (0x410U)
#define NEMA_VERTEX1_VAR7_F1  (0x414U)
#define NEMA_VERTEX1_VAR7_F2  (0x418U)
#define NEMA_VERTEX1_VAR7_F3  (0x41cU)
    //-----------------------------
#define NEMA_VERTEX2_VAR0_F0  (0x420U)
#define NEMA_VERTEX2_VAR0_F1  (0x424U)
#define NEMA_VERTEX2_VAR0_F2  (0x428U)
#define NEMA_VERTEX2_VAR0_F3  (0x42cU)
#define NEMA_VERTEX2_VAR1_F0  (0x430U)
#define NEMA_VERTEX2_VAR1_F1  (0x434U)
#define NEMA_VERTEX2_VAR1_F2  (0x438U)
#define NEMA_VERTEX2_VAR1_F3  (0x43cU)
#define NEMA_VERTEX2_VAR2_F0  (0x440U)
#define NEMA_VERTEX2_VAR2_F1  (0x444U)
#define NEMA_VERTEX2_VAR2_F2  (0x448U)
#define NEMA_VERTEX2_VAR2_F3  (0x44cU)
#define NEMA_VERTEX2_VAR3_F0  (0x450U)
#define NEMA_VERTEX2_VAR3_F1  (0x454U)
#define NEMA_VERTEX2_VAR3_F2  (0x458U)
#define NEMA_VERTEX2_VAR3_F3  (0x45cU)
#define NEMA_VERTEX2_VAR4_F0  (0x460U)
#define NEMA_VERTEX2_VAR4_F1  (0x464U)
#define NEMA_VERTEX2_VAR4_F2  (0x468U)
#define NEMA_VERTEX2_VAR4_F3  (0x46cU)
#define NEMA_VERTEX2_VAR5_F0  (0x470U)
#define NEMA_VERTEX2_VAR5_F1  (0x474U)
#define NEMA_VERTEX2_VAR5_F2  (0x478U)
#define NEMA_VERTEX2_VAR5_F3  (0x47cU)
#define NEMA_VERTEX2_VAR6_F0  (0x480U)
#define NEMA_VERTEX2_VAR6_F1  (0x484U)
#define NEMA_VERTEX2_VAR6_F2  (0x488U)
#define NEMA_VERTEX2_VAR6_F3  (0x48cU)
#define NEMA_VERTEX2_VAR7_F0  (0x490U)
#define NEMA_VERTEX2_VAR7_F1  (0x494U)
#define NEMA_VERTEX2_VAR7_F2  (0x498U)
#define NEMA_VERTEX2_VAR7_F3  (0x49cU)
    //-----------------------------
#define NEMA_VARYING0_INFO    (0x4a0U)
#define NEMA_VARYING1_INFO    (0x4a4U)
#define NEMA_VARYING2_INFO    (0x4a8U)
#define NEMA_VARYING3_INFO    (0x4acU)
#define NEMA_VARYING4_INFO    (0x4b0U)
#define NEMA_VARYING5_INFO    (0x4b4U)
#define NEMA_VARYING6_INFO    (0x4b8U)
#define NEMA_VARYING7_INFO    (0x4bcU)

    // Vertex
    //-----------------------------
#define NEMA_VERTEX_VA_PTR    (0x300U)
#define NEMA_VERTEX_VS_PTR    (0x304U)
#define NEMA_VERTEX_REGADDR   (0x308U)
#define NEMA_VERTEX_REGDATA   (0x30cU)
#define NEMA_VERTEX_CONADDR   (0x310U)
#define NEMA_VERTEX_CONDATA   (0x314U)
#define NEMA_VERTEX_TRIGGER   (0x318U | NEMA_HOLDCMD)
    //-----------------------------
#define NEMA_VERTEX_MVP00     (0x3c0U)
#define NEMA_VERTEX_MVP01     (0x3c4U)
#define NEMA_VERTEX_MVP02     (0x3c8U)
#define NEMA_VERTEX_MVP03     (0x3ccU)
#define NEMA_VERTEX_MVP10     (0x3d0U)
#define NEMA_VERTEX_MVP11     (0x3d4U)
#define NEMA_VERTEX_MVP12     (0x3d8U)
#define NEMA_VERTEX_MVP13     (0x3dcU)
#define NEMA_VERTEX_MVP20     (0x3e0U)
#define NEMA_VERTEX_MVP21     (0x3e4U)
#define NEMA_VERTEX_MVP22     (0x3e8U)
#define NEMA_VERTEX_MVP23     (0x3ecU)
#define NEMA_VERTEX_MVP30     (0x3f0U)
#define NEMA_VERTEX_MVP31     (0x3f4U)
#define NEMA_VERTEX_MVP32     (0x3f8U)
#define NEMA_VERTEX_MVP33     (0x3fcU)
    //-----------------------------

    // ViewPort
    //-----------------------------
#define NEMA_VIEWPORT_X     (0x4c0U)
#define NEMA_VIEWPORT_Y     (0x4c4U)
#define NEMA_VIEWPORT_W     (0x4c8U)
#define NEMA_VIEWPORT_H     (0x4ccU)
    //-----------------------------
//<--

    // Processor
    //-----------------------------
#define NEMA_ROPBLENDER_BLEND_MODE  (0x1d0U)
#define NEMA_ROPBLENDER_DST_CKEY    (0x1d4U)
#define NEMA_ROPBLENDER_CONST_COLOR (0x1d8U)
    //-----------------------------

    // Processor
    //-----------------------------
#define NEMA_IMEM_ADDR        (0x0c4U)
#define NEMA_IMEM_DATAH       (0x0c8U)
#define NEMA_IMEM_DATAL       (0x0ccU)
#define NEMA_FORKPTR          (0x0d0U)
#define NEMA_FORKDATA         (0x0d8U | NEMA_HOLDCMD)
#define NEMA_FORKDATAH        (0x0dcU)
    //-----------------------------
#define NEMA_C0_REG           (0x200U)
#define NEMA_C1_REG           (0x204U)
#define NEMA_C2_REG           (0x208U)
#define NEMA_C3_REG           (0x20cU)
#define NEMA_CMAX_REG         (0x20cU)
#define NEMA_FRAG_CONADDR     (0x210U)
#define NEMA_FRAG_CONDATA     (0x214U)

    // Status & Control
    //-----------------------------
#define NEMA_CLID             (0x148U)
#define NEMA_LOADCTRL         (0x1f0U)
#define NEMA_CONFIG           (0x1f0U)
#define NEMA_CONFIGH          (0x1f4U)
#define NEMA_IDREG            (0x1ecU)
#define NEMA_CMDSTATUS        (0x0e8U)
#define NEMA_CMDRINGSTOP      (0x0ecU)
#define NEMA_CMDRINGSTOP_H    (0x844U)
#define NEMA_CMDADDR          (0x0f0U)
#define NEMA_CMDADDR_H        (0x84cU)
#define NEMA_CMDSIZE          (0x0f4U)
#define NEMA_INTERRUPT        (0x0f8U)
#define NEMA_IRQ_ID           (0xff0U)

// bits [11:8]: GP_FLAGS_IRQ_MASK
// bits [ 7:4]: GP_FLAGS_MASK
// bits [ 3:0]: GP_FLAGS
#define NEMA_GP_FLAGS         (0xff4U)

#define NEMA_SYS_INTERRUPT    (0xff8U)
#define NEMA_STATUS           (0x0fcU)

#define NEMA_BREAKPOINT       (0x080U)
#define NEMA_BREAKPOINT_MASK  (0x08CU)
    //-----------------------------

    // Debug & Monitor
    //-----------------------------
#define NEMA_DBG_STATUS       (0x2f0U)
#define NEMA_DBG_ADDR         (0x2f4U)
#define NEMA_DBG_DATA         (0x2f8U)
#define NEMA_DBG_CTRL         (0x2fcU)
    //-----------------------------

    // Clockgating control
    //----------------------------
#define NEMA_CGCMD            (0x090U)
#define NEMA_CGCTRL           (0x094U)

    // Dirty Region
    //----------------------------
#define NEMA_DIRTYMIN         (0x098U)
#define NEMA_DIRTYMAX         (0x09cU)

#ifdef __cplusplus
}
#endif

#endif
