#!/bin/bash

# =================================================================
# Configuration
# =================================================================
RTL_DIR="../rtl"
TOP_MODULE="aes_key_scheduler"

# Integer values for parameters (Match crypto_pkg.sv Enums)
ARCH_LUT=0
ARCH_CANRIGHT=1

DUP_HALF=0
DUP_FULL=1

# =================================================================
# Table Header
# =================================================================
printf "%-15s | %-10s | %-10s | %-10s\n" "Implementation" "Duplex" "Key Bits" "Gate Count"
echo "------------------------------------------------------------"

# =================================================================
# Benchmark Function (Gate Level)
# =================================================================
run_bench() {
    # Match these variables to the order they are called in the loop!
    local i_name=$1    # "LUT" or "CANRIGHT"
    local i_val=$2     # 0 or 1
    local dup_name=$3  # "HALF" or "FULL"
    local dup_val=$4   # 0 or 1
    local k_val=$5     # 128, 192, or 256

    # Yosys command: 
    # 1. Added mix_columns.sv (found to be a dependency)
    # 2. Used specific filenames to avoid double-loading package
    output=$(yosys -p "
        read_verilog -sv ${RTL_DIR}/crypto_pkg.sv;
        read_verilog -sv ${RTL_DIR}/sbox.sv;
        read_verilog -sv ${RTL_DIR}/mix_columns.sv;
        read_verilog -sv ${RTL_DIR}/aes_key_schedule_iterative.sv;
        hierarchy -top ${TOP_MODULE} \
                  -chparam SBOX_ARCH ${i_val} \
                  -chparam DUPLEX ${dup_val} \
                  -chparam KEY_BITS ${k_val};
        synth -flatten;
        stat
    " 2>/dev/null)

    # Parsing the count (Design Hierarchy total)
    count=$(echo "$output" | grep "cells" | tail -n 1 | tr -dc '0-9')

    if [ -z "$count" ]; then
        count="ERR"
    fi

    # Format the table row
    printf "%-15s | %-10s | %-10s | %-10s\n" "$i_name" "$dup_name" "$k_val" "$count"
}

# =================================================================
# Execution Matrix
# =================================================================

for k_bits in 128 192 256; do
    # Correct Syntax: run_bench "Name" Value "DuplexName" DuplexValue KeyBits
    run_bench "LUT" "$ARCH_LUT" "HALF" "$DUP_HALF" "$k_bits"
    run_bench "LUT" "$ARCH_LUT" "FULL" "$DUP_FULL" "$k_bits"
    
    echo "------------------------------------------------------------"
    
    run_bench "CANRIGHT" "$ARCH_CANRIGHT" "HALF" "$DUP_HALF" "$k_bits"
    run_bench "CANRIGHT" "$ARCH_CANRIGHT" "FULL" "$DUP_FULL" "$k_bits"
    
    echo "============================================================"
done
