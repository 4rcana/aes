#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>

// Include the Verilator model and tracing headers
#include "Vaes_top.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

// Define the Key size at compile time, defaulting to 128
#ifndef KEY_BITS
#define KEY_BITS 128
#endif

// Global simulation time
vluint64_t main_time = 0;

// Helper function to advance the clock and dump VCD traces
void tick(Vaes_top* dut, VerilatedVcdC* tfp) {
    dut->clk = 0;
    dut->eval();
    if (tfp) tfp->dump(main_time);
    main_time += 5; // Half-cycle

    dut->clk = 1;
    dut->eval();
    if (tfp) tfp->dump(main_time);
    main_time += 5; // Half-cycle
}

// Helper function to print 128-bit values (array of 4x uint32_t)
void print_128(const uint32_t* val) {
    std::cout << std::hex << std::setfill('0')
              << std::setw(8) << val[3]
              << std::setw(8) << val[2]
              << std::setw(8) << val[1]
              << std::setw(8) << val[0]
              << std::dec;
}

// Single Encryption Test Task
bool run_test(Vaes_top* dut, VerilatedVcdC* tfp, 
              const uint32_t* key, const uint32_t* pt, const uint32_t* expected_ct, 
              int test_id) 
{
    std::cout << "--- Test " << test_id << " (AES-" << KEY_BITS << ") ---" << std::endl;

    // Apply reset
    dut->rst_n = 0;
    dut->key_load = 0;
    dut->enc_start = 0;
    tick(dut, tfp);
    tick(dut, tfp);
    dut->rst_n = 1;
    tick(dut, tfp);

    // Load key (Verilator maps wide signals to arrays of 32-bit integers)
    for (int i = 0; i < KEY_BITS / 32; i++) {
        dut->key_in[i] = key[i];
    }
    dut->key_load = 1;
    tick(dut, tfp);
    dut->key_load = 0;

    // Wait for key expansion to complete
    int timeout = 0;
    while (!dut->key_ready && timeout < 200) {
        tick(dut, tfp);
        timeout++;
    }
    if (timeout >= 200) {
        std::cout << "  FAIL: key expansion timeout" << std::endl;
        return false;
    }
    std::cout << "  Key expanded in " << timeout << " cycles\n";

    // Start encryption
    for (int i = 0; i < 4; i++) {
        dut->plaintext[i] = pt[i];
    }
    dut->enc_start = 1;
    tick(dut, tfp);
    dut->enc_start = 0;

    // Wait for enc_done
    timeout = 0;
    while (!dut->enc_done && timeout < 100) {
        tick(dut, tfp);
        timeout++;
    }
    if (timeout >= 100) {
        std::cout << "  FAIL: encryption timeout" << std::endl;
        return false;
    }

    // Check result
    bool pass = true;
    for (int i = 0; i < 4; i++) {
        if (dut->ciphertext[i] != expected_ct[i]) {
            pass = false;
            break;
        }
    }

    if (pass) {
        std::cout << "  PASS: ciphertext = ";
        print_128(dut->ciphertext);
        std::cout << std::endl;
        return true;
    } else {
        std::cout << "  FAIL:\n    expected : ";
        print_128(expected_ct);
        std::cout << "\n    got      : ";
        print_128(dut->ciphertext);
        std::cout << std::endl;
        return false;
    }
}

int main(int argc, char** argv) {
    // Initialize Verilator setup
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    // Instantiate DUT and Tracer
    Vaes_top* dut = new Vaes_top;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99); 
    tfp->open("aes_top_tb.vcd");

    int pass_count = 0;
    int fail_count = 0;

    // ---------------------------------------------------------------
    // Test vectors — mapped into uint32_t arrays (Little-Endian)
    // ---------------------------------------------------------------

    // Common Plaintexts
    const uint32_t pt1[4] = {0x7393172a, 0xe93d7e11, 0x2e409f96, 0x6bc1bee2};
    const uint32_t pt2[4] = {0x45af8e51, 0x9eb76fac, 0x1e03ac9c, 0xae2d8a57};
    const uint32_t pt3[4] = {0x1a0a52ef, 0xe5fbc119, 0xa35ce411, 0x30c81c46};
    const uint32_t pt4[4] = {0xe66c3710, 0xad2b417b, 0xdf4f9b17, 0xf69f2445};

    // Initialize all signals to zero
    dut->rst_n = 0;
    dut->key_load = 0;
    dut->enc_start = 0;
    for(int i = 0; i < 4; i++) dut->plaintext[i] = 0;
    for(int i = 0; i < KEY_BITS / 32; i++) dut->key_in[i] = 0;
    
    // Initial warmup ticks
    for(int i = 0; i < 4; i++) tick(dut, tfp);

#if KEY_BITS == 128
    const uint32_t key[4] = {0x09cf4f3c, 0xabf71588, 0x28aed2a6, 0x2b7e1516};

    const uint32_t ct1[4] = {0x2466ef97, 0xa89ecaf3, 0x0d7a3660, 0x3ad77bb4};
    const uint32_t ct2[4] = {0x96fdbaaf, 0xe785895a, 0x03b9699d, 0xf5d3d585};
    const uint32_t ct3[4] = {0xed030688, 0x881b00e3, 0x598ece23, 0x43b1cd7f};
    const uint32_t ct4[4] = {0x04725dd4, 0x82232071, 0x27e8ad3f, 0x7b0c785e};

#elif KEY_BITS == 192
    const uint32_t key[6] = {0x522c6b7b, 0x62f8ead2, 0x809079e5, 0xc810f32b, 0xda0e6452, 0x8e73b0f7};

    const uint32_t ct1[4] = {0x571fa5cc, 0xf712a214, 0x6e45f25f, 0xbd334f1d};
    const uint32_t ct2[4] = {0xecee4eef, 0x7734ecb3, 0x6d0ad3ad, 0x97410484};
    const uint32_t ct3[4] = {0xace6444e, 0xdce0ba2f, 0x70e2e60a, 0xef7afd22};
    const uint32_t ct4[4] = {0x03c18e0e, 0xfb166916, 0x738d6c72, 0x9a4b41ba};

#elif KEY_BITS == 256
    const uint32_t key[8] = {0x0914dff4, 0x2d9810a3, 0x3b6108d7, 0x1f352c07, 0x857d7781, 0x2b73aef0, 0x15ca71be, 0x603deb10};

    const uint32_t ct1[4] = {0x3db181f8, 0x064b5a7e, 0xb5d2a03c, 0xf3eed1bd};
    const uint32_t ct2[4] = {0x31362870, 0xdc5ba74a, 0xd410ed26, 0x591ccb10};
    const uint32_t ct3[4] = {0xbeafed1d, 0xf153e7b1, 0x9ca6f4f9, 0xb6ed21b9};
    const uint32_t ct4[4] = {0x9e24ecc7, 0x067d8d8f, 0x39f9f3ff, 0x23304b7a};

#else
    #error "KEY_BITS must be 128, 192, or 256"
#endif

    // Run tests
    if (run_test(dut, tfp, key, pt1, ct1, 1)) pass_count++; else fail_count++;
    if (run_test(dut, tfp, key, pt2, ct2, 2)) pass_count++; else fail_count++;
    if (run_test(dut, tfp, key, pt3, ct3, 3)) pass_count++; else fail_count++;
    if (run_test(dut, tfp, key, pt4, ct4, 4)) pass_count++; else fail_count++;

    // Summary
    std::cout << "===============================\n";
    std::cout << "Results: " << pass_count << " passed, " << fail_count << " failed\n";
    if (fail_count == 0) {
        std::cout << "ALL TESTS PASSED\n";
    } else {
        std::cout << "FAILURES DETECTED\n";
    }
    std::cout << "===============================\n";

    // Clean up
    dut->eval();
    tfp->close();
    delete dut;
    delete tfp;
    
    return 0;
}
