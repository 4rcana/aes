#!/bin/bash
# =================================================================
# Mix Columns Generic Module Schematic Generator (Flattened)
# =================================================================
RTL_DIR="../../rtl"
TOP_MODULE="mix_columns_generic"

# List all files in specific order to satisfy dependencies
FILES=(
    "${RTL_DIR}/crypto_pkg.sv"
    "${RTL_DIR}/mix_columns.sv"
)

# Default parameters (adjust as needed)
DIRECTION=2      # FORWARD (0), INVERSE (1), or SHARED (2)

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
echo "Synthesizing ${TOP_MODULE} (flattened) and generating schematic JSON..."

yosys -p "
    ${read_cmds}
    hierarchy -top ${TOP_MODULE} \
              -chparam DIRECTION ${DIRECTION};
    proc; opt; fsm; opt; memory; opt;
    flatten;
    opt_clean;
    rename -hide */t:*\$paramod*;
    splitnets;
    opt_clean;
    write_json ${TOP_MODULE}_schematic.json
" 2>&1 | tee synthesis.log

# =================================================================
# Clean up paramod names in JSON with more aggressive patterns
# =================================================================
if [ -f "${TOP_MODULE}_schematic.json" ]; then
    echo "Cleaning up module names..."
    # Remove $paramod\module\PARAM=value format
    sed -i "s/\\\$paramod\\\\[^\\\\]*\\\\\\([^\\\\]*\\)\\\\[^\"]*/\\1/g" ${TOP_MODULE}_schematic.json
    # Remove $paramod$hash\module format
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
