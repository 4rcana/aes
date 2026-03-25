// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VAES_TOP__SYMS_H_
#define VERILATED_VAES_TOP__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vaes_top.h"

// INCLUDE MODULE CLASSES
#include "Vaes_top___024root.h"
#include "Vaes_top_sbox.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vaes_top__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vaes_top* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vaes_top___024root             TOP;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox;
    Vaes_top_sbox                  TOP__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox;

    // CONSTRUCTORS
    Vaes_top__Syms(VerilatedContext* contextp, const char* namep, Vaes_top* modelp);
    ~Vaes_top__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
