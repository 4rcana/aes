#!/bin/bash

# =================================================================
# Configuration (Canright 2005 and Weste & Harris Methodology)
# =================================================================
RTL_DIR="../../rtl"
PKG_FILE="${RTL_DIR}/crypto_pkg.sv"
TOP_MODULE="aes_round_generic"
WIDTH=128
KEY_BITS=128

# Technology FO4 Delays (ps) 
FO4_65=31.35; FO4_40=23.35; FO4_28=18.12

# Overhead Constants
O_REG=7.0        
BETA_W=0.30      

# Parameter Maps
ARCH_LUT=0; ARCH_CANRIGHT=1
DIR_FORWARD=0; DIR_INVERSE=1; DIR_SHARED=2

# Log Files
FINAL_LOG="synthesis.log"
TEMP_LOG="yosys_temp.log"

# Clear the final log at start
> "$FINAL_LOG"

run_bench() {
    local a_name=$1; local a_val=$2
    local d_name=$3; local d_val=$4

    echo "============================================================================"
    echo " BENCHMARKING: $TOP_MODULE | $a_name | $d_name"
    echo "============================================================================"

    # Run Yosys
    yosys -ql $TEMP_LOG -p "
        read_verilog -sv ${PKG_FILE};
        $(for f in ${RTL_DIR}/*.sv; do [[ "$f" != *"crypto_pkg.sv" ]] && echo "read_verilog -sv $f;"; done)
        hierarchy -top ${TOP_MODULE} -chparam SBOX_ARCH ${a_val} -chparam DIRECTION ${d_val};
        synth -flatten;
        abc -g gates;
        ltp;
        stat;
    "

    # Append full detailed run to the master synthesis.log
    echo -e "\n--- CONFIG: $a_name | $d_name ---\n" >> "$FINAL_LOG"
    cat "$TEMP_LOG" >> "$FINAL_LOG"

    # 1. Extract Logic Depth (LD)
    ltp_line=$(grep "length=" $TEMP_LOG | tail -n 1)
    depth=$(echo "$ltp_line" | sed 's/.*length=\([0-9]*\).*/\1/')
    depth="${depth:-0}"
    
    # 2. Extract ONLY the FINAL Gate Statistics (Post-ABC)
    # We use tac to find the last occurrence of the module header in the log
    raw_stats=$(tac $TEMP_LOG | awk '/^=== '"$TOP_MODULE"' ===/ {exit} {print}' | tac | awk '/cells/ || /^[[:space:]]+[0-9]+[[:space:]]+\$_/')

    # 3. Calculate Average Fan-out (h)
    local pi_count=258
    h_avg=$(echo "$raw_stats" | awk -v pi="$pi_count" '
        BEGIN { inputs = 0; outputs = 0 }
        /\$_NOT_/ { inputs += $1 * 1; outputs += $1 }
        /\$_MUX_/ { inputs += $1 * 3; outputs += $1 }
        /\$_AND_/ || /\$_NAND_/ || /\$_OR_/ || /\$_NOR_/ || /\$_XOR_/ || /\$_XNOR_/ || /\$_ANDNOT_/ || /\$_ORNOT_/ { 
            inputs += $1 * 2; outputs += $1 
        }
        END { 
            drivers = outputs + pi;
            if (drivers > 0) printf "%.3f", inputs / drivers; else print "2.000" 
        }
    ')

    # 4. Calculate Dynamic Complexity Factor (k)
    k_val=$(echo "$raw_stats" | awk -v h="$h_avg" '
        BEGIN { total_delay = 0; total_gates = 0 }
        /\$_NAND_/   || /\$_ANDNOT_/ { d = (1.333 * h + 2.0); total_delay += $1 * d; total_gates += $1 }
        /\$_NOR_/    || /\$_ORNOT_/  { d = (1.666 * h + 2.0); total_delay += $1 * d; total_gates += $1 }
        /\$_NOT_/                    { d = (1.000 * h + 1.0); total_delay += $1 * d; total_gates += $1 }
        /\$_AND_/    || /\$_OR_/     { d = (1.333 * h + 3.0); total_delay += $1 * d; total_gates += $1 }
        /\$_XOR_/    || /\$_XNOR_/   { d = (4.000 * h + 4.0); total_delay += $1 * d; total_gates += $1 }
        /\$_MUX_/                    { d = (2.000 * h + 4.0); total_delay += $1 * d; total_gates += $1 }
        END { if (total_gates > 0) printf "%.3f", (total_delay / total_gates) / 5; else print "1.200" }
    ')

    # 5. AREA ESTIMATION (GE)
    ge_total=$(echo "$raw_stats" | awk '
        /\$_NAND_/ || /\$_NOR_/ || /\$_ANDNOT_/ || /\$_ORNOT_/ { sum += $1 * 1.00 }
        /\$_NOT_/                                              { sum += $1 * 0.75 }
        /\$_AND_/  || /\$_OR_/                                 { sum += $1 * 1.75 }
        /\$_XOR_/  || /\$_XNOR_/                               { sum += $1 * 1.75 }
        /\$_MUX_/                                              { sum += $1 * 1.75 }
        END { printf "%.2f", sum }
    ')

    # 6. Output Clean Metrics to terminal
    echo -e "\nFINAL RESOURCE BREAKDOWN:"
    echo "$raw_stats"

    echo -e "\n--- PERFORMANCE ESTIMATES ---"
    echo "Logic Depth (LD):         $depth"
    echo "Estimated Area (GE):      $ge_total"
    echo "Avg Fan-out (h):          $h_avg"
    echo "Gate Complexity (k):      $k_val"

    if [[ "$depth" != "0" ]]; then
        fo4_cycle=$(awk "BEGIN { print ($depth * $k_val + $O_REG) * (1 + $BETA_W) }")
        echo "Cycle Time (FO4):         $(printf "%.2f" $fo4_cycle)"

        if [ "$KEY_BITS" -eq 128 ]; then cycles=11; 
        elif [ "$KEY_BITS" -eq 192 ]; then cycles=13; 
        else cycles=15; fi

        calc_metrics() {
            local dfo4=$1
            awk "BEGIN {
                t_clk = $fo4_cycle * $dfo4;
                f_max = 1000000 / t_clk;
                tp = (128 * f_max) / $cycles;
                printf \"%.2f MHz | Throughput: %.2f Mbps\", f_max, tp;
            }"
        }
        echo "Metrics (65nm):           $(calc_metrics $FO4_65)"
        echo "Metrics (40nm):           $(calc_metrics $FO4_40)"
        echo "Metrics (28nm):           $(calc_metrics $FO4_28)"
    fi

    echo "============================================================================"
    echo -e "\n"
    rm -f "$TEMP_LOG"
}

# --- Execution Matrix ---
run_bench "LUT" "$ARCH_LUT" "FORWARD" "$DIR_FORWARD"
run_bench "LUT" "$ARCH_LUT" "INVERSE" "$DIR_INVERSE"
run_bench "LUT" "$ARCH_LUT" "SHARED"  "$DIR_SHARED"

echo "------------------------------------------------------------"

run_bench "CANRIGHT" "$ARCH_CANRIGHT" "FORWARD" "$DIR_FORWARD"
run_bench "CANRIGHT" "$ARCH_CANRIGHT" "INVERSE" "$DIR_INVERSE"
run_bench "CANRIGHT" "$ARCH_CANRIGHT" "SHARED"  "$DIR_SHARED"

echo "All detailed logs saved to $FINAL_LOG"
