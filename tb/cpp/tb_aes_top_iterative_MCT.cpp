#include <iostream>
#include <iomanip>
#include <cstdint>
#include <string>
#include <vector>
#include <cstring>

#include "Vaes_top.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vectors.h"

vluint64_t main_time = 0;

// Standard clock tick
void tick(Vaes_top* dut, VerilatedVcdC* tfp) {
    dut->clk = 0; dut->eval();
    if (tfp) tfp->dump(main_time); main_time += 5;
    dut->clk = 1; dut->eval();
    if (tfp) tfp->dump(main_time); main_time += 5;
}

// Global state to track current key in hardware to avoid redundant expansions
std::vector<uint32_t> current_hw_key(8, 0xFFFFFFFF); 

bool load_key_if_needed(Vaes_top* dut, VerilatedVcdC* tfp, const uint32_t* new_key) {
    bool match = true;
    for(int i=0; i < (KEY_BITS/32); i++) {
        if(current_hw_key[i] != new_key[i]) match = false;
    }
    if (match) return true; 

    int k_words = KEY_BITS / 32;
    for (int i = 0; i < k_words; i++) {
        dut->key_in[k_words - 1 - i] = new_key[i];
        current_hw_key[i] = new_key[i];
    }
    
    dut->key_load = 1; tick(dut, tfp); dut->key_load = 0;

    int timeout = 0;
    while (!dut->key_ready && timeout < 500) { tick(dut, tfp); timeout++; }
    if (timeout >= 500) {
        std::cout << "  FAIL: key expansion timeout" << std::endl;
        return false;
    }
    return true;
}

// Helper to print 128-bit values
void print_128(const uint32_t* v) {
    std::cout << std::hex << std::setfill('0');
    for (int i = 0; i < 4; i++) std::cout << std::setw(8) << v[i];
    std::cout << std::dec;
}

bool run_mct_sample(Vaes_top* dut, VerilatedVcdC* tfp, const TestVector& v) {
    std::string name(v.name);
    bool is_decrypt = (name.find("Dec") != std::string::npos);
    
    std::cout << "--- " << v.name << " [MCT 1000 Iterations] ---" << std::endl;

    // 1. Load key (NIST MCT changes keys every 1000 iterations)
    if (!load_key_if_needed(dut, tfp, v.key)) return false;

    // 2. Initialize the recursive buffer
    uint32_t current_val[4];
    for(int i=0; i<4; i++) current_val[i] = is_decrypt ? v.ct[i] : v.pt[i];

    // 3. Perform 1000 recursive iterations
    // Note: Tracing a million cycles can create a massive VCD file. 
    // You might want to pass NULL to tick() here if the file gets too big.
    for (int iter = 0; iter < 1000; iter++) {
        if (is_decrypt) {
            // Set input from previous output
            for (int i = 0; i < 4; i++) dut->i_ciphertext[3 - i] = current_val[i];
            dut->dec_start = 1; tick(dut, tfp); dut->dec_start = 0;

            int timeout = 0;
            while (!dut->dec_done && timeout < 200) { tick(dut, tfp); timeout++; }
            
            // Feed result back for next iteration
            for (int i = 0; i < 4; i++) current_val[i] = dut->o_plain_text[3 - i];
        } else {
            // Set input from previous output
            for (int i = 0; i < 4; i++) dut->i_plaintext[3 - i] = current_val[i];
            dut->enc_start = 1; tick(dut, tfp); dut->enc_start = 0;

            int timeout = 0;
            while (!dut->enc_done && timeout < 200) { tick(dut, tfp); timeout++; }

            // Feed result back for next iteration
            for (int i = 0; i < 4; i++) current_val[i] = dut->o_ciphertext[3 - i];
        }
    }

    // 4. Compare final iteration result with NIST expected value
    const uint32_t* expected = is_decrypt ? v.pt : v.ct;
    bool pass = true;
    for (int i = 0; i < 4; i++) {
        if (current_val[i] != expected[i]) pass = false;
    }

    if (pass) {
        std::cout << "  PASS" << std::endl;
    } else {
        std::cout << "  FAIL!" << std::endl;
        std::cout << "    Expected: "; print_128(expected); std::cout << std::endl;
        std::cout << "    Got     : "; print_128(current_val); std::cout << std::endl;
    }
    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    Vaes_top* dut = new Vaes_top;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    
    // Set trace depth. 99 is deep, but VCD will be huge for MCT.
    dut->trace(tfp, 99);
    tfp->open("aes_mct_tb.vcd");

    // Power-on Reset
    dut->rst_n = 0;
    tick(dut, tfp); tick(dut, tfp);
    dut->rst_n = 1;
    tick(dut, tfp);

    int pass_count = 0;
    
    // NIST MCT files usually have 100 "Samples" (each is 1000 iterations)
    for (int i = 0; i < NUM_VECTORS; i++) {
        if (run_mct_sample(dut, tfp, vectors[i])) {
            pass_count++;
        } else {
            // Optional: Stop on first failure to save time
            // break; 
        }
    }

    std::cout << "\n===============================" << std::endl;
    std::cout << "MCT Results: " << pass_count << "/" << NUM_VECTORS << " samples passed." << std::endl;
    std::cout << "===============================" << std::endl;

    tfp->close();
    delete dut;
    return (pass_count == NUM_VECTORS) ? 0 : 1;
}
