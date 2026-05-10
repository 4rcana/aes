#!/bin/bash
# =================================================================
# AES Controller Iterative Module Schematic Generator
# =================================================================
RTL_DIR="../../rtl"
TOP_MODULE="aes_controller_iterative"

# List all files in specific order to satisfy dependencies
FILES=(
    "${RTL_DIR}/crypto_pkg.sv"
    "${RTL_DIR}/aes_controller_iterative.sv"
)

# Default parameters (adjust as needed)
DIRECTION=2      # FORWARD (0), INVERSE (1), or SHARED (2)
KEY_BITS=128     # 128, 192, or 256

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
              -chparam DIRECTION ${DIRECTION} \
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
