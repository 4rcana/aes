// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vaes_top__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vaes_top::Vaes_top(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vaes_top__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , key_load{vlSymsp->TOP.key_load}
    , enc_start{vlSymsp->TOP.enc_start}
    , key_ready{vlSymsp->TOP.key_ready}
    , enc_done{vlSymsp->TOP.enc_done}
    , key_in{vlSymsp->TOP.key_in}
    , plaintext{vlSymsp->TOP.plaintext}
    , ciphertext{vlSymsp->TOP.ciphertext}
    , __PVT__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0{vlSymsp->TOP.__PVT__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u0}
    , __PVT__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1{vlSymsp->TOP.__PVT__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u1}
    , __PVT__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2{vlSymsp->TOP.__PVT__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u2}
    , __PVT__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3{vlSymsp->TOP.__PVT__aes_top__DOT__u_ksi__DOT__u_sw__DOT__u3}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__0__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__1__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__2__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__3__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__4__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__5__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__6__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__7__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__8__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__9__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__10__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__11__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__12__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__13__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__14__KET____DOT__u_sbox}
    , __PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox{vlSymsp->TOP.__PVT__aes_top__DOT__u_round__DOT__u_sub__DOT__sbox_inst__BRA__15__KET____DOT__u_sbox}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vaes_top::Vaes_top(const char* _vcname__)
    : Vaes_top(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vaes_top::~Vaes_top() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vaes_top___024root___eval_debug_assertions(Vaes_top___024root* vlSelf);
#endif  // VL_DEBUG
void Vaes_top___024root___eval_static(Vaes_top___024root* vlSelf);
void Vaes_top___024root___eval_initial(Vaes_top___024root* vlSelf);
void Vaes_top___024root___eval_settle(Vaes_top___024root* vlSelf);
void Vaes_top___024root___eval(Vaes_top___024root* vlSelf);

void Vaes_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vaes_top::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vaes_top___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vaes_top___024root___eval_static(&(vlSymsp->TOP));
        Vaes_top___024root___eval_initial(&(vlSymsp->TOP));
        Vaes_top___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vaes_top___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vaes_top::eventsPending() { return false; }

uint64_t Vaes_top::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vaes_top::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vaes_top___024root___eval_final(Vaes_top___024root* vlSelf);

VL_ATTR_COLD void Vaes_top::final() {
    Vaes_top___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vaes_top::hierName() const { return vlSymsp->name(); }
const char* Vaes_top::modelName() const { return "Vaes_top"; }
unsigned Vaes_top::threads() const { return 1; }
void Vaes_top::prepareClone() const { contextp()->prepareClone(); }
void Vaes_top::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vaes_top::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vaes_top___024root__trace_decl_types(VerilatedVcd* tracep);

void Vaes_top___024root__trace_init_top(Vaes_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vaes_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaes_top___024root*>(voidSelf);
    Vaes_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vaes_top___024root__trace_decl_types(tracep);
    Vaes_top___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vaes_top___024root__trace_register(Vaes_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vaes_top::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vaes_top::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 158);
    Vaes_top___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
