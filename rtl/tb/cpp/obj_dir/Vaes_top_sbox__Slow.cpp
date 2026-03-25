// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaes_top.h for the primary calling header

#include "Vaes_top__pch.h"

void Vaes_top_sbox___ctor_var_reset(Vaes_top_sbox* vlSelf);

Vaes_top_sbox::Vaes_top_sbox() = default;
Vaes_top_sbox::~Vaes_top_sbox() = default;

void Vaes_top_sbox::ctor(Vaes_top__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vaes_top_sbox___ctor_var_reset(this);
}

void Vaes_top_sbox::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vaes_top_sbox::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
