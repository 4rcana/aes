#!/bin/bash

# =================================================================
# Configuration
# =================================================================
VERILOG_FILE="../rtl/sbox.v"
TOP_MODULE="sub_generic"
WIDTH=128

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
    output=$(yosys -p "
        read_verilog -sv ${VERILOG_FILE};
        hierarchy -top ${TOP_MODULE} -chparam SBOX_IMPL ${i_val} -chparam DIRECTION ${d_val} -chparam WIDTH ${WIDTH};
        synth -flatten;
        abc -lut 6;
        stat
    " 2>/dev/null)

    # NEW ROBUST PARSING:
    # 1. We look for a line that has a number followed by '$lut'
    # 2. We use awk to ensure we only grab the line where $lut is the second column
    # 3. This ignores the "ABC RESULTS..." summary text entirely.
    count=$(echo "$output" | awk '$2 == "$lut" {print $1; exit}' | tr -d '\r\n')

    # If count is still empty, the module might be empty or had a synth error
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
