#!/bin/bash

# =================================================================
# Configuration (Canright 2005 and Weste & Harris Methodology)
# =================================================================
PKG_FILE="../rtl/crypto_pkg.sv"
RTL_FILE="../rtl/sbox.sv"
TOP_MODULE="sub_generic"
WIDTH=128
KEY_BITS=128  # Used to determine throughput cycles (128->11, 192->13, 256->15)

# Technology FO4 Delays (ps) 
# Source: Krishna et al., 2021 (Springer LNEE 722 / UMC FO4 Data)
FO4_65=31.35; FO4_40=23.35; FO4_28=18.12

# O_REG=7 (Overhead), BETA_W=0.30 (30% Wire delay)
O_REG=7.0        
BETA_W=0.30      

# Integer values for parameters
ARCH_LUT=0; ARCH_CANRIGHT=1
DIR_FORWARD=0; DIR_INVERSE=1; DIR_SHARED=2

LOG="yosys_run.log"

run_bench() {
    local i_name=$1; local i_val=$2
    local d_name=$3; local d_val=$4

    echo "============================================================================"
    echo " CONFIGURATION: $i_name | $d_name | Width=$WIDTH"
    echo "============================================================================"

    yosys -ql $LOG -p "
        read_verilog -sv ${PKG_FILE};
        read_verilog -sv ${RTL_FILE};
        hierarchy -top ${TOP_MODULE} -chparam SBOX_ARCH ${i_val} -chparam DIRECTION ${d_val} -chparam WIDTH ${WIDTH};
        synth -flatten;
        abc -g gates;
        ltp;
        stat;
    "

    # 1. Extract Logic Depth (LD)
    ltp_line=$(grep "length=" $LOG | tail -n 1)
    depth=$(echo "$ltp_line" | sed 's/.*length=\([0-9]*\).*/\1/')
    depth="${depth:-0}"
    
    echo "TIMING ANALYSIS:"
    echo "$ltp_line"

    # 2. Extract Final Resource Stats block
    raw_stats=$(awk '/^=== '"$TOP_MODULE"' ===/ { block=""; next } /cells/ { block=$0; next } /^[[:space:]]+[0-9]+[[:space:]]+\$_/ { block = block "\n" $0 } END { print block }' $LOG)

    # 3. Calculate Average Fan-out (h)
    local pi_count=$((WIDTH + 1))
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

    # 4. Calculate Dynamic Complexity Factor (k) in FO4 units [Weste & Harris Tables 4.2 & 4.3]
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

    # 5. AREA ESTIMATION (GE) [Canright 2005 Weights]
    ge_total=$(echo "$raw_stats" | awk '
        /\$_NAND_/ || /\$_NOR_/ || /\$_ANDNOT_/ || /\$_ORNOT_/ { sum += $1 * 1.00 }
        /\$_NOT_/                                              { sum += $1 * 0.75 }
        /\$_AND_/  || /\$_OR_/                                 { sum += $1 * 1.75 }
        /\$_XOR_/  || /\$_XNOR_/                               { sum += $1 * 1.75 }
        /\$_MUX_/                                              { sum += $1 * 1.75 }
        END { printf "%.2f", sum }
    ')

    # 6. Printing
    echo -e "\nRESOURCE BREAKDOWN (RAW):"
    echo "$raw_stats" | grep -v "\$scopeinfo"

    echo -e "\n--- CALCULATED ESTIMATES ---"
    echo "Estimated Area (GE):      $ge_total"
    echo "Avg Fan-out (h):          $h_avg"
    echo "Gate Complexity (k):      $k_val"
    echo "Logic Depth (LD):         $depth"

    if [[ "$depth" != "0" ]]; then
        # Cycle Time in FO4: (LD * k + Oreg) * (1 + beta_w)
        fo4_cycle=$(awk "BEGIN { print ($depth * $k_val + $O_REG) * (1 + $BETA_W) }")
        echo "Cycle Time (FO4):         $(printf "%.2f" $fo4_cycle)"

        # Determine cycles per block based on iterative architecture (11, 13, 15)
        if [ "$KEY_BITS" -eq 128 ]; then cycles=11; 
        elif [ "$KEY_BITS" -eq 192 ]; then cycles=13; 
        else cycles=15; fi

        calc_metrics() {
            local dfo4=$1
            awk "BEGIN {
                t_clk = $fo4_cycle * $dfo4;
                f_max = 1000000 / t_clk;
                # Throughput (Mbps) = (128 bits * Fmax_MHz) / Cycles
                tp = (128 * f_max) / $cycles;
                # TPA = Mbps / GE
                tpa = tp / $ge_total;
                printf \"%.2f MHz | TP: %.2f Mbps | TPA: %.4f\", f_max, tp, tpa;
            }"
        }
        echo "Metrics (UMC65):          $(calc_metrics $FO4_65)"
        echo "Metrics (UMC40):          $(calc_metrics $FO4_40)"
        echo "Metrics (UMC28):          $(calc_metrics $FO4_28)"
    fi

    echo "============================================================================"
    echo -e "\n"
    rm -f $LOG
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
