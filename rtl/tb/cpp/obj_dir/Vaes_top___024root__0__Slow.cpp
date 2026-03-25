// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaes_top.h for the primary calling header

#include "Vaes_top__pch.h"

VL_ATTR_COLD void Vaes_top___024root___eval_static__TOP(Vaes_top___024root* vlSelf);
VL_ATTR_COLD void Vaes_top___024root____Vm_traceActivitySetAll(Vaes_top___024root* vlSelf);

VL_ATTR_COLD void Vaes_top___024root___eval_static(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_static\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vaes_top___024root___eval_static__TOP(vlSelf);
    Vaes_top___024root____Vm_traceActivitySetAll(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

VL_ATTR_COLD void Vaes_top___024root___eval_static__TOP(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_static__TOP\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->aes_top__DOT__u_ksi__DOT__rcon__Vstatic__rc = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6426651070341820526ull);
}

VL_ATTR_COLD void Vaes_top___024root___eval_initial(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_initial\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vaes_top___024root___eval_final(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_final\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaes_top___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vaes_top___024root___eval_phase__stl(Vaes_top___024root* vlSelf);

VL_ATTR_COLD void Vaes_top___024root___eval_settle(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_settle\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vaes_top___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("../../aes_top.v", 1, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vaes_top___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vaes_top___024root___eval_triggers_vec__stl(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_triggers_vec__stl\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vaes_top___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaes_top___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vaes_top___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vaes_top___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vaes_top___024root___stl_sequent__TOP__0(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___stl_sequent__TOP__0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
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

VL_ATTR_COLD void Vaes_top___024root___stl_sequent__TOP__1(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___stl_sequent__TOP__1\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
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
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2__0(Vaes_top_sbox* vlSelf);
void Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3__0(Vaes_top_sbox* vlSelf);

VL_ATTR_COLD void Vaes_top___024root___eval_stl(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_stl\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vaes_top___024root___stl_sequent__TOP__0(vlSelf);
        Vaes_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox__0((&vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0__0((&vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1__0((&vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2__0((&vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2));
        Vaes_top_sbox___nba_sequent__TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3__0((&vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3));
        Vaes_top___024root___stl_sequent__TOP__1(vlSelf);
    }
}

VL_ATTR_COLD bool Vaes_top___024root___eval_phase__stl(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___eval_phase__stl\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vaes_top___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaes_top___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vaes_top___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vaes_top___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vaes_top___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaes_top___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vaes_top___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vaes_top___024root____Vm_traceActivitySetAll(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root____Vm_traceActivitySetAll\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.__Vm_traceActivity[3U] = 1U;
}

VL_ATTR_COLD void Vaes_top___024root___ctor_var_reset(Vaes_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root___ctor_var_reset\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1638864771569018232ull);
    vlSelf->key_load = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13420099715390458109ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->key_in, __VscopeHash, 112244031664460840ull);
    vlSelf->enc_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4919697728394618961ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->plaintext, __VscopeHash, 15306753485699558102ull);
    vlSelf->key_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14166555156929256162ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->ciphertext, __VscopeHash, 5156948722554576173ull);
    vlSelf->enc_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12886564746813552092ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->aes_top__DOT__round_key, __VscopeHash, 8287299446170246729ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->aes_top__DOT__round_out, __VscopeHash, 15619377118452214423ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->aes_top__DOT__state, __VscopeHash, 7090820808299688214ull);
    vlSelf->aes_top__DOT__round_num = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 14928177237054049818ull);
    vlSelf->aes_top__DOT__running = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13914389680612097776ull);
    vlSelf->aes_top__DOT__u_ksi__DOT____Vlvbound_h94f983f0__0 = 0;
    vlSelf->aes_top__DOT__u_ksi__DOT____Vlvbound_h2d2a71e7__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 44; ++__Vi0) {
        vlSelf->aes_top__DOT__u_ksi__DOT__w[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13600596324892821693ull);
    }
    vlSelf->aes_top__DOT__u_ksi__DOT__word_idx = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 10744769623246167330ull);
    vlSelf->aes_top__DOT__u_ksi__DOT__expanding = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11985459032865538235ull);
    vlSelf->aes_top__DOT__u_ksi__DOT__sw_in = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2037605975040734101ull);
    vlSelf->aes_top__DOT__u_ksi__DOT__w_prev = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4002595289987894660ull);
    vlSelf->aes_top__DOT__u_ksi__DOT__w_nk = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4054244294533391062ull);
    vlSelf->aes_top__DOT__u_ksi__DOT__new_word = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11603022623598292612ull);
    vlSelf->aes_top__DOT__u_ksi__DOT__j = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3969270348320506686ull);
    vlSelf->aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out = 0;
    vlSelf->aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out = 0;
    vlSelf->aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__2__KET____DOT__u_col__out = 0;
    vlSelf->aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__3__KET____DOT__u_col__out = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__1__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__1__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__2__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__2__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__3__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__3__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__4__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__4__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__5__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__5__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__6__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__6__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__7__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__7__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__8__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__8__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__9__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__9__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__10__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__10__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__11__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__11__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__12__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__12__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__13__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__13__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__14__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__14__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__15__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__15__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__16__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__16__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__17__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__17__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__18__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__18__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__19__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__19__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__20__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__20__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__21__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__21__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__22__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__22__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__23__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__23__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__24__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__24__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__25__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__25__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__26__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__26__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__27__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__27__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__28__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__28__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__29__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__29__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__30__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__30__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__31__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__31__b = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__32__Vfuncout = 0;
    vlSelf->__Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__32__b = 0;
    vlSelf->__Vdly__aes_top__DOT__round_num = 0;
    vlSelf->__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v0 = 0;
    vlSelf->__VdlySet__aes_top__DOT__u_ksi__DOT__w__v0 = 0;
    vlSelf->__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v1 = 0;
    vlSelf->__VdlySet__aes_top__DOT__u_ksi__DOT__w__v1 = 0;
    vlSelf->__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v2 = 0;
    vlSelf->__VdlySet__aes_top__DOT__u_ksi__DOT__w__v2 = 0;
    vlSelf->__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v3 = 0;
    vlSelf->__VdlySet__aes_top__DOT__u_ksi__DOT__w__v3 = 0;
    vlSelf->__VdlyVal__aes_top__DOT__u_ksi__DOT__w__v4 = 0;
    vlSelf->__VdlyDim0__aes_top__DOT__u_ksi__DOT__w__v4 = 0;
    vlSelf->__VdlySet__aes_top__DOT__u_ksi__DOT__w__v4 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
