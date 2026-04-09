#include <iostream>
#include <vector>
#include <string>
#include "Vaes_top.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vectors.h"

vluint64_t main_time = 0;
std::vector<uint32_t> current_hw_key(8, 0xFFFFFFFF);

void tick(Vaes_top* dut, VerilatedVcdC* tfp) {
    dut->clk = 0; dut->eval(); if (tfp) tfp->dump(main_time); main_time += 5;
    dut->clk = 1; dut->eval(); if (tfp) tfp->dump(main_time); main_time += 5;
}

void load_key(Vaes_top* dut, VerilatedVcdC* tfp, const uint32_t* key) {
    bool match = true;
    for(int i=0; i<(KEY_BITS/32); i++) if(current_hw_key[i] != key[i]) match = false;
    if (match) return;

    int k_words = KEY_BITS/32;
    for (int i=0; i<k_words; i++) {
        dut->key_in[k_words-1-i] = key[i];
        current_hw_key[i] = key[i];
    }
    dut->key_load = 1; tick(dut, tfp); dut->key_load = 0;
    int timeout = 0;
    while (!dut->key_ready && timeout++ < 500) tick(dut, tfp);
}

void load_iv(Vaes_top* dut, VerilatedVcdC* tfp, const uint32_t* iv) {
    for (int i=0; i<4; i++) dut->iv_in[3-i] = iv[i];
    dut->iv_load = 1; tick(dut, tfp); dut->iv_load = 0;
    tick(dut, tfp); // Extra cycle for sync
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    Vaes_top* dut = new Vaes_top;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99); tfp->open("sim.vcd");

    // Power-on Reset
    dut->rst_n = 0; tick(dut, tfp); tick(dut, tfp); dut->rst_n = 1; tick(dut, tfp);

    int pass_count = 0;
    for (int i = 0; i < NUM_VECTORS; i++) {
        const TestVector& v = vectors[i];
        std::string name(v.name);
        bool is_dec = (name.find("Dec") != std::string::npos);
        bool is_mct = (name.find("[MCT]") != std::string::npos);
        bool is_b0  = (name.find("B0") != std::string::npos); // First block of message

        load_key(dut, tfp, v.key);
        
        // In CBC, we load the IV at the start of a message (B0) or for single KATs
        if (is_b0) load_iv(dut, tfp, v.iv);

        int iters = is_mct ? 1000 : 1;
        uint32_t buf[4];
        for(int j=0; j<4; j++) buf[j] = is_dec ? v.ct[j] : v.pt[j];

        for(int j=0; j < iters; j++) {
            if (is_dec) {
                for (int k=0; k<4; k++) dut->i_ciphertext[3-k] = buf[k];
                dut->dec_start = 1; tick(dut, tfp); dut->dec_start = 0;
                while (!dut->dec_done) tick(dut, tfp);
                for (int k=0; k<4; k++) buf[k] = dut->o_plaintext[3-k];
            } else {
                for (int k=0; k<4; k++) dut->i_plaintext[3-k] = buf[k];
                dut->enc_start = 1; tick(dut, tfp); dut->enc_start = 0;
                while (!dut->enc_done) tick(dut, tfp);
                for (int k=0; k<4; k++) buf[k] = dut->o_ciphertext[3-k];
            }
        }

        bool match = true;
        const uint32_t* exp = is_dec ? v.pt : v.ct;
        for(int j=0; j<4; j++) if(buf[j] != exp[j]) match = false;

        if (match) { pass_count++; std::cout << "PASS: " << name << "\n"; }
        else { std::cout << "FAIL: " << name << "\n"; }
    }

    std::cout << "\nFinal: " << pass_count << "/" << NUM_VECTORS << " passed.\n";
    tfp->close(); return 0;
}
