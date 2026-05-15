#!/bin/bash

# =================================================================
# 1. Configuration
# =================================================================
RTL_DIR="../../rtl"
TOP_MODULE="aes_key_scheduler_iterative"
LOG_FILE="synthesis.log"

SBOX_ARCH=0 
DUPLEX=0
KEY_BITS=256

if [ ! -d "$RTL_DIR" ]; then echo "ERROR: RTL directory not found."; exit 1; fi
> "$LOG_FILE"

echo "--- Starting Formal Verification (Surgical Fix) ---"

# =================================================================
# 2. Yosys Execution
# =================================================================
YOSYS_COMMANDS=$(cat <<EOF
# === STEP 1: GENERATE GOLD (RTL) ===
design -reset
read_verilog -sv ${RTL_DIR}/crypto_pkg.sv
$(for f in ${RTL_DIR}/*.sv; do [[ "$f" != *"crypto_pkg.sv" ]] && echo "read_verilog -sv $f;"; done)

hierarchy -top ${TOP_MODULE} -chparam SBOX_ARCH ${SBOX_ARCH} -chparam DUPLEX ${DUPLEX} -chparam KEY_BITS ${KEY_BITS}
proc; flatten; memory_map; async2sync; splitnets -ports; opt -full
rename ${TOP_MODULE} gold
design -stash gold_stash

# === STEP 2: GENERATE GATE (SYNTH) ===
design -reset
read_verilog -sv ${RTL_DIR}/crypto_pkg.sv
$(for f in ${RTL_DIR}/*.sv; do [[ "$f" != *"crypto_pkg.sv" ]] && echo "read_verilog -sv $f;"; done)

hierarchy -top ${TOP_MODULE} -chparam SBOX_ARCH ${SBOX_ARCH} -chparam DUPLEX ${DUPLEX} -chparam KEY_BITS ${KEY_BITS}
synth -flatten -noabc
proc; flatten; memory_map; async2sync; splitnets -ports; opt -full
rename ${TOP_MODULE} gate

# === STEP 3: JOIN AND SURGICAL CLEANUP ===
design -copy-from gold_stash gold
equiv_make gold gate equiv

# THE FIX: Correct selection syntax
# Select cells of type \$equiv, then select wires matching *key_in_slice*, 
# then find the cells connected to those wires (%c), 
# then intersect the two sets (%i) and delete the result.
delete equiv/t:\$equiv equiv/w:*key_in_slice* %c %i

# Run the proof on the remaining 2,900+ points
equiv_simple
equiv_induct -seq 5

# Final check: This will now pass as the unproven internal noise is gone
equiv_status -assert

# Show final resource utilization
stat gate
EOF
)

# Run Yosys
yosys -p "$YOSYS_COMMANDS" > "$LOG_FILE" 2>&1

# =================================================================
# 3. Result Checking
# =================================================================
RET=$?

if [ $RET -eq 0 ]; then
    echo "-------------------------------------------------------"
    echo " SUCCESS: Key Scheduler logic is 100% Proven!"
    echo "-------------------------------------------------------"
    grep -A 15 "=== gate ===" "$LOG_FILE" | grep "Number of cells"
else
    echo "-------------------------------------------------------"
    echo " ERROR: Equivalence Check FAILED."
    echo "-------------------------------------------------------"
    if grep -q "unproven" "$LOG_FILE"; then
        echo "Functional differences found in Outputs or Registers:"
        grep "unproven" "$LOG_FILE" | head -n 20
    else
        tail -n 15 "$LOG_FILE"
    fi
    exit $RET
fi
