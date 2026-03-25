// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaes_top.h for the primary calling header

#include "Vaes_top__pch.h"

void Vaes_top___024root___ctor_var_reset(Vaes_top___024root* vlSelf);

Vaes_top___024root::Vaes_top___024root(Vaes_top__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vaes_top___024root___ctor_var_reset(this);
}

void Vaes_top___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vaes_top___024root::~Vaes_top___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
