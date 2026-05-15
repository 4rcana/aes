#!/bin/bash

# =================================================================
# Methodology: 
# Area: Canright (2005) GE weights
# Timing: Weste & Harris Logical Effort (FO4 Methodology)
# Technology: UMC CMOS (65nm, 40nm, 28nm)
# =================================================================

RTL_DIR="../../rtl"
PKG_FILE="${RTL_DIR}/crypto_pkg.sv"
TOP_MODULE="aes_key_scheduler_iterative"

# Technology FO4 Delays (ps) 
FO4_65=31.35; FO4_40=23.35; FO4_28=18.12

# Delay Model Constants
O_REG=7.0        # Register overhead (Clock-to-Q + Setup) in FO4
BETA_W=0.30      # 30% Wire delay estimation factor

# Parameter Maps
ARCH_LUT=0; ARCH_CANRIGHT=1
DUPLEX_HALF=0; DUPLEX_FULL=1

# Log Files
FINAL_LOG="synthesis.log"
TEMP_LOG="yosys_temp.log"

# Initialize Master Log
> "$FINAL_LOG"

run_bench() {
    local a_name=$1; local a_val=$2
    local d_name=$3; local d_val=$4
    local k_bits=$5

    echo "============================================================================"
    echo " BENCHMARKING (UMC): $TOP_MODULE | $a_name | $d_name | $k_bits-bit"
    echo "============================================================================"

    # --- PASS 1: AREA ESTIMATION (Keep Registers) ---
    yosys -ql "$TEMP_LOG" -p "
        read_verilog -sv ${PKG_FILE};
        $(for f in ${RTL_DIR}/*.sv; do [[ "$f" != *"crypto_pkg.sv" ]] && echo "read_verilog -sv $f;"; done)
        hierarchy -top ${TOP_MODULE} -chparam SBOX_ARCH ${a_val} -chparam DUPLEX ${d_val} -chparam KEY_BITS ${k_bits};
        synth -flatten;
        abc -g gates;
        stat;
    "
    # Extract stats from Pass 1 (Including Flip-Flops)
    area_stats=$(tac "$TEMP_LOG" | awk '/^=== '"$TOP_MODULE"' ===/ {exit} {print}' | tac | awk '/cells/ || /^[[:space:]]+[0-9]+[[:space:]]+\$_/')
    
    # Save Pass 1 to Master Log
    echo -e "\n--- CONFIG: $a_name | $d_name | $k_bits (Pass 1: Area) ---\n" >> "$FINAL_LOG"
    cat "$TEMP_LOG" >> "$FINAL_LOG"

    # --- PASS 2: TIMING ANALYSIS (The Hard Cut) ---
    yosys -ql "$TEMP_LOG" -p "
        read_verilog -sv ${PKG_FILE};
        $(for f in ${RTL_DIR}/*.sv; do [[ "$f" != *"crypto_pkg.sv" ]] && echo "read_verilog -sv $f;"; done)
        hierarchy -top ${TOP_MODULE} -chparam SBOX_ARCH ${a_val} -chparam DUPLEX ${d_val} -chparam KEY_BITS ${k_bits};
        synth -flatten;
        # Isolate combinational round math
        expose -dff;
        delete t:\$_DFF_* t:\$_DFFE_* t:\$_DFF?_*;
        abc -g gates;
        ltp;
    "
    # Extract Logic Depth from Pass 2
    ltp_line=$(grep "length=" "$TEMP_LOG" | tail -n 1)
    depth=$(echo "$ltp_line" | sed 's/.*length=\([0-9]*\).*/\1/')
    depth="${depth:-0}"

    # Save Pass 2 to Master Log
    echo -e "\n--- CONFIG: $a_name | $d_name | $k_bits (Pass 2: Timing) ---\n" >> "$FINAL_LOG"
    cat "$TEMP_LOG" >> "$FINAL_LOG"

    # --- CALCULATIONS ---

    # 1. Total GE Area (Including Logic Gates and DFFs)
    # Weights: NAND/NOR=1, NOT=0.75, XOR/MUX=1.75, DFF=6.0
    ge_total=$(echo "$area_stats" | awk '
        /\$_NAND_/ || /\$_NOR_/ || /\$_ANDNOT_/ || /\$_ORNOT_/ { sum += $1 * 1.00 }
        /\$_NOT_/                                              { sum += $1 * 0.75 }
        /\$_AND_/  || /\$_OR_/                                 { sum += $1 * 1.75 }
        /\$_XOR_/  || /\$_XNOR_/                               { sum += $1 * 1.75 }
        /\$_MUX_/                                              { sum += $1 * 1.75 }
        /\$_DFF_/  || /\$_DFFE_/                               { sum += $1 * 6.00 }
        END { printf "%.2f", sum }
    ')

    # 2. Average Fan-out (h) from Pass 1
    local pi_count=$((k_bits + 4))
    h_avg=$(echo "$area_stats" | awk -v pi="$pi_count" '
        BEGIN { inputs = 0; outputs = 0 }
        /\$_NOT_/ { inputs += $1 * 1; outputs += $1 }
        /\$_MUX_/ { inputs += $1 * 3; outputs += $1 }
        /\$_DFF_/ { inputs += $1 * 1; outputs += $1 }
        /\$_AND_/ || /\$_NAND_/ || /\$_OR_/ || /\$_NOR_/ || /\$_XOR_/ || /\$_XNOR_/ || /\$_ANDNOT_/ || /\$_ORNOT_/ { 
            inputs += $1 * 2; outputs += $1 
        }
        END { 
            drivers = outputs + pi;
            if (drivers > 0) printf "%.3f", inputs / drivers; else print "2.000" 
        }
    ')

    # 3. Dynamic Complexity Factor (k) in FO4 units
    k_val=$(echo "$area_stats" | awk -v h="$h_avg" '
        BEGIN { total_delay = 0; total_gates = 0 }
        /\$_NAND_/   || /\$_ANDNOT_/ { d = (1.333 * h + 2.0); total_delay += $1 * d; total_gates += $1 }
        /\$_NOR_/    || /\$_ORNOT_/  { d = (1.666 * h + 2.0); total_delay += $1 * d; total_gates += $1 }
        /\$_NOT_/                    { d = (1.000 * h + 1.0); total_delay += $1 * d; total_gates += $1 }
        /\$_AND_/    || /\$_OR_/     { d = (1.333 * h + 3.0); total_delay += $1 * d; total_gates += $1 }
        /\$_XOR_/    || /\$_XNOR_/   { d = (4.000 * h + 4.0); total_delay += $1 * d; total_gates += $1 }
        /\$_MUX_/                    { d = (2.000 * h + 4.0); total_delay += $1 * d; total_gates += $1 }
        END { if (total_gates > 0) printf "%.3f", (total_delay / total_gates) / 5; else print "1.200" }
    ')

    # 4. Final Output Formatting
    echo "TIMING ANALYSIS (Pass 2):"
    echo "Longest topological path (Register-to-Register) length: $depth"

    echo -e "\nRESOURCE BREAKDOWN (Pass 1):"
    echo "$area_stats"

    echo -e "\n--- CALCULATED ESTIMATES (UMC) ---"
    echo "Estimated Total Area (GE): $ge_total"
    echo "Avg Fan-out (h):           $h_avg"
    echo "Gate Complexity (k):       $k_val"
    echo "Logic Depth (LD):          $depth"

    if [[ "$depth" != "0" ]]; then
        fo4_cycle=$(awk "BEGIN { printf \"%.2f\", ($depth * $k_val + $O_REG) * (1 + $BETA_W) }")
        echo "Cycle Time (FO4):          $fo4_cycle"

        # Determine throughut cycles (standard iterative AES: N_rounds + 1)
        if [ "$k_bits" -eq 128 ]; then cycles=11; 
        elif [ "$k_bits" -eq 192 ]; then cycles=13; 
        else cycles=15; fi

        calc_metrics() {
            local dfo4=$1
            awk "BEGIN {
                t_clk = $fo4_cycle * $dfo4;
                f_max = 1000000 / t_clk;
                tp = (128 * f_max) / $cycles;
                printf \"%.2f MHz | TP: %.2f Mbps\", f_max, tp;
            }"
        }
        echo "Metrics (65UMC):           $(calc_metrics $FO4_65)"
        echo "Metrics (40UMC):           $(calc_metrics $FO4_40)"
        echo "Metrics (28UMC):           $(calc_metrics $FO4_28)"
    fi
    echo "============================================================================"
    echo -e "\n"
    rm -f "$TEMP_LOG"
}

# --- Execution Matrix ---

run_bench "LUT" "$ARCH_LUT" "HALF" "$DUPLEX_HALF" 128
run_bench "CANRIGHT" "$ARCH_CANRIGHT" "HALF" "$DUPLEX_HALF" 128

echo "All detailed tool outputs saved to $FINAL_LOG"
