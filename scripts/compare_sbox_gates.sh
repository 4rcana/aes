#!/bin/bash

# =================================================================
# Configuration
# =================================================================
PKG_FILE="../rtl/crypto_pkg.sv"
RTL_FILE="../rtl/sbox.sv"
TOP_MODULE="sub_generic"
WIDTH=128 

# Integer values for parameters (These match the Enum values 0, 1, 2)
ARCH_LUT=0
ARCH_CANRIGHT=1

DIR_FORWARD=0
DIR_INVERSE=1
DIR_SHARED=2

# =================================================================
# Table Header
# =================================================================
printf "%-15s | %-10s | %-10s | %-10s\n" "Implementation" "Direction" "Width" "Gate Count"
echo "------------------------------------------------------------"

# =================================================================
# Benchmark Function (Gate Level)
# =================================================================
run_bench() {
    local i_name=$1
    local i_val=$2
    local d_name=$3
    local d_val=$4

    output=$(yosys -p "
        read_verilog -sv ${PKG_FILE};
        read_verilog -sv ${RTL_FILE};
        hierarchy -top ${TOP_MODULE} -chparam SBOX_ARCH ${i_val} -chparam DIRECTION ${d_val} -chparam WIDTH ${WIDTH};
        synth -flatten;
        stat
    " 2>/dev/null)

    count=$(echo "$output" | grep "cells" | tail -n 1 | tr -dc '0-9')

    if [ -z "$count" ]; then
        count="ERR"
    fi

    printf "%-15s | %-10s | %-10s | %-10s\n" "$i_name" "$d_name" "$WIDTH" "$count"
}

# =================================================================
# Execution Matrix
# =================================================================

run_bench "LUT" "$ARCH_LUT" "FORWARD" "$DIR_FORWARD"
run_bench "LUT" "$ARCH_LUT" "INVERSE" "$DIR_INVERSE"
run_bench "LUT" "$ARCH_LUT" "SHARED"  "$DIR_SHARED"

echo "------------------------------------------------------------"

run_bench "CANRIGHT" "$ARCH_CANRIGHT" "FORWARD" "$DIR_FORWARD"
run_bench "CANRIGHT" "$ARCH_CANRIGHT" "INVERSE" "$DIR_INVERSE"
run_bench "CANRIGHT" "$ARCH_CANRIGHT" "SHARED"  "$DIR_SHARED"
