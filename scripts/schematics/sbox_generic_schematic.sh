#!/bin/bash
# =================================================================
# SBox Generic Module Schematic Generator (Optimized/Flattened)
# =================================================================
RTL_DIR="../../rtl"
TOP_MODULE="sbox_generic"

# Parameters
SBOX_ARCH=1      # 1: CANRIGHT
DIRECTION=2     # 0: FORWARD, 1: INVERSE, 2: SHARED

# Load Package and then the main S-Box file
# We list them explicitly to ensure correct order
FILES=(
    "${RTL_DIR}/crypto_pkg.sv"
    "${RTL_DIR}/sbox.sv"
)

echo "Synthesizing ${TOP_MODULE} (ARCH=${SBOX_ARCH}, DIR=${DIRECTION})..."

# Use a Here-Doc (<<EOF) instead of -p "" to avoid shell parsing errors
yosys <<EOF
    read_verilog -sv ${RTL_DIR}/crypto_pkg.sv
    read_verilog -sv ${RTL_DIR}/sbox.sv
    
    hierarchy -top ${TOP_MODULE} -chparam SBOX_ARCH ${SBOX_ARCH} -chparam DIRECTION ${DIRECTION}
    
    # 1. Convert processes and flatten hierarchy
    proc
    flatten
    
    # 2. Optimization to propagate the DIRECTION constant
    opt -purge
    
    # 3. ABC mapping to generic gates
    # This is required to make the unused logic (like Inverse matrices) physically disappear
    abc -g gates
    
    # 4. Final aggressive cleanup
    opt_clean -purge
    
    # 5. Optional: Clean up naming for a prettier schematic
    rename -hide */t:*\$paramod*
    splitnets
    opt_clean -purge
    
    # 6. Export to JSON
    write_json ${TOP_MODULE}_schematic.json
EOF

# =================================================================
# Post-Processing and SVG Generation
# =================================================================
if [ -f "${TOP_MODULE}_schematic.json" ]; then
    echo "Cleaning up JSON module names..."
    sed -i "s/\\\$paramod\\\\[^\\\\]*\\\\\\([^\\\\]*\\)\\\\[^\"]*/\\1/g" ${TOP_MODULE}_schematic.json
    sed -i 's/\$paramod\$[0-9a-f]*\\//g' ${TOP_MODULE}_schematic.json
    
    if command -v netlistsvg &> /dev/null; then
        # Generate SVG with a name indicating the direction
        netlistsvg ${TOP_MODULE}_schematic.json -o ${TOP_MODULE}_dir${DIRECTION}_schematic.svg
        echo "✓ Generated: ./${TOP_MODULE}_dir${DIRECTION}_schematic.svg"
        rm ${TOP_MODULE}_schematic.json
    else
        echo "✗ netlistsvg not found. Please install it."
    fi
else
    echo "✗ Failed to generate schematic JSON"
    exit 1
fi
