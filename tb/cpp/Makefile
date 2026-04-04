# --- Variables ---
# Default key size (can be overridden via: make KEY_BITS=256)
KEY_BITS ?= 128

# Top-level Verilog module name (determines the executable name)
TOP_MODULE = aes_top

# Source files
V_SRCS      = ../../rtl/sbox.v
V_SRCS     += ../../rtl/shift_rows.v
V_SRCS     += ../../rtl/mix_columns.v
V_SRCS     += ../../rtl/aes_round.v
V_SRCS     += ../../rtl/aes_key_schedule_iterative.v
V_SRCS	   += ../../rtl/aes_core_iterative.v
V_SRCS     += ../../rtl/$(TOP_MODULE).v
CPP_SRCS    = tb_aes_top_iterative.cpp

# Directories to search for missing Verilog files (e.g., parent directory)
INC_DIRS   = -y ../../rtl

# Verilator flags
VFLAGS     = --cc --exe --build -j 0 --trace
VFLAGS    += $(INC_DIRS)
VFLAGS    += --top-module $(TOP_MODULE)
VFLAGS    += -GKEY_BITS=$(KEY_BITS)
VFLAGS    += -CFLAGS "-DKEY_BITS=$(KEY_BITS)"
VFLAGS	  += --trace-max-array 1024

# The generated executable
TARGET     = obj_dir/V$(TOP_MODULE)

# --- Targets ---
.PHONY: all build run clean

# Default target: build and run
all: build run

# 1. Run Verilator to generate C++ code and compile the executable
build: $(TARGET)

$(TARGET): $(V_SRCS) $(CPP_SRCS)
	@echo "--- Building for KEY_BITS=$(KEY_BITS) ---"
	verilator $(VFLAGS) $(V_SRCS) $(CPP_SRCS)

# 2. Run the generated simulation
run: $(TARGET)
	@echo "--- Running Simulation ---"
	./$(TARGET)

# 3. Clean up build files and waveforms
clean:
	@echo "--- Cleaning up ---"
	rm -rf obj_dir
	rm -f *.vcd
