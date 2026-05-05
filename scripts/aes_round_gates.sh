#!/bin/bash

# =================================================================
# Configuration
# =================================================================
RTL_DIR="../rtl"
TOP_MODULE="aes_round_generic"

# Integer values for parameters (Match crypto_pkg.sv Enums)
ARCH_LUT=0
ARCH_CANRIGHT=1

DIR_FORWARD=0
DIR_INVERSE=1
DIR_SHARED=2

# =================================================================
# Table Header
# =================================================================
printf "%-15s | %-10s | %-10s | %-10s\n" "Implementation" "Direction" "Key Bits" "Gate Count"
echo "------------------------------------------------------------"

# =================================================================
# Benchmark Function (Gate Level)
# =================================================================
run_bench() {
    local i_name=$1
    local i_val=$2
    local d_name=$3
    local d_val=$4
    local k_val=$5

    # Using your working file-loading logic and chparam syntax
    output=$(yosys -p "
        read_verilog -sv ${RTL_DIR}/crypto_pkg.sv;
        $(for f in ${RTL_DIR}/*.sv; do 
            if [[ "$f" != *"crypto_pkg.sv" ]]; then 
                echo "read_verilog -sv $f;"
            fi
        done)
        hierarchy -top ${TOP_MODULE} -chparam SBOX_ARCH ${i_val} -chparam DIRECTION ${d_val} -chparam KEY_BITS ${k_val};
        synth -flatten;
        stat
    " 2>/dev/null)

    # Parsing logic
    count=$(echo "$output" | grep "cells" | tail -n 1 | tr -dc '0-9')

    if [ -z "$count" ]; then
        count="ERR"
    fi

    printf "%-15s | %-10s | %-10s | %-10s\n" "$i_name" "$d_name" "$k_val" "$count"
}

# =================================================================
# Execution Matrix
# =================================================================

for k_bits in 128 192 256; do
    # 1. LUT-based Round
    run_bench "LUT" "$ARCH_LUT" "FORWARD" "$DIR_FORWARD" "$k_bits"
    run_bench "LUT" "$ARCH_LUT" "INVERSE" "$DIR_INVERSE" "$k_bits"
    run_bench "LUT" "$ARCH_LUT" "SHARED"  "$DIR_SHARED"  "$k_bits"

    echo "------------------------------------------------------------"

    # 2. Canright-based Round
    run_bench "CANRIGHT" "$ARCH_CANRIGHT" "FORWARD" "$DIR_FORWARD" "$k_bits"
    run_bench "CANRIGHT" "$ARCH_CANRIGHT" "INVERSE" "$DIR_INVERSE" "$k_bits"
    run_bench "CANRIGHT" "$ARCH_CANRIGHT" "SHARED"  "$DIR_SHARED"  "$k_bits"
    
    echo "============================================================"
done
