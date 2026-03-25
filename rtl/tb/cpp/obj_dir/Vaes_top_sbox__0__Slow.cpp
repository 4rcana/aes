// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaes_top.h for the primary calling header

#include "Vaes_top__pch.h"

VL_ATTR_COLD void Vaes_top_sbox___ctor_var_reset(Vaes_top_sbox* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaes_top_sbox___ctor_var_reset\n"); );
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->byte_in = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6945550168992394540ull);
    vlSelf->byte_out = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7344353692365043141ull);
}
