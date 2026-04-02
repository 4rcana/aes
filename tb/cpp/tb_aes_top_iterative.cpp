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

// Include generated vectors
#include "vectors.h"

vluint64_t main_time = 0;

// Standard clock tick
void tick(Vaes_top* dut, VerilatedVcdC* tfp) {
    dut->clk = 0; dut->eval();
    if (tfp) tfp->dump(main_time); main_time += 5;
    dut->clk = 1; dut->eval();
    if (tfp) tfp->dump(main_time); main_time += 5;
}

// Print 128-bit array in Big-Endian (Human Readable) hex
void print_128(const uint32_t* v, bool is_dut_output) {
    std::cout << std::hex << std::setfill('0');
    if (is_dut_output) {
        // Verilator arrays are Little-Endian [0]=LSB, so print 3 down to 0
        for (int i = 3; i >= 0; i--) std::cout << std::setw(8) << v[i];
    } else {
        // TestVector arrays are Big-Endian [0]=MSB, so print 0 to 3
        for (int i = 0; i < 4; i++) std::cout << std::setw(8) << v[i];
    }
    std::cout << std::dec;
}

bool run_test(Vaes_top* dut, VerilatedVcdC* tfp, const TestVector& v) {
    std::string name(v.name);
    bool is_decrypt = (name.find("Dec") != std::string::npos);
    
    std::cout << "--- " << v.name << " (" << (is_decrypt ? "DECRYPT" : "ENCRYPT") << ") ---" << std::endl;

    // 1. Reset the core
    dut->rst_n = 0; 
    dut->key_load = 0; 
    dut->enc_start = 0; 
    dut->dec_start = 0;
    tick(dut, tfp); tick(dut, tfp);
    dut->rst_n = 1; tick(dut, tfp);

    // 2. Load Key (Big-Endian struct -> Little-Endian DUT)
    int k_words = KEY_BITS / 32;
    for (int i = 0; i < k_words; i++) {
        dut->key_in[k_words - 1 - i] = v.key[i];
    }
    dut->key_load = 1; tick(dut, tfp); dut->key_load = 0;

    // 3. Wait for Key Scheduler
    int timeout = 0;
    while (!dut->key_ready && timeout < 200) { tick(dut, tfp); timeout++; }
    if (timeout >= 200) {
        std::cout << "  FAIL: key expansion timeout" << std::endl;
        return false;
    }

    // 4. Mode-specific execution
    if (is_decrypt) {
        // Drive Ciphertext to Decrypt lane
        for (int i = 0; i < 4; i++) dut->i_ciphertext[3 - i] = v.ct[i];
        dut->dec_start = 1; tick(dut, tfp); dut->dec_start = 0;

        // Wait for Decryption Done
        timeout = 0;
        while (!dut->dec_done && timeout < 100) { tick(dut, tfp); timeout++; }
        
        // Compare DUT Output Plaintext against Struct v.pt
        bool pass = true;
        for (int i = 0; i < 4; i++) {
            if (dut->o_plain_text[3 - i] != v.pt[i]) pass = false;
        }

        if (pass) {
            std::cout << "  PASS: pt = "; print_128(dut->o_plain_text, true); std::cout << std::endl;
            return true;
        } else {
            std::cout << "  FAIL:\n    expected pt: "; print_128(v.pt, false);
            std::cout << "\n    got pt     : "; print_128(dut->o_plain_text, true);
            std::cout << std::endl;
            return false;
        }
    } 
    else {
        // Drive Plaintext to Encrypt lane
        for (int i = 0; i < 4; i++) dut->i_plaintext[3 - i] = v.pt[i];
        dut->enc_start = 1; tick(dut, tfp); dut->enc_start = 0;

        // Wait for Encryption Done
        timeout = 0;
        while (!dut->enc_done && timeout < 100) { tick(dut, tfp); timeout++; }

        // Compare DUT Output Ciphertext against Struct v.ct
        bool pass = true;
        for (int i = 0; i < 4; i++) {
            if (dut->o_ciphertext[3 - i] != v.ct[i]) pass = false;
        }

        if (pass) {
            std::cout << "  PASS: ct = "; print_128(dut->o_ciphertext, true); std::cout << std::endl;
            return true;
        } else {
            std::cout << "  FAIL:\n    expected ct: "; print_128(v.ct, false);
            std::cout << "\n    got ct     : "; print_128(dut->o_ciphertext, true);
            std::cout << std::endl;
            return false;
        }
    }
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vaes_top* dut = new Vaes_top;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("aes_top_tb.vcd");

    // Initialize all inputs
    dut->rst_n = 0;
    dut->key_load = 0;
    dut->enc_start = 0;
    dut->dec_start = 0;
    for (int i = 0; i < 4; i++) {
        dut->i_plaintext[i] = 0;
        dut->i_ciphertext[i] = 0;
    }
    for (int i = 0; i < 8; i++) dut->key_in[i] = 0;
    
    // Warm up simulation
    for (int i = 0; i < 10; i++) tick(dut, tfp);

    int pass_count = 0, fail_count = 0;

    // NUM_VECTORS is defined in vectors.h by the python script
    for (int i = 0; i < NUM_VECTORS; i++) {
        if (run_test(dut, tfp, vectors[i]))
            pass_count++;
        else
            fail_count++;
        
        // Small gap between tests
        for (int g = 0; g < 5; g++) tick(dut, tfp);
    }

    std::cout << "\n===============================" << std::endl;
    std::cout << "Final Results: " << pass_count << " passed, "
              << fail_count << " failed" << std::endl;
    if (fail_count == 0) 
        std::cout << "SUCCESS: ALL TESTS PASSED" << std::endl;
    else 
        std::cout << "FAILURE: " << fail_count << " TESTS FAILED" << std::endl;
    std::cout << "===============================" << std::endl;

    tfp->close();
    delete dut;
    delete tfp;
    return (fail_count == 0) ? 0 : 1;
}
