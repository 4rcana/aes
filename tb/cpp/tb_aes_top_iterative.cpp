#include <iostream>
#include <iomanip>
#include <cstdint>
#include <string>
#include <vector>

#include "Vaes_top.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vectors.h"

vluint64_t main_time = 0;

void tick(Vaes_top* dut, VerilatedVcdC* tfp) {
    dut->clk = 0; dut->eval();
    if (tfp) tfp->dump(main_time); main_time += 5;
    dut->clk = 1; dut->eval();
    if (tfp) tfp->dump(main_time); main_time += 5;
}

// Global state to track current key in hardware
std::vector<uint32_t> current_hw_key(8, 0xFFFFFFFF); 

bool load_key_if_needed(Vaes_top* dut, VerilatedVcdC* tfp, const uint32_t* new_key) {
    bool match = true;
    for(int i=0; i < (KEY_BITS/32); i++) {
        if(current_hw_key[i] != new_key[i]) match = false;
    }
    if (match) return true; // Key already loaded

    std::cout << "  [Config] Loading new Key..." << std::endl;
    int k_words = KEY_BITS / 32;
    for (int i = 0; i < k_words; i++) {
        dut->key_in[k_words - 1 - i] = new_key[i];
        current_hw_key[i] = new_key[i];
    }
    
    dut->key_load = 1; tick(dut, tfp); dut->key_load = 0;

    int timeout = 0;
    while (!dut->key_ready && timeout < 200) { tick(dut, tfp); timeout++; }
    if (timeout >= 200) {
        std::cout << "  FAIL: key expansion timeout" << std::endl;
        return false;
    }
    return true;
}

bool run_test(Vaes_top* dut, VerilatedVcdC* tfp, const TestVector& v) {
    std::string name(v.name);
    bool is_decrypt = (name.find("Dec") != std::string::npos);
    
    // Check if this vector matches the compiled KEY_BITS
    // (Optional: skip vectors that don't match our current hardware parameter)
    if (name.find(std::to_string(KEY_BITS)) == std::string::npos) {
        // return true; // Uncomment to skip mismatched bit-lengths
    }

    std::cout << "--- " << v.name << " ---" << std::endl;

    // 1. Load key only if it changed (Tests FSM back-to-back capability)
    if (!load_key_if_needed(dut, tfp, v.key)) return false;

    // 2. Start Operation
    if (is_decrypt) {
        for (int i = 0; i < 4; i++) dut->i_ciphertext[3 - i] = v.ct[i];
        dut->dec_start = 1; tick(dut, tfp); dut->dec_start = 0;
        
        int timeout = 0;
        while (!dut->dec_done && timeout < 100) { tick(dut, tfp); timeout++; }
        
        for (int i = 0; i < 4; i++) {
            if (dut->o_plain_text[3 - i] != v.pt[i]) {
                std::cout << "  FAIL: Decryption Mismatch" << std::endl;
                return false;
            }
        }
    } else {
        for (int i = 0; i < 4; i++) dut->i_plaintext[3 - i] = v.pt[i];
        dut->enc_start = 1; tick(dut, tfp); dut->enc_start = 0;

        int timeout = 0;
        while (!dut->enc_done && timeout < 100) { tick(dut, tfp); timeout++; }

        for (int i = 0; i < 4; i++) {
            if (dut->o_ciphertext[3 - i] != v.ct[i]) {
                std::cout << "  FAIL: Encryption Mismatch" << std::endl;
                return false;
            }
        }
    }
    std::cout << "  PASS" << std::endl;
    return true;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    Vaes_top* dut = new Vaes_top;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("aes_top_tb.vcd");

    // Initial hardware reset (ONCE)
    dut->rst_n = 0;
    tick(dut, tfp); tick(dut, tfp);
    dut->rst_n = 1;
    tick(dut, tfp);

    int pass_count = 0;
    for (int i = 0; i < NUM_VECTORS; i++) {
        if (run_test(dut, tfp, vectors[i])) pass_count++;
    }

    std::cout << "Result: " << pass_count << "/" << NUM_VECTORS << " passed." << std::endl;

    tfp->close();
    delete dut;
    return 0;
}
