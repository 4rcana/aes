#include <iostream>
#include <iomanip>
#include <cstdint>
#include <string>

#include "Vaes_top.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#ifndef KEY_BITS
#define KEY_BITS 128
#endif

#include "vectors.h"

vluint64_t main_time = 0;

void tick(Vaes_top* dut, VerilatedVcdC* tfp) {
    dut->clk = 0; dut->eval();
    if (tfp) tfp->dump(main_time); main_time += 5;
    dut->clk = 1; dut->eval();
    if (tfp) tfp->dump(main_time); main_time += 5;
}

void print_128(const uint32_t* v) {
    std::cout << std::hex << std::setfill('0')
              << std::setw(8) << v[0] << std::setw(8) << v[1]
              << std::setw(8) << v[2] << std::setw(8) << v[3] << std::dec;
}

bool run_test(Vaes_top* dut, VerilatedVcdC* tfp,
              const uint32_t* key, const uint32_t* pt,
              const uint32_t* exp_ct, const char* name)
{
    std::cout << "--- " << name << " ---" << std::endl;

    dut->rst_n = 0; dut->key_load = 0; dut->enc_start = 0;
    tick(dut, tfp); tick(dut, tfp);
    dut->rst_n = 1; tick(dut, tfp);

    for (int i = 0; i < KEY_BITS / 32; i++) dut->key_in[(KEY_BITS / 32) - 1 - i] = key[i];
    dut->key_load = 1; tick(dut, tfp); dut->key_load = 0;

    int timeout = 0;
    while (!dut->key_ready && timeout < 200) { tick(dut, tfp); timeout++; }
    if (timeout >= 200) {
        std::cout << "  FAIL: key expansion timeout" << std::endl;
        return false;
    }

    for (int i = 0; i < 4; i++) dut->plaintext[3-i] = pt[i];
    dut->enc_start = 1; tick(dut, tfp); dut->enc_start = 0;

    timeout = 0;
    while (!dut->enc_done && timeout < 100) { tick(dut, tfp); timeout++; }
    if (timeout >= 100) {
        std::cout << "  FAIL: encryption timeout" << std::endl;
        return false;
    }

    bool pass = true;
    for (int i = 0; i < 4; i++)
        if (dut->ciphertext[3-i] != exp_ct[i]) { pass = false; break; }

    if (pass) {
        std::cout << "  PASS: "; print_128(dut->ciphertext); std::cout << std::endl;
    } else {
        std::cout << "  FAIL:\n    expected : "; print_128(exp_ct);
        std::cout << "\n    got      : "; print_128(dut->ciphertext);
        std::cout << std::endl;
    }
    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vaes_top* dut = new Vaes_top;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("aes_top_tb.vcd");

    // Initialize
    dut->rst_n = 0; dut->key_load = 0; dut->enc_start = 0;
    for (int i = 0; i < 4; i++) dut->plaintext[i] = 0;
    for (int i = 0; i < KEY_BITS/32; i++) dut->key_in[i] = 0;
    for (int i = 0; i < 4; i++) tick(dut, tfp);

    int pass_count = 0, fail_count = 0;

    for (int i = 0; i < NUM_VECTORS; i++) {
        const TestVector& v = vectors[i];
        if (run_test(dut, tfp, v.key, v.pt, v.ct, v.name))
            pass_count++;
        else
            fail_count++;
    }

    std::cout << "===============================" << std::endl;
    std::cout << "Results: " << pass_count << " passed, "
              << fail_count << " failed" << std::endl;
    std::cout << (fail_count == 0 ? "ALL TESTS PASSED" : "FAILURES DETECTED")
              << std::endl;
    std::cout << "===============================" << std::endl;

    dut->eval();
    tfp->close();
    delete dut;
    delete tfp;
    return fail_count == 0 ? 0 : 1;
}
