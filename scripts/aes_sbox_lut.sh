#!/bin/bash

# =================================================================
# Configuration
# =================================================================
# 1. ADDED: Path to your package file
PKG_FILE="../rtl/crypto_pkg.sv"
# 2. UPDATED: Ensure extension is .sv
VERILOG_FILE="../rtl/sbox.sv"
TOP_MODULE="sub_generic"
WIDTH=128

# Integer values for parameters (Enums map to 0, 1, 2)
IMPL_LUT=0
IMPL_CANRIGHT=1

DIR_FORWARD=0
DIR_INVERSE=1
DIR_SHARED=2

# =================================================================
# Table Header
# =================================================================
printf "%-15s | %-10s | %-10s | %-10s\n" "Implementation" "Direction" "Width" "LUT Count"
echo "------------------------------------------------------------"

# =================================================================
# Benchmark Function
# =================================================================
run_bench() {
    local i_name=$1
    local i_val=$2
    local d_name=$3
    local d_val=$4

    # Run Yosys
    # 3. UPDATED: Read PKG_FILE first, then RTL_FILE
    # 4. UPDATED: Changed SBOX_IMPL to SBOX_ARCH to match your code
    output=$(yosys -p "
        read_verilog -sv ${PKG_FILE};
        read_verilog -sv ${VERILOG_FILE};
        hierarchy -top ${TOP_MODULE} -chparam SBOX_ARCH ${i_val} -chparam DIRECTION ${d_val} -chparam WIDTH ${WIDTH};
        synth -flatten;
        abc -lut 6;
        stat
    " 2>/dev/null)

    # Parsing logic (remains the same)
    count=$(echo "$output" | awk '$2 == "$lut" {print $1; exit}' | tr -d '\r\n')

    if [ -z "$count" ]; then
        if echo "$output" | grep -q "Number of cells"; then
            count=0
        else
            count="ERR"
        fi
    fi

    printf "%-15s | %-10s | %-10s | %-10s\n" "$i_name" "$d_name" "$WIDTH" "$count"
}

# =================================================================
# Execution Matrix
# =================================================================

run_bench "LUT" "$IMPL_LUT" "FORWARD" "$DIR_FORWARD"
run_bench "LUT" "$IMPL_LUT" "INVERSE" "$DIR_INVERSE"
run_bench "LUT" "$IMPL_LUT" "SHARED"  "$DIR_SHARED"

echo "------------------------------------------------------------"

run_bench "CANRIGHT" "$IMPL_CANRIGHT" "FORWARD" "$DIR_FORWARD"
run_bench "CANRIGHT" "$IMPL_CANRIGHT" "INVERSE" "$DIR_INVERSE"
run_bench "CANRIGHT" "$IMPL_CANRIGHT" "SHARED"  "$DIR_SHARED"
