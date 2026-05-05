#!/bin/bash

# =================================================================
# Configuration
# =================================================================
RTL_DIR="../rtl"
TOP_MODULE="aes_top"

# Explicit file list to ensure correct compilation order
FILES=(
    "${RTL_DIR}/crypto_pkg.sv"
    "${RTL_DIR}/sbox.sv"
    "${RTL_DIR}/shift_rows.sv"
    "${RTL_DIR}/mix_columns.sv"
    "${RTL_DIR}/aes_round.sv"
    "${RTL_DIR}/aes_key_schedule_iterative.sv"
    "${RTL_DIR}/aes_controller_iterative.sv"
    "${RTL_DIR}/aes_core_iterative.sv"
    "${RTL_DIR}/aes_top.sv"
)

# Integer values for Enum parameters (Match crypto_pkg.sv)
ARCH_LUT=0;      ARCH_CANRIGHT=1
DUP_HALF=0;      DUP_FULL=1
MODE_ECB=0;      MODE_CBC=1

# =================================================================
# Table Header
# =================================================================
printf "%-15s | %-7s | %-6s | %-8s | %-10s\n" "Implementation" "Duplex" "Mode" "Keys" "Gates"
echo "------------------------------------------------------------"

# =================================================================
# Benchmark Function
# =================================================================
run_bench() {
    local i_name=$1; local i_val=$2
    local d_name=$3; local d_val=$4
    local m_name=$5; local m_val=$6
    local k_val=$7

    # Build file loading commands
    local read_cmds=""
    for f in "${FILES[@]}"; do
        read_cmds+="read_verilog -sv $f; "
    done

    # Run Yosys with all 4 parameters
    output=$(yosys -p "
        ${read_cmds}
        hierarchy -top ${TOP_MODULE} \
                  -chparam SBOX_ARCH ${i_val} \
                  -chparam DUPLEX ${d_val} \
                  -chparam MODE ${m_val} \
                  -chparam KEY_BITS ${k_val};
        synth -flatten;
        stat
    " 2>/dev/null)

    # Robust gate count parsing
    count=$(echo "$output" | grep "cells" | tail -n 1 | tr -dc '0-9')

    if [ -z "$count" ]; then
        count="ERR"
    fi

    # Formatted row output
    printf "%-15s | %-7s | %-6s | %-8s | %-10s\n" "$i_name" "$d_name" "$m_name" "$k_val" "$count"
}

# =================================================================
# Execution Matrix (Total 24 combinations)
# =================================================================

for k in 128 192 256; do
    for mode_str in "ECB,$MODE_ECB" "CBC,$MODE_CBC"; do
        IFS=',' read -r m_name m_val <<< "$mode_str"
        
        # Run LUT combinations
        run_bench "LUT" "$ARCH_LUT" "HALF" "$DUP_HALF" "$m_name" "$m_val" "$k"
        run_bench "LUT" "$ARCH_LUT" "FULL" "$DUP_FULL" "$m_name" "$m_val" "$k"
        
        # Run Canright combinations
        run_bench "CANRIGHT" "$ARCH_CANRIGHT" "HALF" "$DUP_HALF" "$m_name" "$m_val" "$k"
        run_bench "CANRIGHT" "$ARCH_CANRIGHT" "FULL" "$DUP_FULL" "$m_name" "$m_val" "$k"
        
        echo "------------------------------------------------------------"
    done
    echo "============================================================"
done
