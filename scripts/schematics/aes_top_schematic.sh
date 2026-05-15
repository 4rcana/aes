#!/bin/bash
# =================================================================
# AES Top Module Schematic Generator
# =================================================================

RTL_DIR="../../rtl"
TOP_MODULE="aes_top"

# Explicit file list to ensure correct compilation order
FILES=(
    "${RTL_DIR}/crypto_pkg.sv"
    "${RTL_DIR}/sbox.sv"
    "${RTL_DIR}/shift_rows.sv"
    "${RTL_DIR}/mix_columns.sv"
    "${RTL_DIR}/aes_round.sv"
    "${RTL_DIR}/aes_key_scheduler_iterative.sv"
    "${RTL_DIR}/aes_controller_iterative.sv"
    "${RTL_DIR}/aes_core_iterative.sv"
    "${RTL_DIR}/aes_top.sv"
)

# Default parameters (adjust as needed)
SBOX_ARCH=0      # LUT
DUPLEX=1         # HALF
MODE=1           # ECB
KEY_BITS=128

# =================================================================
# Build file loading commands
# =================================================================
read_cmds=""
for f in "${FILES[@]}"; do
    read_cmds+="read_verilog -sv $f; "
done

# =================================================================
# Run Yosys and generate JSON
# =================================================================
echo "Synthesizing ${TOP_MODULE} and generating schematic JSON..."

yosys -p "
    ${read_cmds}
    hierarchy -top ${TOP_MODULE} \
              -chparam SBOX_ARCH ${SBOX_ARCH} \
              -chparam DUPLEX ${DUPLEX} \
              -chparam MODE ${MODE} \
              -chparam KEY_BITS ${KEY_BITS};
    proc; opt; fsm; opt; memory; opt;
    opt_clean;
    write_json ${TOP_MODULE}_schematic.json
" 2>&1 | tee synthesis.log

# =================================================================
# Clean up paramod names in JSON
# =================================================================
if [ -f "${TOP_MODULE}_schematic.json" ]; then
    echo "Cleaning up module names..."
    sed -i 's/\$paramod\$[0-9a-f]*\\//g' ${TOP_MODULE}_schematic.json
    
    echo "✓ Schematic JSON generated successfully"
    
    # =================================================================
    # Convert JSON to SVG using netlistsvg
    # =================================================================
    echo "Converting JSON to SVG..."
    
    if command -v netlistsvg &> /dev/null; then
        netlistsvg ${TOP_MODULE}_schematic.json -o ${TOP_MODULE}_schematic.svg
        
        if [ -f "${TOP_MODULE}_schematic.svg" ]; then
            echo "✓ SVG schematic generated successfully:"
            echo "  ./${TOP_MODULE}_schematic.svg"
            echo ""
            echo "File size: $(du -h "${TOP_MODULE}_schematic.svg" | cut -f1)"
            
            # Remove JSON file
            rm ${TOP_MODULE}_schematic.json
            echo "✓ JSON file removed"
        else
            echo "✗ Failed to generate SVG"
            exit 1
        fi
    else
        echo "✗ netlistsvg not found. Please install it:"
        echo "  npm install -g netlistsvg"
        exit 1
    fi
else
    echo "✗ Failed to generate schematic JSON"
    exit 1
fi
