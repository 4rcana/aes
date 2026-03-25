// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaes_top.h for the primary calling header

#include "Vaes_top__pch.h"

extern const VlUnpacked<CData/*7:0*/, 256> Vaes_top__ConstPool__TABLE_h7f8eda62_0;

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    __Vtableidx1 = (vlSymsp->TOP.aes_top__DOT__u_ksi__DOT__sw_in 
                    >> 0x00000018U);
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx1];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    // Body
    __Vtableidx2 = (0x000000ffU & (vlSymsp->TOP.aes_top__DOT__u_ksi__DOT__sw_in 
                                   >> 0x00000010U));
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx2];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx3;
    __Vtableidx3 = 0;
    // Body
    __Vtableidx3 = (0x000000ffU & (vlSymsp->TOP.aes_top__DOT__u_ksi__DOT__sw_in 
                                   >> 8U));
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx3];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx4;
    __Vtableidx4 = 0;
    // Body
    __Vtableidx4 = (0x000000ffU & vlSymsp->TOP.aes_top__DOT__u_ksi__DOT__sw_in);
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx4];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx5;
    __Vtableidx5 = 0;
    // Body
    __Vtableidx5 = (vlSymsp->TOP.aes_top__DOT__state[3U] 
                    >> 0x00000018U);
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx5];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx6;
    __Vtableidx6 = 0;
    // Body
    __Vtableidx6 = (0x000000ffU & (vlSymsp->TOP.aes_top__DOT__state[3U] 
                                   >> 0x00000010U));
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx6];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx7;
    __Vtableidx7 = 0;
    // Body
    __Vtableidx7 = (0x000000ffU & (vlSymsp->TOP.aes_top__DOT__state[3U] 
                                   >> 8U));
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx7];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx8;
    __Vtableidx8 = 0;
    // Body
    __Vtableidx8 = (0x000000ffU & vlSymsp->TOP.aes_top__DOT__state[3U]);
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx8];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx9;
    __Vtableidx9 = 0;
    // Body
    __Vtableidx9 = (vlSymsp->TOP.aes_top__DOT__state[2U] 
                    >> 0x00000018U);
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx9];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx10;
    __Vtableidx10 = 0;
    // Body
    __Vtableidx10 = (0x000000ffU & (vlSymsp->TOP.aes_top__DOT__state[2U] 
                                    >> 0x00000010U));
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx10];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx11;
    __Vtableidx11 = 0;
    // Body
    __Vtableidx11 = (0x000000ffU & (vlSymsp->TOP.aes_top__DOT__state[2U] 
                                    >> 8U));
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx11];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx12;
    __Vtableidx12 = 0;
    // Body
    __Vtableidx12 = (0x000000ffU & vlSymsp->TOP.aes_top__DOT__state[2U]);
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx12];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx13;
    __Vtableidx13 = 0;
    // Body
    __Vtableidx13 = (vlSymsp->TOP.aes_top__DOT__state[1U] 
                     >> 0x00000018U);
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx13];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx14;
    __Vtableidx14 = 0;
    // Body
    __Vtableidx14 = (0x000000ffU & (vlSymsp->TOP.aes_top__DOT__state[1U] 
                                    >> 0x00000010U));
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx14];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx15;
    __Vtableidx15 = 0;
    // Body
    __Vtableidx15 = (0x000000ffU & (vlSymsp->TOP.aes_top__DOT__state[1U] 
                                    >> 8U));
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx15];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx16;
    __Vtableidx16 = 0;
    // Body
    __Vtableidx16 = (0x000000ffU & vlSymsp->TOP.aes_top__DOT__state[1U]);
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx16];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx17;
    __Vtableidx17 = 0;
    // Body
    __Vtableidx17 = (vlSymsp->TOP.aes_top__DOT__state[0U] 
                     >> 0x00000018U);
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx17];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx18;
    __Vtableidx18 = 0;
    // Body
    __Vtableidx18 = (0x000000ffU & (vlSymsp->TOP.aes_top__DOT__state[0U] 
                                    >> 0x00000010U));
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx18];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx19;
    __Vtableidx19 = 0;
    // Body
    __Vtableidx19 = (0x000000ffU & (vlSymsp->TOP.aes_top__DOT__state[0U] 
                                    >> 8U));
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx19];
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __Vtableidx20;
    __Vtableidx20 = 0;
    // Body
    __Vtableidx20 = (0x000000ffU & vlSymsp->TOP.aes_top__DOT__state[0U]);
    vlSelfRef.byte_out = Vaes_top__ConstPool__TABLE_h7f8eda62_0
        [__Vtableidx20];
}
