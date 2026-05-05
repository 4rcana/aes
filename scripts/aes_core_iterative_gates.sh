#!/bin/bash

# =================================================================
# Configuration
# =================================================================
RTL_DIR="../rtl"
TOP_MODULE="aes_core_iterative"

# List all files in specific order to satisfy dependencies
FILES=(
    "${RTL_DIR}/crypto_pkg.sv"
    "${RTL_DIR}/sbox.sv"
    "${RTL_DIR}/shift_rows.sv"
    "${RTL_DIR}/mix_columns.sv"
    "${RTL_DIR}/aes_round.sv"
    "${RTL_DIR}/aes_key_schedule_iterative.sv"
    "${RTL_DIR}/aes_controller_iterative.sv"
    "${RTL_DIR}/aes_core_iterative.sv"
)

# Integer values for parameters
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
# Benchmark Function
# =================================================================
run_bench() {
    local i_name=$1    # "LUT" or "CANRIGHT"
    local i_val=$2     # 0 or 1
    local dup_name=$3  # "HALF" or "FULL"
    local dup_val=$4   # 0 or 1
    local k_val=$5     # 128, 192, 256

    # Build file list commands
    local read_cmds=""
    for f in "${FILES[@]}"; do
        read_cmds+="read_verilog -sv $f; "
    done

    # Run Yosys
    # Parameters checked: SBOX_ARCH, DUPLEX, KEY_BITS
    output=$(yosys -p "
        ${read_cmds}
        hierarchy -top ${TOP_MODULE} \
                  -chparam SBOX_ARCH ${i_val} \
                  -chparam DUPLEX ${dup_val} \
                  -chparam KEY_BITS ${k_val};
        synth -flatten;
        stat
    " 2>/dev/null)

    # Parsing the count (Total Design Hierarchy cells)
    count=$(echo "$output" | grep "cells" | tail -n 1 | tr -dc '0-9')

    if [ -z "$count" ]; then
        count="ERR"
    fi

    printf "%-15s | %-10s | %-10s | %-10s\n" "$i_name" "$dup_name" "$k_val" "$count"
}

# =================================================================
# Execution Matrix
# =================================================================

for k in 128 192 256; do
    # 1. LUT-based Cores
    run_bench "LUT" "$ARCH_LUT" "HALF" "$DUP_HALF" "$k"
    run_bench "LUT" "$ARCH_LUT" "FULL" "$DUP_FULL" "$k"
    
    echo "------------------------------------------------------------"
    
    # 2. Canright-based Cores
    run_bench "CANRIGHT" "$ARCH_CANRIGHT" "HALF" "$DUP_HALF" "$k"
    run_bench "CANRIGHT" "$ARCH_CANRIGHT" "FULL" "$DUP_FULL" "$k"
    
    echo "============================================================"
done
