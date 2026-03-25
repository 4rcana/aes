// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaes_top.h for the primary calling header

#include "Vaes_top__pch.h"

void Vaes_top___024root___eval_triggers_vec__act(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_triggers_vec__act\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((~ (IData)(vlSelfRef.rst_n)) 
                                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0)) 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.clk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

bool Vaes_top___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vaes_top___024root___nba_sequent__TOP__0(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___nba_sequent__TOP__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vdly__aes_top__DOT__running;
    __Vdly__aes_top__DOT__running = 0;
    CData/*5:0*/ __Vdly__aes_top__DOT__u_ksi__DOT__word_idx;
    __Vdly__aes_top__DOT__u_ksi__DOT__word_idx = 0;
    CData/*0:0*/ __Vdly__aes_top__DOT__u_ksi__DOT__expanding;
    __Vdly__aes_top__DOT__u_ksi__DOT__expanding = 0;
    // Body
    __Vdly__aes_top__DOT__u_ksi__DOT__expanding = vlSelfRef.aes_top__DOT__u_ksi__DOT__expanding;
    vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v0 = 0U;
    vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v1 = 0U;
    vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v2 = 0U;
    vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v3 = 0U;
    vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v4 = 0U;
    __Vdly__aes_top__DOT__u_ksi__DOT__word_idx = vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx;
    vlSelfRef.__Vdly__aes_top__DOT__round_num = vlSelfRef.aes_top__DOT__round_num;
    __Vdly__aes_top__DOT__running = vlSelfRef.aes_top__DOT__running;
    if (vlSelfRef.rst_n) {
        if ((((IData)(vlSelfRef.enc_start) & (IData)(vlSelfRef.key_ready)) 
             & (~ (IData)(vlSelfRef.aes_top__DOT__running)))) {
            vlSelfRef.aes_top__DOT__state[0U] = (vlSelfRef.plaintext[0U] 
                                                 ^ vlSelfRef.aes_top__DOT__round_key[0U]);
            vlSelfRef.aes_top__DOT__state[1U] = (vlSelfRef.plaintext[1U] 
                                                 ^ vlSelfRef.aes_top__DOT__round_key[1U]);
            vlSelfRef.aes_top__DOT__state[2U] = (vlSelfRef.plaintext[2U] 
                                                 ^ vlSelfRef.aes_top__DOT__round_key[2U]);
            vlSelfRef.aes_top__DOT__state[3U] = (vlSelfRef.plaintext[3U] 
                                                 ^ vlSelfRef.aes_top__DOT__round_key[3U]);
            vlSelfRef.__Vdly__aes_top__DOT__round_num = 1U;
            __Vdly__aes_top__DOT__running = 1U;
            vlSelfRef.enc_done = 0U;
        } else if (vlSelfRef.aes_top__DOT__running) {
            vlSelfRef.aes_top__DOT__state[0U] = vlSelfRef.aes_top__DOT__round_out[0U];
            vlSelfRef.aes_top__DOT__state[1U] = vlSelfRef.aes_top__DOT__round_out[1U];
            vlSelfRef.aes_top__DOT__state[2U] = vlSelfRef.aes_top__DOT__round_out[2U];
            vlSelfRef.aes_top__DOT__state[3U] = vlSelfRef.aes_top__DOT__round_out[3U];
            if ((0x0aU == (IData)(vlSelfRef.aes_top__DOT__round_num))) {
                vlSelfRef.ciphertext[0U] = vlSelfRef.aes_top__DOT__round_out[0U];
                vlSelfRef.ciphertext[1U] = vlSelfRef.aes_top__DOT__round_out[1U];
                vlSelfRef.ciphertext[2U] = vlSelfRef.aes_top__DOT__round_out[2U];
                vlSelfRef.ciphertext[3U] = vlSelfRef.aes_top__DOT__round_out[3U];
                vlSelfRef.enc_done = 1U;
                __Vdly__aes_top__DOT__running = 0U;
                vlSelfRef.__Vdly__aes_top__DOT__round_num = 0U;
            } else {
                vlSelfRef.__Vdly__aes_top__DOT__round_num 
                    = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.aes_top__DOT__round_num)));
            }
        }
        if (vlSelfRef.key_load) {
            vlSelfRef.aes_top__DOT__u_ksi__DOT__j = 4U;
            vlSelfRef.aes_top__DOT__u_ksi__DOT____Vlvbound_h2d2a71e7__0 
                = vlSelfRef.key_in[3U];
            vlSelfRef.__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v0 
                = vlSelfRef.aes_top__DOT__u_ksi__DOT____Vlvbound_h2d2a71e7__0;
            vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v0 = 1U;
            __Vdly__aes_top__DOT__u_ksi__DOT__word_idx = 4U;
            __Vdly__aes_top__DOT__u_ksi__DOT__expanding = 1U;
            vlSelfRef.key_ready = 0U;
            vlSelfRef.aes_top__DOT__u_ksi__DOT____Vlvbound_h2d2a71e7__0 
                = vlSelfRef.key_in[2U];
            vlSelfRef.__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v1 
                = vlSelfRef.aes_top__DOT__u_ksi__DOT____Vlvbound_h2d2a71e7__0;
            vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v1 = 1U;
            vlSelfRef.aes_top__DOT__u_ksi__DOT____Vlvbound_h2d2a71e7__0 
                = vlSelfRef.key_in[1U];
            vlSelfRef.__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v2 
                = vlSelfRef.aes_top__DOT__u_ksi__DOT____Vlvbound_h2d2a71e7__0;
            vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v2 = 1U;
            vlSelfRef.aes_top__DOT__u_ksi__DOT____Vlvbound_h2d2a71e7__0 
                = vlSelfRef.key_in[0U];
            vlSelfRef.__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v3 
                = vlSelfRef.aes_top__DOT__u_ksi__DOT____Vlvbound_h2d2a71e7__0;
            vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v3 = 1U;
        } else if (vlSelfRef.aes_top__DOT__u_ksi__DOT__expanding) {
            vlSelfRef.aes_top__DOT__u_ksi__DOT____Vlvbound_h94f983f0__0 
                = vlSelfRef.aes_top__DOT__u_ksi__DOT__new_word;
            if ((0x2bU >= (IData)(vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx))) {
                vlSelfRef.__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v4 
                    = vlSelfRef.aes_top__DOT__u_ksi__DOT____Vlvbound_h94f983f0__0;
                vlSelfRef.__VdlyDim0__aes_top__DOT__u_ksi__DOT__w__v4 
                    = vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx;
                vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v4 = 1U;
            }
            if ((0x2bU == (IData)(vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx))) {
                __Vdly__aes_top__DOT__u_ksi__DOT__expanding = 0U;
                vlSelfRef.key_ready = 1U;
            } else {
                __Vdly__aes_top__DOT__u_ksi__DOT__word_idx 
                    = (0x0000003fU & ((IData)(1U) + (IData)(vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx)));
            }
        }
        vlSelfRef.aes_top__DOT__round_out[0U] = (((0x0aU 
                                                   == (IData)(vlSelfRef.aes_top__DOT__round_num))
                                                   ? 
                                                  ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox.byte_out) 
                                                     << 0x00000018U) 
                                                    | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox.byte_out) 
                                                       << 0x00000010U)) 
                                                   | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox.byte_out) 
                                                       << 8U) 
                                                      | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox.byte_out)))
                                                   : vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__3__KET____DOT__u_col__out) 
                                                 ^ vlSelfRef.aes_top__DOT__round_key[0U]);
        vlSelfRef.aes_top__DOT__round_out[1U] = (((0x0aU 
                                                   == (IData)(vlSelfRef.aes_top__DOT__round_num))
                                                   ? 
                                                  ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox.byte_out) 
                                                     << 0x00000018U) 
                                                    | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox.byte_out) 
                                                       << 0x00000010U)) 
                                                   | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox.byte_out) 
                                                       << 8U) 
                                                      | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox.byte_out)))
                                                   : vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__2__KET____DOT__u_col__out) 
                                                 ^ vlSelfRef.aes_top__DOT__round_key[1U]);
        vlSelfRef.aes_top__DOT__round_out[2U] = (((0x0aU 
                                                   == (IData)(vlSelfRef.aes_top__DOT__round_num))
                                                   ? (IData)(
                                                             (((QData)((IData)(
                                                                               ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox.byte_out) 
                                                                                << 0x00000018U) 
                                                                                | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox.byte_out) 
                                                                                << 0x00000010U)) 
                                                                                | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox.byte_out) 
                                                                                << 8U) 
                                                                                | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox.byte_out))))) 
                                                               << 0x00000020U) 
                                                              | (QData)((IData)(
                                                                                ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox.byte_out) 
                                                                                << 0x00000018U) 
                                                                                | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox.byte_out) 
                                                                                << 0x00000010U)) 
                                                                                | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox.byte_out) 
                                                                                << 8U) 
                                                                                | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox.byte_out)))))))
                                                   : (IData)(
                                                             (((QData)((IData)(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out)) 
                                                               << 0x00000020U) 
                                                              | (QData)((IData)(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out))))) 
                                                 ^ vlSelfRef.aes_top__DOT__round_key[2U]);
        vlSelfRef.aes_top__DOT__round_out[3U] = (((0x0aU 
                                                   == (IData)(vlSelfRef.aes_top__DOT__round_num))
                                                   ? (IData)(
                                                             ((((QData)((IData)(
                                                                                ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox.byte_out) 
                                                                                << 0x00000018U) 
                                                                                | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox.byte_out) 
                                                                                << 0x00000010U)) 
                                                                                | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox.byte_out) 
                                                                                << 8U) 
                                                                                | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox.byte_out))))) 
                                                                << 0x00000020U) 
                                                               | (QData)((IData)(
                                                                                ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox.byte_out) 
                                                                                << 0x00000018U) 
                                                                                | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox.byte_out) 
                                                                                << 0x00000010U)) 
                                                                                | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox.byte_out) 
                                                                                << 8U) 
                                                                                | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox.byte_out)))))) 
                                                              >> 0x00000020U))
                                                   : (IData)(
                                                             ((((QData)((IData)(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out)) 
                                                                << 0x00000020U) 
                                                               | (QData)((IData)(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out))) 
                                                              >> 0x00000020U))) 
                                                 ^ vlSelfRef.aes_top__DOT__round_key[3U]);
    } else {
        vlSelfRef.__Vdly__aes_top__DOT__round_num = 0U;
        __Vdly__aes_top__DOT__running = 0U;
        vlSelfRef.enc_done = 0U;
        vlSelfRef.aes_top__DOT__round_out[0U] = 0U;
        vlSelfRef.aes_top__DOT__round_out[1U] = 0U;
        vlSelfRef.aes_top__DOT__round_out[2U] = 0U;
        vlSelfRef.aes_top__DOT__round_out[3U] = 0U;
        __Vdly__aes_top__DOT__u_ksi__DOT__word_idx = 0U;
        __Vdly__aes_top__DOT__u_ksi__DOT__expanding = 0U;
        vlSelfRef.key_ready = 0U;
    }
    vlSelfRef.aes_top__DOT__running = __Vdly__aes_top__DOT__running;
    vlSelfRef.aes_top__DOT__u_ksi__DOT__expanding = __Vdly__aes_top__DOT__u_ksi__DOT__expanding;
    vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx = __Vdly__aes_top__DOT__u_ksi__DOT__word_idx;
}

void Vaes_top___024root___nba_sequent__TOP__1(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___nba_sequent__TOP__1\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_ASSIGNSEL_II(32, 8, 0x18U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out, 
                    (((([&]() {
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__1__b 
                                = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox.byte_out;
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__1__Vfuncout 
                                = (0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__1__b))
                                                   ? 
                                                  (0x1bU 
                                                   ^ 
                                                   VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__1__b), 1U))
                                                   : 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__1__b), 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__1__Vfuncout)) 
                       ^ (([&]() {
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__2__b 
                                    = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox.byte_out;
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__2__Vfuncout 
                                    = (0x000000ffU 
                                       & ((0x00000080U 
                                           & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__2__b))
                                           ? (0x1bU 
                                              ^ VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__2__b), 1U))
                                           : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__2__b), 1U)));
                            }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__2__Vfuncout)) 
                          ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox.byte_out))) 
                      ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox.byte_out)) 
                     ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox.byte_out)));
    VL_ASSIGNSEL_II(32, 8, 0x10U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out, 
                    ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox.byte_out) 
                       ^ ([&]() {
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__3__b 
                                = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox.byte_out;
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__3__Vfuncout 
                                = (0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__3__b))
                                                   ? 
                                                  (0x1bU 
                                                   ^ 
                                                   VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__3__b), 1U))
                                                   : 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__3__b), 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__3__Vfuncout))) 
                      ^ (([&]() {
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__4__b 
                                = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox.byte_out;
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__4__Vfuncout 
                                = (0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__4__b))
                                                   ? 
                                                  (0x1bU 
                                                   ^ 
                                                   VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__4__b), 1U))
                                                   : 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__4__b), 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__4__Vfuncout)) 
                         ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox.byte_out))) 
                     ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox.byte_out)));
    VL_ASSIGNSEL_II(32, 8, 8U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out, 
                    ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox.byte_out) 
                       ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox.byte_out)) 
                      ^ ([&]() {
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__5__b 
                            = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox.byte_out;
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__5__Vfuncout 
                            = (0x000000ffU & ((0x00000080U 
                                               & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__5__b))
                                               ? (0x1bU 
                                                  ^ 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__5__b), 1U))
                                               : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__5__b), 1U)));
                    }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__5__Vfuncout))) 
                     ^ (([&]() {
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__6__b 
                            = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox.byte_out;
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__6__Vfuncout 
                            = (0x000000ffU & ((0x00000080U 
                                               & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__6__b))
                                               ? (0x1bU 
                                                  ^ 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__6__b), 1U))
                                               : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__6__b), 1U)));
                    }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__6__Vfuncout)) 
                        ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox.byte_out))));
    VL_ASSIGNSEL_II(32, 8, 0U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out, 
                    ((((([&]() {
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__7__b 
                                    = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox.byte_out;
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__7__Vfuncout 
                                    = (0x000000ffU 
                                       & ((0x00000080U 
                                           & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__7__b))
                                           ? (0x1bU 
                                              ^ VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__7__b), 1U))
                                           : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__7__b), 1U)));
                            }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__7__Vfuncout)) 
                        ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox.byte_out)) 
                       ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox.byte_out)) 
                      ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox.byte_out)) 
                     ^ ([&]() {
                    vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__8__b 
                        = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox.byte_out;
                    vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__8__Vfuncout 
                        = (0x000000ffU & ((0x00000080U 
                                           & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__8__b))
                                           ? (0x1bU 
                                              ^ VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__8__b), 1U))
                                           : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__8__b), 1U)));
                }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__8__Vfuncout))));
    VL_ASSIGNSEL_II(32, 8, 0x18U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out, 
                    (((([&]() {
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__9__b 
                                = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox.byte_out;
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__9__Vfuncout 
                                = (0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__9__b))
                                                   ? 
                                                  (0x1bU 
                                                   ^ 
                                                   VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__9__b), 1U))
                                                   : 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__9__b), 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__9__Vfuncout)) 
                       ^ (([&]() {
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__10__b 
                                    = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox.byte_out;
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__10__Vfuncout 
                                    = (0x000000ffU 
                                       & ((0x00000080U 
                                           & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__10__b))
                                           ? (0x1bU 
                                              ^ VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__10__b), 1U))
                                           : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__10__b), 1U)));
                            }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__10__Vfuncout)) 
                          ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox.byte_out))) 
                      ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox.byte_out)) 
                     ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox.byte_out)));
    VL_ASSIGNSEL_II(32, 8, 0x10U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out, 
                    ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox.byte_out) 
                       ^ ([&]() {
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__11__b 
                                = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox.byte_out;
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__11__Vfuncout 
                                = (0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__11__b))
                                                   ? 
                                                  (0x1bU 
                                                   ^ 
                                                   VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__11__b), 1U))
                                                   : 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__11__b), 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__11__Vfuncout))) 
                      ^ (([&]() {
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__12__b 
                                = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox.byte_out;
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__12__Vfuncout 
                                = (0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__12__b))
                                                   ? 
                                                  (0x1bU 
                                                   ^ 
                                                   VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__12__b), 1U))
                                                   : 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__12__b), 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__12__Vfuncout)) 
                         ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox.byte_out))) 
                     ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox.byte_out)));
    VL_ASSIGNSEL_II(32, 8, 8U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out, 
                    ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox.byte_out) 
                       ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox.byte_out)) 
                      ^ ([&]() {
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__13__b 
                            = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox.byte_out;
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__13__Vfuncout 
                            = (0x000000ffU & ((0x00000080U 
                                               & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__13__b))
                                               ? (0x1bU 
                                                  ^ 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__13__b), 1U))
                                               : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__13__b), 1U)));
                    }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__13__Vfuncout))) 
                     ^ (([&]() {
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__14__b 
                            = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox.byte_out;
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__14__Vfuncout 
                            = (0x000000ffU & ((0x00000080U 
                                               & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__14__b))
                                               ? (0x1bU 
                                                  ^ 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__14__b), 1U))
                                               : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__14__b), 1U)));
                    }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__14__Vfuncout)) 
                        ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox.byte_out))));
    VL_ASSIGNSEL_II(32, 8, 0U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out, 
                    ((((([&]() {
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__15__b 
                                    = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox.byte_out;
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__15__Vfuncout 
                                    = (0x000000ffU 
                                       & ((0x00000080U 
                                           & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__15__b))
                                           ? (0x1bU 
                                              ^ VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__15__b), 1U))
                                           : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__15__b), 1U)));
                            }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__15__Vfuncout)) 
                        ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox.byte_out)) 
                       ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox.byte_out)) 
                      ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox.byte_out)) 
                     ^ ([&]() {
                    vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__16__b 
                        = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox.byte_out;
                    vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__16__Vfuncout 
                        = (0x000000ffU & ((0x00000080U 
                                           & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__16__b))
                                           ? (0x1bU 
                                              ^ VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__16__b), 1U))
                                           : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__16__b), 1U)));
                }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__16__Vfuncout))));
    VL_ASSIGNSEL_II(32, 8, 0x18U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__2__KET____DOT__u_col__out, 
                    (((([&]() {
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__17__b 
                                = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox.byte_out;
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__17__Vfuncout 
                                = (0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__17__b))
                                                   ? 
                                                  (0x1bU 
                                                   ^ 
                                                   VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__17__b), 1U))
                                                   : 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__17__b), 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__17__Vfuncout)) 
                       ^ (([&]() {
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__18__b 
                                    = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox.byte_out;
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__18__Vfuncout 
                                    = (0x000000ffU 
                                       & ((0x00000080U 
                                           & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__18__b))
                                           ? (0x1bU 
                                              ^ VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__18__b), 1U))
                                           : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__18__b), 1U)));
                            }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__18__Vfuncout)) 
                          ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox.byte_out))) 
                      ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox.byte_out)) 
                     ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox.byte_out)));
    VL_ASSIGNSEL_II(32, 8, 0x10U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__2__KET____DOT__u_col__out, 
                    ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox.byte_out) 
                       ^ ([&]() {
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__19__b 
                                = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox.byte_out;
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__19__Vfuncout 
                                = (0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__19__b))
                                                   ? 
                                                  (0x1bU 
                                                   ^ 
                                                   VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__19__b), 1U))
                                                   : 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__19__b), 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__19__Vfuncout))) 
                      ^ (([&]() {
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__20__b 
                                = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox.byte_out;
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__20__Vfuncout 
                                = (0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__20__b))
                                                   ? 
                                                  (0x1bU 
                                                   ^ 
                                                   VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__20__b), 1U))
                                                   : 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__20__b), 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__20__Vfuncout)) 
                         ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox.byte_out))) 
                     ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox.byte_out)));
    VL_ASSIGNSEL_II(32, 8, 8U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__2__KET____DOT__u_col__out, 
                    ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox.byte_out) 
                       ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox.byte_out)) 
                      ^ ([&]() {
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__21__b 
                            = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox.byte_out;
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__21__Vfuncout 
                            = (0x000000ffU & ((0x00000080U 
                                               & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__21__b))
                                               ? (0x1bU 
                                                  ^ 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__21__b), 1U))
                                               : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__21__b), 1U)));
                    }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__21__Vfuncout))) 
                     ^ (([&]() {
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__22__b 
                            = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox.byte_out;
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__22__Vfuncout 
                            = (0x000000ffU & ((0x00000080U 
                                               & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__22__b))
                                               ? (0x1bU 
                                                  ^ 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__22__b), 1U))
                                               : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__22__b), 1U)));
                    }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__22__Vfuncout)) 
                        ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox.byte_out))));
    VL_ASSIGNSEL_II(32, 8, 0U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__2__KET____DOT__u_col__out, 
                    ((((([&]() {
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__23__b 
                                    = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox.byte_out;
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__23__Vfuncout 
                                    = (0x000000ffU 
                                       & ((0x00000080U 
                                           & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__23__b))
                                           ? (0x1bU 
                                              ^ VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__23__b), 1U))
                                           : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__23__b), 1U)));
                            }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__23__Vfuncout)) 
                        ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox.byte_out)) 
                       ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox.byte_out)) 
                      ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox.byte_out)) 
                     ^ ([&]() {
                    vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__24__b 
                        = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox.byte_out;
                    vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__24__Vfuncout 
                        = (0x000000ffU & ((0x00000080U 
                                           & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__24__b))
                                           ? (0x1bU 
                                              ^ VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__24__b), 1U))
                                           : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__24__b), 1U)));
                }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__24__Vfuncout))));
    VL_ASSIGNSEL_II(32, 8, 0x18U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__3__KET____DOT__u_col__out, 
                    (((([&]() {
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__25__b 
                                = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox.byte_out;
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__25__Vfuncout 
                                = (0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__25__b))
                                                   ? 
                                                  (0x1bU 
                                                   ^ 
                                                   VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__25__b), 1U))
                                                   : 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__25__b), 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__25__Vfuncout)) 
                       ^ (([&]() {
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__26__b 
                                    = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox.byte_out;
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__26__Vfuncout 
                                    = (0x000000ffU 
                                       & ((0x00000080U 
                                           & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__26__b))
                                           ? (0x1bU 
                                              ^ VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__26__b), 1U))
                                           : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__26__b), 1U)));
                            }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__26__Vfuncout)) 
                          ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox.byte_out))) 
                      ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox.byte_out)) 
                     ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox.byte_out)));
    VL_ASSIGNSEL_II(32, 8, 0x10U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__3__KET____DOT__u_col__out, 
                    ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox.byte_out) 
                       ^ ([&]() {
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__27__b 
                                = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox.byte_out;
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__27__Vfuncout 
                                = (0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__27__b))
                                                   ? 
                                                  (0x1bU 
                                                   ^ 
                                                   VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__27__b), 1U))
                                                   : 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__27__b), 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__27__Vfuncout))) 
                      ^ (([&]() {
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__28__b 
                                = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox.byte_out;
                            vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__28__Vfuncout 
                                = (0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__28__b))
                                                   ? 
                                                  (0x1bU 
                                                   ^ 
                                                   VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__28__b), 1U))
                                                   : 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__28__b), 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__28__Vfuncout)) 
                         ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox.byte_out))) 
                     ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox.byte_out)));
    VL_ASSIGNSEL_II(32, 8, 8U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__3__KET____DOT__u_col__out, 
                    ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox.byte_out) 
                       ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox.byte_out)) 
                      ^ ([&]() {
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__29__b 
                            = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox.byte_out;
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__29__Vfuncout 
                            = (0x000000ffU & ((0x00000080U 
                                               & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__29__b))
                                               ? (0x1bU 
                                                  ^ 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__29__b), 1U))
                                               : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__29__b), 1U)));
                    }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__29__Vfuncout))) 
                     ^ (([&]() {
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__30__b 
                            = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox.byte_out;
                        vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__30__Vfuncout 
                            = (0x000000ffU & ((0x00000080U 
                                               & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__30__b))
                                               ? (0x1bU 
                                                  ^ 
                                                  VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__30__b), 1U))
                                               : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__30__b), 1U)));
                    }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__30__Vfuncout)) 
                        ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox.byte_out))));
    VL_ASSIGNSEL_II(32, 8, 0U, vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__3__KET____DOT__u_col__out, 
                    ((((([&]() {
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__31__b 
                                    = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox.byte_out;
                                vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__31__Vfuncout 
                                    = (0x000000ffU 
                                       & ((0x00000080U 
                                           & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__31__b))
                                           ? (0x1bU 
                                              ^ VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__31__b), 1U))
                                           : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__31__b), 1U)));
                            }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__31__Vfuncout)) 
                        ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox.byte_out)) 
                       ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox.byte_out)) 
                      ^ (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox.byte_out)) 
                     ^ ([&]() {
                    vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__32__b 
                        = vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox.byte_out;
                    vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__32__Vfuncout 
                        = (0x000000ffU & ((0x00000080U 
                                           & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__32__b))
                                           ? (0x1bU 
                                              ^ VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__32__b), 1U))
                                           : VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__32__b), 1U)));
                }(), (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__32__Vfuncout))));
}

void Vaes_top___024root___nba_sequent__TOP__2(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___nba_sequent__TOP__2\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.aes_top__DOT__round_key[0U] = ((0x2bU 
                                              >= (0x0000003fU 
                                                  & ((IData)(3U) 
                                                     + 
                                                     ((IData)(vlSelfRef.aes_top__DOT__round_num) 
                                                      << 2U))))
                                              ? vlSelfRef.aes_top__DOT__u_ksi__DOT__w
                                             [(0x0000003fU 
                                               & ((IData)(3U) 
                                                  + 
                                                  ((IData)(vlSelfRef.aes_top__DOT__round_num) 
                                                   << 2U)))]
                                              : 0U);
    vlSelfRef.aes_top__DOT__round_key[1U] = ((0x2bU 
                                              >= (0x0000003fU 
                                                  & ((IData)(2U) 
                                                     + 
                                                     ((IData)(vlSelfRef.aes_top__DOT__round_num) 
                                                      << 2U))))
                                              ? vlSelfRef.aes_top__DOT__u_ksi__DOT__w
                                             [(0x0000003fU 
                                               & ((IData)(2U) 
                                                  + 
                                                  ((IData)(vlSelfRef.aes_top__DOT__round_num) 
                                                   << 2U)))]
                                              : 0U);
    vlSelfRef.aes_top__DOT__round_key[2U] = ((0x2bU 
                                              >= (0x0000003fU 
                                                  & ((IData)(1U) 
                                                     + 
                                                     ((IData)(vlSelfRef.aes_top__DOT__round_num) 
                                                      << 2U))))
                                              ? vlSelfRef.aes_top__DOT__u_ksi__DOT__w
                                             [(0x0000003fU 
                                               & ((IData)(1U) 
                                                  + 
                                                  ((IData)(vlSelfRef.aes_top__DOT__round_num) 
                                                   << 2U)))]
                                              : 0U);
    vlSelfRef.aes_top__DOT__round_key[3U] = ((0x2bU 
                                              >= ((IData)(vlSelfRef.aes_top__DOT__round_num) 
                                                  << 2U))
                                              ? vlSelfRef.aes_top__DOT__u_ksi__DOT__w
                                             [((IData)(vlSelfRef.aes_top__DOT__round_num) 
                                               << 2U)]
                                              : 0U);
}

void Vaes_top___024root___nba_sequent__TOP__3(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___nba_sequent__TOP__3\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.aes_top__DOT__round_num = vlSelfRef.__Vdly__aes_top__DOT__round_num;
    if (vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v0) {
        vlSelfRef.aes_top__DOT__u_ksi__DOT__w[0U] = vlSelfRef.__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v0;
    }
    if (vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v1) {
        vlSelfRef.aes_top__DOT__u_ksi__DOT__w[1U] = vlSelfRef.__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v1;
    }
    if (vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v2) {
        vlSelfRef.aes_top__DOT__u_ksi__DOT__w[2U] = vlSelfRef.__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v2;
    }
    if (vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v3) {
        vlSelfRef.aes_top__DOT__u_ksi__DOT__w[3U] = vlSelfRef.__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v3;
    }
    if (vlSelfRef.__VdlySet__aes_top__DOT__u_ksi__DOT__w__v4) {
        vlSelfRef.aes_top__DOT__u_ksi__DOT__w[vlSelfRef.__VdlyDim0__aes_top__DOT__u_ksi__DOT__w__v4] 
            = vlSelfRef.__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v4;
    }
    if (vlSelfRef.aes_top__DOT__u_ksi__DOT__expanding) {
        vlSelfRef.aes_top__DOT__u_ksi__DOT__w_nk = 
            ((0x2bU >= (0x0000003fU & ((IData)(vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx) 
                                       - (IData)(4U))))
              ? vlSelfRef.aes_top__DOT__u_ksi__DOT__w
             [(0x0000003fU & ((IData)(vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx) 
                              - (IData)(4U)))] : 0U);
        vlSelfRef.aes_top__DOT__u_ksi__DOT__w_prev 
            = ((0x2bU >= (0x0000003fU & ((IData)(vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx) 
                                         - (IData)(1U))))
                ? vlSelfRef.aes_top__DOT__u_ksi__DOT__w
               [(0x0000003fU & ((IData)(vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx) 
                                - (IData)(1U)))] : 0U);
    } else {
        vlSelfRef.aes_top__DOT__u_ksi__DOT__w_nk = 0U;
        vlSelfRef.aes_top__DOT__u_ksi__DOT__w_prev = 0U;
    }
    vlSelfRef.aes_top__DOT__u_ksi__DOT__sw_in = ((0U 
                                                  == 
                                                  (3U 
                                                   & (IData)(vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx)))
                                                  ? 
                                                 ((vlSelfRef.aes_top__DOT__u_ksi__DOT__w_prev 
                                                   << 8U) 
                                                  | (vlSelfRef.aes_top__DOT__u_ksi__DOT__w_prev 
                                                     >> 0x00000018U))
                                                  : vlSelfRef.aes_top__DOT__u_ksi__DOT__w_prev);
}

void Vaes_top___024root___nba_sequent__TOP__4(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___nba_sequent__TOP__4\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.aes_top__DOT__u_ksi__DOT__new_word = 
        ((0U == (3U & (IData)(vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx)))
          ? ((vlSelfRef.aes_top__DOT__u_ksi__DOT__w_nk 
              ^ ((((IData)(vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0.byte_out) 
                   << 0x00000018U) | ((IData)(vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1.byte_out) 
                                      << 0x00000010U)) 
                 | (((IData)(vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2.byte_out) 
                     << 8U) | (IData)(vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3.byte_out)))) 
             ^ ([&]() {
                    vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i 
                        = (0x0000000fU & ((IData)(vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx) 
                                          >> 2U));
                    vlSelfRef.aes_top__DOT__u_ksi__DOT__rcon__Vstatic__rc 
                        = ((8U & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i))
                            ? ((4U & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i))
                                ? 0U : ((2U & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i))
                                         ? ((1U & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i))
                                             ? 0U : 0x36U)
                                         : ((1U & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i))
                                             ? 0x1bU
                                             : 0x80U)))
                            : ((4U & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i))
                                ? ((2U & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i))
                                    ? ((1U & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i))
                                        ? 0x40U : 0x20U)
                                    : ((1U & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i))
                                        ? 0x10U : 8U))
                                : ((2U & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i))
                                    ? ((1U & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i))
                                        ? 4U : 2U) : 
                                   ((1U & (IData)(vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i))
                                     ? 1U : 0U))));
                    vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__Vfuncout 
                        = ((IData)(vlSelfRef.aes_top__DOT__u_ksi__DOT__rcon__Vstatic__rc) 
                           << 0x00000018U);
                }(), vlSelfRef.__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__Vfuncout))
          : (vlSelfRef.aes_top__DOT__u_ksi__DOT__w_nk 
             ^ vlSelfRef.aes_top__DOT__u_ksi__DOT__w_prev));
}

void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3__0(Vaes_top_sbox* vlSelf);

void Vaes_top___024root___eval_nba(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_nba\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vaes_top___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox));
        Vaes_top___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vaes_top___024root___nba_sequent__TOP__2(vlSelf);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vaes_top___024root___nba_sequent__TOP__3(vlSelf);
        vlSelfRef.__Vm_traceActivity[3U] = 1U;
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0__0((&vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1__0((&vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2__0((&vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3__0((&vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3));
        Vaes_top___024root___nba_sequent__TOP__4(vlSelf);
    }
}

void Vaes_top___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaes_top___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vaes_top___024root___eval_phase__act(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_phase__act\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vaes_top___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaes_top___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vaes_top___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vaes_top___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vaes_top___024root___eval_phase__nba(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_phase__nba\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vaes_top___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vaes_top___024root___eval_nba(vlSelf);
        Vaes_top___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vaes_top___024root___eval(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vaes_top___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("../../aes_top.v", 1, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vaes_top___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("../../aes_top.v", 1, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vaes_top___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vaes_top___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vaes_top___024root___eval_debug_assertions(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_debug_assertions\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst_n & 0xfeU)))) {
        Verilated::overWidthError("rst_n");
    }
    if (VL_UNLIKELY(((vlSelfRef.key_load & 0xfeU)))) {
        Verilated::overWidthError("key_load");
    }
    if (VL_UNLIKELY(((vlSelfRef.enc_start & 0xfeU)))) {
        Verilated::overWidthError("enc_start");
    }
}
#endif  // VL_DEBUG
