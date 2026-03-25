// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaes_top.h for the primary calling header

#ifndef VERILATED_VAES_TOP___024ROOT_H_
#define VERILATED_VAES_TOP___024ROOT_H_  // guard

#include "verilated.h"
class Vaes_top_sbox;


class Vaes_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaes_top___024root final {
  public:
    // CELLS
    Vaes_top_sbox* __PVT__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox;
    Vaes_top_sbox* __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox;

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst_n,0,0);
        VL_IN8(key_load,0,0);
        VL_IN8(enc_start,0,0);
        VL_OUT8(key_ready,0,0);
        VL_OUT8(enc_done,0,0);
        CData/*3:0*/ aes_top__DOT__round_num;
        CData/*0:0*/ aes_top__DOT__running;
        CData/*7:0*/ aes_top__DOT__u_ksi__DOT__rcon__Vstatic__rc;
        CData/*5:0*/ aes_top__DOT__u_ksi__DOT__word_idx;
        CData/*0:0*/ aes_top__DOT__u_ksi__DOT__expanding;
        CData/*3:0*/ __Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__i;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__1__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__1__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__2__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__2__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__3__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__3__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__4__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__4__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__5__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__5__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__6__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__6__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__7__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__7__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__8__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__0__KET____DOT__u_col__DOT__xtime__8__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__9__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__9__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__10__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__10__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__11__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__11__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__12__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__12__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__13__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__13__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__14__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__14__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__15__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__15__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__16__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__1__KET____DOT__u_col__DOT__xtime__16__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__17__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__17__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__18__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__18__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__19__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__19__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__20__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__20__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__21__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__21__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__22__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__22__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__23__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__23__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__24__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__2__KET____DOT__u_col__DOT__xtime__24__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__25__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__25__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__26__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__26__b;
    };
    struct {
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__27__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__27__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__28__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__28__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__29__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__29__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__30__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__30__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__31__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__31__b;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__32__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_top__DOT__u_round__DOT__u_mix__DOT__mc_col__BRA__3__KET____DOT__u_col__DOT__xtime__32__b;
        CData/*3:0*/ __Vdly__aes_top__DOT__round_num;
        CData/*0:0*/ __VdlySet__aes_top__DOT__u_ksi__DOT__w__v0;
        CData/*0:0*/ __VdlySet__aes_top__DOT__u_ksi__DOT__w__v1;
        CData/*0:0*/ __VdlySet__aes_top__DOT__u_ksi__DOT__w__v2;
        CData/*0:0*/ __VdlySet__aes_top__DOT__u_ksi__DOT__w__v3;
        CData/*5:0*/ __VdlyDim0__aes_top__DOT__u_ksi__DOT__w__v4;
        CData/*0:0*/ __VdlySet__aes_top__DOT__u_ksi__DOT__w__v4;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        VL_INW(key_in,127,0,4);
        VL_INW(plaintext,127,0,4);
        VL_OUTW(ciphertext,127,0,4);
        VlWide<4>/*127:0*/ aes_top__DOT__round_key;
        VlWide<4>/*127:0*/ aes_top__DOT__round_out;
        VlWide<4>/*127:0*/ aes_top__DOT__state;
        IData/*31:0*/ aes_top__DOT__u_ksi__DOT____Vlvbound_h94f983f0__0;
        IData/*31:0*/ aes_top__DOT__u_ksi__DOT____Vlvbound_h2d2a71e7__0;
        IData/*31:0*/ aes_top__DOT__u_ksi__DOT__sw_in;
        IData/*31:0*/ aes_top__DOT__u_ksi__DOT__w_prev;
        IData/*31:0*/ aes_top__DOT__u_ksi__DOT__w_nk;
        IData/*31:0*/ aes_top__DOT__u_ksi__DOT__new_word;
        IData/*31:0*/ aes_top__DOT__u_ksi__DOT__j;
        IData/*31:0*/ aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__0__KET____DOT__u_col__out;
        IData/*31:0*/ aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__1__KET____DOT__u_col__out;
        IData/*31:0*/ aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__2__KET____DOT__u_col__out;
        IData/*31:0*/ aes_top__DOT__u_round__DOT__u_mix__DOT____Vcellout__mc_col__BRA__3__KET____DOT__u_col__out;
        IData/*31:0*/ __Vfunc_aes_top__DOT__u_ksi__DOT__rcon__0__Vfuncout;
        IData/*31:0*/ __VdlyVal__aes_top__DOT__u_ksi__DOT__w__v0;
        IData/*31:0*/ __VdlyVal__aes_top__DOT__u_ksi__DOT__w__v1;
        IData/*31:0*/ __VdlyVal__aes_top__DOT__u_ksi__DOT__w__v2;
        IData/*31:0*/ __VdlyVal__aes_top__DOT__u_ksi__DOT__w__v3;
        IData/*31:0*/ __VdlyVal__aes_top__DOT__u_ksi__DOT__w__v4;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<IData/*31:0*/, 44> aes_top__DOT__u_ksi__DOT__w;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
        VlUnpacked<CData/*0:0*/, 4> __Vm_traceActivity;
    };

    // INTERNAL VARIABLES
    Vaes_top__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vaes_top___024root(Vaes_top__Syms* symsp, const char* namep);
    ~Vaes_top___024root();
    VL_UNCOPYABLE(Vaes_top___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
