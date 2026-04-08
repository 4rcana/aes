# --- Parameters (Default values) ---
KEY_BITS   ?= 128
SBOX_IMPL  ?= LUT
DUPLEX     ?= HALF
PIPE_DEPTH ?= 1
MODE       ?= ECB

# --- File Paths ---
TOP_MODULE   = aes_top
V_DIR        = ../../rtl
VECTOR_DIR   = ./AESMCT
PARSE_SCRIPT = ./parser.py
VECTORS_H    = vectors.h

# --- Tool Configuration ---
PYTHON = python
VERILATOR = verilator

# --- Source Files ---
V_SRCS      = $(V_DIR)/sbox.v \
              $(V_DIR)/shift_rows.v \
              $(V_DIR)/mix_columns.v \
              $(V_DIR)/aes_round.v \
              $(V_DIR)/aes_key_schedule_iterative.v \
              $(V_DIR)/aes_core_iterative.v \
              $(V_DIR)/$(TOP_MODULE).v
CPP_SRCS    = tb_aes_top_iterative_MCT.cpp

# --- Verilator Flags ---
VFLAGS      = --cc --exe --build -j 0 --trace
VFLAGS     += -y $(V_DIR)
VFLAGS     += --top-module $(TOP_MODULE)
VFLAGS     += --trace-max-array 1024
VFLAGS     += -GKEY_BITS=$(KEY_BITS) -GSBOX_IMPL=\"$(SBOX_IMPL)\" -GDUPLEX=\"$(DUPLEX)\"
VFLAGS     += -CFLAGS "-DKEY_BITS=$(KEY_BITS) -DSBOX_IMPL=\"$(SBOX_IMPL)\" -DDUPLEX=\"$(DUPLEX)\""

# The generated executable
TARGET     = obj_dir/V$(TOP_MODULE)

# --- Targets ---
.PHONY: all build run clean help

all: build run

# 1. Logic to generate the header file via Python
# This rule looks for any .rsp files in the KAT folder that match the current KEY_BITS
$(VECTORS_H): $(PARSE_SCRIPT)
	@echo "--- Generating Test Vectors for AES-$(KEY_BITS) ---"
	$(PYTHON) $(PARSE_SCRIPT) $(VECTOR_DIR)/$(MODE)*$(KEY_BITS).rsp > $(VECTORS_H)

# 2. Build depends on vectors.h
build: $(VECTORS_H) $(TARGET)

$(TARGET): $(V_SRCS) $(CPP_SRCS) $(VECTORS_H)
	@echo "--- Building Simulation ---"
	$(VERILATOR) $(VFLAGS) $(V_SRCS) $(CPP_SRCS)

# 3. Run
run: $(TARGET)
	@echo "--- Running Simulation ---"
	./$(TARGET)

# 4. Help
help:
	@echo "Usage: make [PARAMETER=VALUE]"
	@echo ""
	@echo "Available Parameters:"
	@echo "  KEY_BITS   : 128, 192, 256  (Default: 128)"
	@echo "  SBOX_IMPL  : LUT, CANRIGHT  (Default: LUT)"
	@echo "  DUPLEX     : HALF, FULL     (Default: HALF)"
	@echo "  PIPE_DEPTH : 1              (Default: 1)"
	@echo "  MODE       : ECB            (Default: ECB)"

# 5. Cleanup
clean:
	rm -rf obj_dir
	rm -f *.vcd
	rm -f $(VECTORS_H)
