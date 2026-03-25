// VIBECODED AND NOT TESTED

`timescale 1ns/1ps

module tb_aes_top;

// ---------------------------------------------------------------
// Clock and reset
// ---------------------------------------------------------------
reg clk;
reg rst_n;

initial clk = 0;
always #5 clk = ~clk;   // 100 MHz

// ---------------------------------------------------------------
// DUT signals — widest key size, overridden per test
// ---------------------------------------------------------------
reg         key_load;
reg         enc_start;
reg [255:0] key_in_wide;   // max width, sliced per test
reg [127:0] plaintext;
wire [127:0] ciphertext;
wire         enc_done;
wire         key_ready;

// ---------------------------------------------------------------
// Test tracking
// ---------------------------------------------------------------
integer test_num;
integer pass_count;
integer fail_count;

// ---------------------------------------------------------------
// Task: run one encryption and check result
// ---------------------------------------------------------------
task run_test;
    input [255:0] key;
    input integer  key_bits;
    input [127:0]  pt;
    input [127:0]  expected_ct;
    input [63:0]   test_id;   // just for display

    reg [127:0] ct_result;
    integer     timeout;
    begin
        $display("--- Test %0d (AES-%0d) ---", test_id, key_bits);

        // Apply reset
        rst_n     = 0;
        key_load  = 0;
        enc_start = 0;
        @(posedge clk); #1;
        @(posedge clk); #1;
        rst_n = 1;
        @(posedge clk); #1;

        // Load key — single cycle pulse
        key_in_wide = key;
        key_load    = 1;
        @(posedge clk); #1;
        key_load = 0;

        // Wait for key expansion to complete
        timeout = 0;
        while (!key_ready && timeout < 200) begin
            @(posedge clk); #1;
            timeout = timeout + 1;
        end
        if (timeout >= 200) begin
            $display("  FAIL: key expansion timeout");
            fail_count = fail_count + 1;
            disable run_test;
        end
        $display("  Key expanded in %0d cycles", timeout);

        // Start encryption
        plaintext = pt;
        enc_start = 1;
        @(posedge clk); #1;
        enc_start = 0;

        // Wait for enc_done
        timeout = 0;
        while (!enc_done && timeout < 100) begin
            @(posedge clk); #1;
            timeout = timeout + 1;
        end
        if (timeout >= 100) begin
            $display("  FAIL: encryption timeout");
            fail_count = fail_count + 1;
            disable run_test;
        end

        ct_result = ciphertext;

        if (ct_result === expected_ct) begin
            $display("  PASS: ciphertext = %h", ct_result);
            pass_count = pass_count + 1;
        end else begin
            $display("  FAIL:");
            $display("    expected : %h", expected_ct);
            $display("    got      : %h", ct_result);
            fail_count = fail_count + 1;
        end
    end
endtask

// ---------------------------------------------------------------
// Instantiate DUT — parametrize per test using generate or
// simply instantiate all three and mux. For a basic testbench
// we instantiate one at a time using conditional compilation.
//
// To test a specific key size, set TB_KEY_BITS at compile time:
//   +define+TB_KEY_BITS=128   (default)
//   +define+TB_KEY_BITS=192
//   +define+TB_KEY_BITS=256
// ---------------------------------------------------------------
`ifndef TB_KEY_BITS
  `define TB_KEY_BITS 128
`endif

localparam TB_KEY_BITS = `TB_KEY_BITS;

aes_top #(.KEY_BITS(TB_KEY_BITS)) u_dut (
    .clk       (clk),
    .rst_n     (rst_n),
    .key_load  (key_load),
    .key_in    (key_in_wide[255 -: TB_KEY_BITS]),
    .enc_start (enc_start),
    .plaintext (plaintext),
    .ciphertext(ciphertext),
    .enc_done  (enc_done)
);

// Pull key_ready from the internal key scheduler for the wait loop
// If your aes_top doesn't expose key_ready, add it as an output port
assign key_ready = u_dut.key_ready;

// ---------------------------------------------------------------
// Test vectors — NIST FIPS 197 Appendix B and SP 800-38A
//
// AES-128:
//   Key:        2b7e151628aed2a6abf7158809cf4f3c
//   Plaintext:  6bc1bee22e409f96e93d7e117393172a
//   Ciphertext: 3ad77bb40d7a3660a89ecaf32466ef97
//
// AES-192:
//   Key:        8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b
//   Plaintext:  6bc1bee22e409f96e93d7e117393172a
//   Ciphertext: bd334f1d6e45f25ff712a214571fa5cc
//
// AES-256:
//   Key:        603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4
//   Plaintext:  6bc1bee22e409f96e93d7e117393172a
//   Ciphertext: f3eed1bdb5d2a03c064b5a7e3db181f8
// ---------------------------------------------------------------
initial begin
    pass_count = 0;
    fail_count = 0;
    rst_n      = 0;
    key_load   = 0;
    enc_start  = 0;
    plaintext  = 0;
    key_in_wide = 0;

    repeat(4) @(posedge clk);

    if (TB_KEY_BITS == 128) begin

        // Vector 1 — FIPS 197 / SP 800-38A ECB-AES128
        run_test(
            256'h2b7e151628aed2a6abf7158809cf4f3c_00000000000000000000000000000000,
            128,
            128'h6bc1bee22e409f96e93d7e117393172a,
            128'h3ad77bb40d7a3660a89ecaf32466ef97,
            1
        );

        // Vector 2 — SP 800-38A ECB-AES128 block 2
        run_test(
            256'h2b7e151628aed2a6abf7158809cf4f3c_00000000000000000000000000000000,
            128,
            128'hae2d8a571e03ac9c9eb76fac45af8e51,
            128'hf5d3d58503b9699de785895a96fdbaaf,
            2
        );

        // Vector 3 — SP 800-38A ECB-AES128 block 3
        run_test(
            256'h2b7e151628aed2a6abf7158809cf4f3c_00000000000000000000000000000000,
            128,
            128'h30c81c46a35ce411e5fbc1191a0a52ef,
            128'h43b1cd7f598ece23881b00e3ed030688,
            3
        );

        // Vector 4 — SP 800-38A ECB-AES128 block 4
        run_test(
            256'h2b7e151628aed2a6abf7158809cf4f3c_00000000000000000000000000000000,
            128,
            128'hf69f2445df4f9b17ad2b417be66c3710,
            128'h7b0c785e27e8ad3f8223207104725dd4,
            4
        );

    end
    else if (TB_KEY_BITS == 192) begin

        // Vector 1 — SP 800-38A ECB-AES192 block 1
        run_test(
            256'h8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b_0000000000000000,
            192,
            128'h6bc1bee22e409f96e93d7e117393172a,
            128'hbd334f1d6e45f25ff712a214571fa5cc,
            1
        );

        // Vector 2 — SP 800-38A ECB-AES192 block 2
        run_test(
            256'h8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b_0000000000000000,
            192,
            128'hae2d8a571e03ac9c9eb76fac45af8e51,
            128'h974104846d0ad3ad7734ecb3ecee4eef,
            2
        );

        // Vector 3 — SP 800-38A ECB-AES192 block 3
        run_test(
            256'h8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b_0000000000000000,
            192,
            128'h30c81c46a35ce411e5fbc1191a0a52ef,
            128'hef7afd2270e2e60adce0ba2face6444e,
            3
        );

        // Vector 4 — SP 800-38A ECB-AES192 block 4
        run_test(
            256'h8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b_0000000000000000,
            192,
            128'hf69f2445df4f9b17ad2b417be66c3710,
            128'h9a4b41ba738d6c72fb16691603c18e0e,
            4
        );

    end
    else if (TB_KEY_BITS == 256) begin

        // Vector 1 — SP 800-38A ECB-AES256 block 1
        run_test(
            256'h603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4,
            256,
            128'h6bc1bee22e409f96e93d7e117393172a,
            128'hf3eed1bdb5d2a03c064b5a7e3db181f8,
            1
        );

        // Vector 2 — SP 800-38A ECB-AES256 block 2
        run_test(
            256'h603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4,
            256,
            128'hae2d8a571e03ac9c9eb76fac45af8e51,
            128'h591ccb10d410ed26dc5ba74a31362870,
            2
        );

        // Vector 3 — SP 800-38A ECB-AES256 block 3
        run_test(
            256'h603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4,
            256,
            128'h30c81c46a35ce411e5fbc1191a0a52ef,
            128'hb6ed21b99ca6f4f9f153e7b1beafed1d,
            3
        );

        // Vector 4 — SP 800-38A ECB-AES256 block 4
        run_test(
            256'h603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4,
            256,
            128'hf69f2445df4f9b17ad2b417be66c3710,
            128'h23304b7a39f9f3ff067d8d8f9e24ecc7,
            4
        );

    end

    // ---------------------------------------------------------------
    // Summary
    // ---------------------------------------------------------------
    $display("===============================");
    $display("Results: %0d passed, %0d failed", pass_count, fail_count);
    if (fail_count == 0)
        $display("ALL TESTS PASSED");
    else
        $display("FAILURES DETECTED");
    $display("===============================");

    $finish;
end

// ---------------------------------------------------------------
// Timeout watchdog — kills simulation if something hangs
// ---------------------------------------------------------------
initial begin
    #100000;
    $display("WATCHDOG: simulation timeout");
    $finish;
end

// ---------------------------------------------------------------
// Optional waveform dump
// ---------------------------------------------------------------
initial begin
    $dumpfile("aes_top_tb.vcd");
    $dumpvars(0, tb_aes_top);
end

endmodule
```

---

### A few things to note

**The key slicing** — `key_in_wide[255 -: TB_KEY_BITS]` takes the top `KEY_BITS` from the 256-bit register, so the AES-192 key `8e73b0f7...522c6b7b` sits in the upper 192 bits and the lower 64 bits are zero and ignored. This matches how `key_in` is consumed MSB-first in the key scheduler.

**`key_ready` visibility** — the testbench reaches into the DUT hierarchy with `u_dut.key_ready` to avoid waiting a fixed number of cycles. If your synthesis tool complains about hierarchical references in a netlist sim, add `key_ready` as an output port on `aes_top` instead.

**Back-to-back blocks with same key** — vectors 1 through 4 reuse the same key, so after the first `run_test` the task resets the DUT each time which re-triggers key expansion. If you want to test the back-to-back performance (no re-expansion), you'd need a variant that skips the reset and `key_load` after the first test.

**Compile-time key size selection** — run all three variants with:
```
vlog +define+TB_KEY_BITS=128 tb_aes_top.v
vlog +define+TB_KEY_BITS=192 tb_aes_top.v
vlog +define+TB_KEY_BITS=256 tb_aes_top.v
