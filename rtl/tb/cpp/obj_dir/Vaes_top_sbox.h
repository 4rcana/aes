// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaes_top.h for the primary calling header

#ifndef VERILATED_VAES_TOP_SBOX_H_
#define VERILATED_VAES_TOP_SBOX_H_  // guard

#include "verilated.h"


class Vaes_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaes_top_sbox final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*7:0*/ byte_in;
    CData/*7:0*/ byte_out;

    // INTERNAL VARIABLES
    Vaes_top__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vaes_top_sbox();
    ~Vaes_top_sbox();
    void ctor(Vaes_top__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vaes_top_sbox);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
