// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vaes_top__Syms.h"


void Vaes_top___024root__trace_chg_0_sub_0(Vaes_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vaes_top___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root__trace_chg_0\n"); );
    // Body
    Vaes_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaes_top___024root*>(voidSelf);
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vaes_top___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vaes_top___024root__trace_chg_0_sub_0(Vaes_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root__trace_chg_0_sub_0\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlWide<4>/*127:0*/ __Vtemp_2;
    VlWide<4>/*127:0*/ __Vtemp_4;
    VlWide<4>/*127:0*/ __Vtemp_6;
    VlWide<4>/*127:0*/ __Vtemp_13;
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgWData(oldp+0,(vlSelfRef.aes_top__DOT__round_out),128);
        bufp->chgWData(oldp+4,(vlSelfRef.aes_top__DOT__state),128);
        bufp->chgBit(oldp+8,(vlSelfRef.aes_top__DOT__running));
        bufp->chgCData(oldp+9,(vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx),6);
        bufp->chgBit(oldp+10,(vlSelfRef.aes_top__DOT__u_ksi__DOT__expanding));
        bufp->chgBit(oldp+11,((0U == (3U & (IData)(vlSelfRef.aes_top__DOT__u_ksi__DOT__word_idx)))));
        bufp->chgIData(oldp+12,(vlSelfRef.aes_top__DOT__u_ksi__DOT__j),32);
        __Vtemp_2[0U] = ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox.byte_out) 
                           << 0x00000018U) | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox.byte_out) 
                                              << 0x00000010U)) 
                         | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox.byte_out) 
                             << 8U) | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox.byte_out)));
        __Vtemp_2[1U] = ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox.byte_out) 
                           << 0x00000018U) | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox.byte_out) 
                                              << 0x00000010U)) 
                         | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox.byte_out) 
                             << 8U) | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox.byte_out)));
        __Vtemp_2[2U] = (IData)((((QData)((IData)((
                                                   (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox.byte_out) 
                                                     << 0x00000018U) 
                                                    | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox.byte_out) 
                                                       << 0x00000010U)) 
                                                   | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox.byte_out) 
                                                       << 8U) 
                                                      | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox.byte_out))))) 
                                  << 0x00000020U) | (QData)((IData)(
                                                                    ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox.byte_out) 
                                                                       << 0x00000018U) 
                                                                      | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox.byte_out) 
                                                                         << 0x00000010U)) 
                                                                     | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox.byte_out) 
                                                                         << 8U) 
                                                                        | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox.byte_out)))))));
        __Vtemp_2[3U] = (IData)(((((QData)((IData)(
                                                   ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox.byte_out) 
                                                      << 0x00000018U) 
                                                     | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox.byte_out) 
                                                        << 0x00000010U)) 
                                                    | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox.byte_out) 
                                                        << 8U) 
                                                       | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox.byte_out))))) 
                                   << 0x00000020U) 
                                  | (QData)((IData)(
                                                    ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox.byte_out) 
                                                       << 0x00000018U) 
                                                      | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox.byte_out) 
                                                         << 0x00000010U)) 
                                                     | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox.byte_out) 
                                                         << 8U) 
                                                        | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox.byte_out)))))) 
                                 >> 0x00000020U));
        bufp->chgWData(oldp+13,(__Vtemp_2),128);
        __Vtemp_4[0U] = ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox.byte_out) 
                           << 0x00000018U) | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox.byte_out) 
                                              << 0x00000010U)) 
                         | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox.byte_out) 
                             << 8U) | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox.byte_out)));
        __Vtemp_4[1U] = ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox.byte_out) 
                           << 0x00000018U) | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox.byte_out) 
                                              << 0x00000010U)) 
                         | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox.byte_out) 
                             << 8U) | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox.byte_out)));
        __Vtemp_4[2U] = (IData)((((QData)((IData)((
                                                   (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox.byte_out) 
                                                     << 0x00000018U) 
                                                    | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox.byte_out) 
                                                       << 0x00000010U)) 
                                                   | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox.byte_out) 
                                                       << 8U) 
                                                      | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox.byte_out))))) 
                                  << 0x00000020U) | (QData)((IData)(
                                                                    ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox.byte_out) 
                                                                       << 0x00000018U) 
                                                                      | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox.byte_out) 
                                                                         << 0x00000010U)) 
                                                                     | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox.byte_out) 
                                                                         << 8U) 
                                                                        | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox.byte_out)))))));
        __Vtemp_4[3U] = (IData)(((((QData)((IData)(
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
                                 >> 0x00000020U));
        bufp->chgWData(oldp+17,(__Vtemp_4),128);
        __Vtemp_6[0U] = vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__3__KET____DOT__u_col__out;
        __Vtemp_6[1U] = vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__2__KET____DOT__u_col__out;
        __Vtemp_6[2U] = (IData)((((QData)((IData)(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out)) 
                                  << 0x00000020U) | (QData)((IData)(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out))));
        __Vtemp_6[3U] = (IData)(((((QData)((IData)(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out)) 
                                   << 0x00000020U) 
                                  | (QData)((IData)(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out))) 
                                 >> 0x00000020U));
        bufp->chgWData(oldp+21,(__Vtemp_6),128);
        bufp->chgIData(oldp+25,(((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox.byte_out) 
                                   << 0x00000018U) 
                                  | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox.byte_out) 
                                     << 0x00000010U)) 
                                 | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox.byte_out) 
                                     << 8U) | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox.byte_out)))),32);
        bufp->chgIData(oldp+26,(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out),32);
        bufp->chgCData(oldp+27,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+28,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+29,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+30,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox.byte_out),8);
        bufp->chgIData(oldp+31,(((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox.byte_out) 
                                   << 0x00000018U) 
                                  | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox.byte_out) 
                                     << 0x00000010U)) 
                                 | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox.byte_out) 
                                     << 8U) | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox.byte_out)))),32);
        bufp->chgIData(oldp+32,(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out),32);
        bufp->chgCData(oldp+33,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+34,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+35,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+36,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox.byte_out),8);
        bufp->chgIData(oldp+37,(((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox.byte_out) 
                                   << 0x00000018U) 
                                  | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox.byte_out) 
                                     << 0x00000010U)) 
                                 | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox.byte_out) 
                                     << 8U) | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox.byte_out)))),32);
        bufp->chgIData(oldp+38,(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__2__KET____DOT__u_col__out),32);
        bufp->chgCData(oldp+39,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+40,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+41,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+42,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox.byte_out),8);
        bufp->chgIData(oldp+43,(((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox.byte_out) 
                                   << 0x00000018U) 
                                  | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox.byte_out) 
                                     << 0x00000010U)) 
                                 | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox.byte_out) 
                                     << 8U) | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox.byte_out)))),32);
        bufp->chgIData(oldp+44,(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__3__KET____DOT__u_col__out),32);
        bufp->chgCData(oldp+45,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+46,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+47,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+48,(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox.byte_out),8);
        bufp->chgCData(oldp+49,((vlSelfRef.aes_top__DOT__state[3U] 
                                 >> 0x00000018U)),8);
        bufp->chgCData(oldp+50,((0x000000ffU & (vlSelfRef.aes_top__DOT__state[3U] 
                                                >> 0x00000010U))),8);
        bufp->chgCData(oldp+51,((0x000000ffU & (vlSelfRef.aes_top__DOT__state[3U] 
                                                >> 8U))),8);
        bufp->chgCData(oldp+52,((0x000000ffU & vlSelfRef.aes_top__DOT__state[3U])),8);
        bufp->chgCData(oldp+53,((vlSelfRef.aes_top__DOT__state[2U] 
                                 >> 0x00000018U)),8);
        bufp->chgCData(oldp+54,((0x000000ffU & (vlSelfRef.aes_top__DOT__state[2U] 
                                                >> 0x00000010U))),8);
        bufp->chgCData(oldp+55,((0x000000ffU & (vlSelfRef.aes_top__DOT__state[2U] 
                                                >> 8U))),8);
        bufp->chgCData(oldp+56,((0x000000ffU & vlSelfRef.aes_top__DOT__state[2U])),8);
        bufp->chgCData(oldp+57,((vlSelfRef.aes_top__DOT__state[1U] 
                                 >> 0x00000018U)),8);
        bufp->chgCData(oldp+58,((0x000000ffU & (vlSelfRef.aes_top__DOT__state[1U] 
                                                >> 0x00000010U))),8);
        bufp->chgCData(oldp+59,((0x000000ffU & (vlSelfRef.aes_top__DOT__state[1U] 
                                                >> 8U))),8);
        bufp->chgCData(oldp+60,((0x000000ffU & vlSelfRef.aes_top__DOT__state[1U])),8);
        bufp->chgCData(oldp+61,((vlSelfRef.aes_top__DOT__state[0U] 
                                 >> 0x00000018U)),8);
        bufp->chgCData(oldp+62,((0x000000ffU & (vlSelfRef.aes_top__DOT__state[0U] 
                                                >> 0x00000010U))),8);
        bufp->chgCData(oldp+63,((0x000000ffU & (vlSelfRef.aes_top__DOT__state[0U] 
                                                >> 8U))),8);
        bufp->chgCData(oldp+64,((0x000000ffU & vlSelfRef.aes_top__DOT__state[0U])),8);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[2U]))) {
        bufp->chgWData(oldp+65,(vlSelfRef.aes_top__DOT__round_key),128);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[3U]))) {
        bufp->chgCData(oldp+69,(vlSelfRef.aes_top__DOT__round_num),4);
        bufp->chgCData(oldp+70,(vlSelfRef.aes_top__DOT__u_ksi__DOT__rcon__Vstatic__rc),8);
        bufp->chgIData(oldp+71,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[0]),32);
        bufp->chgIData(oldp+72,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[1]),32);
        bufp->chgIData(oldp+73,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[2]),32);
        bufp->chgIData(oldp+74,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[3]),32);
        bufp->chgIData(oldp+75,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[4]),32);
        bufp->chgIData(oldp+76,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[5]),32);
        bufp->chgIData(oldp+77,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[6]),32);
        bufp->chgIData(oldp+78,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[7]),32);
        bufp->chgIData(oldp+79,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[8]),32);
        bufp->chgIData(oldp+80,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[9]),32);
        bufp->chgIData(oldp+81,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[10]),32);
        bufp->chgIData(oldp+82,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[11]),32);
        bufp->chgIData(oldp+83,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[12]),32);
        bufp->chgIData(oldp+84,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[13]),32);
        bufp->chgIData(oldp+85,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[14]),32);
        bufp->chgIData(oldp+86,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[15]),32);
        bufp->chgIData(oldp+87,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[16]),32);
        bufp->chgIData(oldp+88,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[17]),32);
        bufp->chgIData(oldp+89,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[18]),32);
        bufp->chgIData(oldp+90,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[19]),32);
        bufp->chgIData(oldp+91,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[20]),32);
        bufp->chgIData(oldp+92,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[21]),32);
        bufp->chgIData(oldp+93,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[22]),32);
        bufp->chgIData(oldp+94,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[23]),32);
        bufp->chgIData(oldp+95,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[24]),32);
        bufp->chgIData(oldp+96,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[25]),32);
        bufp->chgIData(oldp+97,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[26]),32);
        bufp->chgIData(oldp+98,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[27]),32);
        bufp->chgIData(oldp+99,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[28]),32);
        bufp->chgIData(oldp+100,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[29]),32);
        bufp->chgIData(oldp+101,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[30]),32);
        bufp->chgIData(oldp+102,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[31]),32);
        bufp->chgIData(oldp+103,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[32]),32);
        bufp->chgIData(oldp+104,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[33]),32);
        bufp->chgIData(oldp+105,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[34]),32);
        bufp->chgIData(oldp+106,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[35]),32);
        bufp->chgIData(oldp+107,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[36]),32);
        bufp->chgIData(oldp+108,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[37]),32);
        bufp->chgIData(oldp+109,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[38]),32);
        bufp->chgIData(oldp+110,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[39]),32);
        bufp->chgIData(oldp+111,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[40]),32);
        bufp->chgIData(oldp+112,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[41]),32);
        bufp->chgIData(oldp+113,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[42]),32);
        bufp->chgIData(oldp+114,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w[43]),32);
        bufp->chgIData(oldp+115,(vlSelfRef.aes_top__DOT__u_ksi__DOT__sw_in),32);
        bufp->chgIData(oldp+116,(((((IData)(vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0.byte_out) 
                                    << 0x00000018U) 
                                   | ((IData)(vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1.byte_out) 
                                      << 0x00000010U)) 
                                  | (((IData)(vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2.byte_out) 
                                      << 8U) | (IData)(vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3.byte_out)))),32);
        bufp->chgIData(oldp+117,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w_prev),32);
        bufp->chgIData(oldp+118,(vlSelfRef.aes_top__DOT__u_ksi__DOT__w_nk),32);
        bufp->chgIData(oldp+119,(((vlSelfRef.aes_top__DOT__u_ksi__DOT__w_prev 
                                   << 8U) | (vlSelfRef.aes_top__DOT__u_ksi__DOT__w_prev 
                                             >> 0x00000018U))),32);
        bufp->chgIData(oldp+120,(vlSelfRef.aes_top__DOT__u_ksi__DOT__new_word),32);
        bufp->chgCData(oldp+121,(((IData)(vlSelfRef.aes_top__DOT__round_num) 
                                  << 2U)),6);
        bufp->chgBit(oldp+122,((0x0aU == (IData)(vlSelfRef.aes_top__DOT__round_num))));
        bufp->chgCData(oldp+123,((vlSelfRef.aes_top__DOT__u_ksi__DOT__sw_in 
                                  >> 0x00000018U)),8);
        bufp->chgCData(oldp+124,(vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0.byte_out),8);
        bufp->chgCData(oldp+125,((0x000000ffU & (vlSelfRef.aes_top__DOT__u_ksi__DOT__sw_in 
                                                 >> 0x00000010U))),8);
        bufp->chgCData(oldp+126,(vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1.byte_out),8);
        bufp->chgCData(oldp+127,((0x000000ffU & (vlSelfRef.aes_top__DOT__u_ksi__DOT__sw_in 
                                                 >> 8U))),8);
        bufp->chgCData(oldp+128,(vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2.byte_out),8);
        bufp->chgCData(oldp+129,((0x000000ffU & vlSelfRef.aes_top__DOT__u_ksi__DOT__sw_in)),8);
        bufp->chgCData(oldp+130,(vlSymsp->TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3.byte_out),8);
    }
    bufp->chgBit(oldp+131,(vlSelfRef.clk));
    bufp->chgBit(oldp+132,(vlSelfRef.rst_n));
    bufp->chgBit(oldp+133,(vlSelfRef.key_load));
    bufp->chgWData(oldp+134,(vlSelfRef.key_in),128);
    bufp->chgBit(oldp+138,(vlSelfRef.enc_start));
    bufp->chgWData(oldp+139,(vlSelfRef.plaintext),128);
    bufp->chgBit(oldp+143,(vlSelfRef.key_ready));
    bufp->chgWData(oldp+144,(vlSelfRef.ciphertext),128);
    bufp->chgBit(oldp+148,(vlSelfRef.enc_done));
    __Vtemp_13[0U] = (((0x0aU == (IData)(vlSelfRef.aes_top__DOT__round_num))
                        ? ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox.byte_out) 
                             << 0x00000018U) | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox.byte_out) 
                                                << 0x00000010U)) 
                           | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox.byte_out) 
                               << 8U) | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox.byte_out)))
                        : vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__3__KET____DOT__u_col__out) 
                      ^ vlSelfRef.aes_top__DOT__round_key[0U]);
    __Vtemp_13[1U] = (((0x0aU == (IData)(vlSelfRef.aes_top__DOT__round_num))
                        ? ((((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox.byte_out) 
                             << 0x00000018U) | ((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox.byte_out) 
                                                << 0x00000010U)) 
                           | (((IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox.byte_out) 
                               << 8U) | (IData)(vlSymsp->TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox.byte_out)))
                        : vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__2__KET____DOT__u_col__out) 
                      ^ vlSelfRef.aes_top__DOT__round_key[1U]);
    __Vtemp_13[2U] = (((0x0aU == (IData)(vlSelfRef.aes_top__DOT__round_num))
                        ? (IData)((((QData)((IData)(
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
                        : (IData)((((QData)((IData)(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out)) 
                                    << 0x00000020U) 
                                   | (QData)((IData)(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out))))) 
                      ^ vlSelfRef.aes_top__DOT__round_key[2U]);
    __Vtemp_13[3U] = (((0x0aU == (IData)(vlSelfRef.aes_top__DOT__round_num))
                        ? (IData)(((((QData)((IData)(
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
                        : (IData)(((((QData)((IData)(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out)) 
                                     << 0x00000020U) 
                                    | (QData)((IData)(vlSelfRef.aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out))) 
                                   >> 0x00000020U))) 
                      ^ vlSelfRef.aes_top__DOT__round_key[3U]);
    bufp->chgWData(oldp+149,(__Vtemp_13),128);
}

void Vaes_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top___024root__trace_cleanup\n"); );
    // Body
    Vaes_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaes_top___024root*>(voidSelf);
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
}
