#!/bin/bash

# =================================================================
# Configuration
# =================================================================
RTL_DIR="../rtl"
TOP_MODULE="aes_controller_iterative"

# Integer values for parameters
DIR_FORWARD=0
DIR_INVERSE=1
DIR_SHARED=2

# =================================================================
# Table Header
# =================================================================
printf "%-12s | %-10s | %-10s\n" "Direction" "Key Bits" "Gate Count"
echo "------------------------------------------------------------"

# =================================================================
# Benchmark Function
# =================================================================
run_bench() {
    local d_name=$1
    local d_val=$2
    local k_val=$3

    # Using the proven file-loading logic
    output=$(yosys -p "
        read_verilog -sv ${RTL_DIR}/crypto_pkg.sv;
        $(for f in ${RTL_DIR}/*.sv; do 
            if [[ "$f" != *"crypto_pkg.sv" ]]; then 
                echo "read_verilog -sv $f;"
            fi
        done)
        hierarchy -top ${TOP_MODULE} -chparam DIRECTION ${d_val} -chparam KEY_BITS ${k_val};
        synth -flatten;
        stat
    " 2>/dev/null)

    # Parsing the count
    count=$(echo "$output" | grep "cells" | tail -n 1 | tr -dc '0-9')

    if [ -z "$count" ]; then
        count="ERR"
    fi

    printf "%-12s | %-10s | %-10s\n" "$d_name" "$k_val" "$count"
}

# =================================================================
# Execution Matrix
# =================================================================

for k_bits in 128 192 256; do
    run_bench "FORWARD" "$DIR_FORWARD" "$k_bits"
    run_bench "INVERSE" "$DIR_INVERSE" "$k_bits"
    run_bench "SHARED"  "$DIR_SHARED"  "$k_bits"
    echo "------------------------------------------------------------"
done
