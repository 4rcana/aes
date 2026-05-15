#!/bin/bash

# =================================================================
# 1. Configuration
# =================================================================
RTL_DIR="../../rtl"
TOP_MODULE="aes_round_generic"
LOG_FILE="synthesis.log"

# AES Parameters
SBOX_ARCH=1    # 0:LUT, 1:CANRIGHT
DIRECTION=2    # 0:FWD, 1:INV, 2:SHARED
KEY_BITS=256

# =================================================================
# 2. Environment Setup
# =================================================================
if [ ! -d "$RTL_DIR" ]; then
    echo "ERROR: RTL directory '$RTL_DIR' not found."
    exit 1
fi

# Clear log
> "$LOG_FILE"

echo "--- Starting Synthesis & Formal Equivalence Check ---"
echo "Module:     $TOP_MODULE"
echo "Parameters: ARCH=$SBOX_ARCH, DIR=$DIRECTION, KEY=$KEY_BITS"

# =================================================================
# 3. Yosys Execution
# =================================================================
YOSYS_COMMANDS=$(cat <<EOF
    # A. Load the RTL
    read_verilog -sv ${RTL_DIR}/crypto_pkg.sv;
    $(for f in ${RTL_DIR}/*.sv; do 
        if [[ "$f" != *"crypto_pkg.sv" ]]; then 
            echo "read_verilog -sv $f;"
        fi
    done)

    # B. Build the Reference (Gold) Model
    hierarchy -top ${TOP_MODULE} \
              -chparam SBOX_ARCH ${SBOX_ARCH} \
              -chparam DIRECTION ${DIRECTION} \
              -chparam KEY_BITS ${KEY_BITS};
    
    # Process RTL into a gate-like structure for comparison
    flatten;
    proc;
    opt;
    
    # Save the flattened RTL to a side-buffer named 'ref_design'
    design -copy-to ref_design ${TOP_MODULE};

    # C. Build the Synthesized (Gate) Model
    # This runs the heavy optimization
    synth -flatten;
    
    # Rename the synthesized result to 'gate'
    opt -full;
    rename ${TOP_MODULE} gate;

    # D. Logic Equivalence Check (LEC)
    # Import the RTL version back from the buffer into the active workspace
    design -copy-from ref_design -as gold ${TOP_MODULE};

    # Create the miter circuit (compares 'gold' vs 'gate')
    equiv_make gold gate equiv;
    
    # Run the formal proof
    equiv_simple;
    equiv_induct;
    
    # This ensures the script exits with error if proof fails
    equiv_status -assert;

    # E. Final Reports
    # We target the module 'gate' specifically for stats
    stat gate;
EOF
)

# Run Yosys
yosys -p "$YOSYS_COMMANDS" > "$LOG_FILE" 2>&1

# =================================================================
# 4. Result Checking
# =================================================================
RET=$?

if [ $RET -eq 0 ]; then
    echo "-------------------------------------------------------"
    echo " SUCCESS: Synthesis complete and Equivalence Proven!"
    echo "-------------------------------------------------------"
    # Extract cell statistics for the synthesized 'gate' module
    echo "Resource Utilization (Gate Level):"
    grep -A 30 "=== gate ===" "$LOG_FILE" | grep -E "Number of cells:|   \\\$"
else
    echo "-------------------------------------------------------"
    echo " ERROR: Synthesis or Equivalence Check FAILED."
    echo "-------------------------------------------------------"
    # If it failed at the proof stage, show the unproven cells
    if grep -q "unproven" "$LOG_FILE"; then
        grep "unproven" "$LOG_FILE"
    fi
    # Show the last few lines for context
    tail -n 15 "$LOG_FILE"
    exit $RET
fi
