# --- Parameters (Default values) ---
KEY_BITS   ?= 128
SBOX_IMPL  ?= LUT
DUPLEX     ?= HALF
PIPE_DEPTH ?= 1
MODE       ?= ECB
TEST       ?= KAT

# --- File Paths ---
TOP_MODULE   = aes_top
V_DIR        = ../../rtl
VECTOR_DIR   = ./TEST_VECTORS/AES$(TEST)
PARSE_SCRIPT = ./parser.py
VECTORS_H    = vectors.h

# --- Tool Configuration ---
PYTHON    = python3
VERILATOR = verilator

# --- Source Files ---
# Using wildcard to ensure all dependencies are tracked
V_SRCS      = $(wildcard $(V_DIR)/*.v)
CPP_SRCS    = tb_aes_top_iterative.cpp

# --- Logic to select .rsp files based on TEST type ---
ifeq ($(TEST),MCT)
    # Monte Carlo Tests: e.g., ECBMCT128.rsp
    RSP_FILES = $(VECTOR_DIR)/$(MODE)MCT$(KEY_BITS).rsp
else ifeq ($(TEST),MMT)
    # Multi-block Message Tests: e.g., ECBMMT128.rsp
    RSP_FILES = $(VECTOR_DIR)/$(MODE)MMT$(KEY_BITS).rsp
else
    # KAT (Known Answer Tests): Matches VarTxt and VarKey
    RSP_FILES = $(VECTOR_DIR)/$(MODE)Var*$(KEY_BITS).rsp
endif

# --- Verilator Flags ---
VFLAGS      = --cc --exe --build -j 0 --trace
VFLAGS     += -y $(V_DIR)
VFLAGS     += --top-module $(TOP_MODULE)
VFLAGS     += --trace-max-array 1024
# Pass parameters to Verilog
VFLAGS     += -GKEY_BITS=$(KEY_BITS) 
VFLAGS     += -GSBOX_IMPL=\"$(SBOX_IMPL)\" 
VFLAGS     += -GDUPLEX=\"$(DUPLEX)\"
# Pass parameters to C++
VFLAGS     += -CFLAGS "-DKEY_BITS=$(KEY_BITS) -DSBOX_IMPL=\"$(SBOX_IMPL)\" -DDUPLEX=\"$(DUPLEX)\" -DTEST_$(TEST)"

# The generated executable
TARGET     = obj_dir/V$(TOP_MODULE)

# --- Targets ---
.PHONY: all build run clean help

all: build run

# 1. Generate the header file via Python
# We force this to run if the RSP_FILES list changes or if a parameter is passed
$(VECTORS_H): $(PARSE_SCRIPT) $(RSP_FILES)
	@echo "--- Generating Test Vectors: [$(TEST)] $(MODE) $(KEY_BITS)-bit ---"
	@if [ -z "$(RSP_FILES)" ]; then echo "Error: No .rsp files found for $(TEST)"; exit 1; fi
	$(PYTHON) $(PARSE_SCRIPT) $(RSP_FILES) > $(VECTORS_H)

# 2. Build depends on vectors.h and source files
build: $(VECTORS_H) $(TARGET)

$(TARGET): $(V_SRCS) $(CPP_SRCS) $(VECTORS_H)
	@echo "--- Building Simulation for $(DUPLEX) Duplex / $(SBOX_IMPL) ---"
	$(VERILATOR) $(VFLAGS) $(V_SRCS) $(CPP_SRCS)

# 3. Run
run: $(TARGET)
	@echo "--- Running Simulation: $(TEST) ---"
	./$(TARGET)

# 4. Help
help:
	@echo ""
	@echo "Usage: make [PARAMETER=VALUE]"
	@echo ""
	@echo "Parameters:"
	@echo "  TEST       : KAT, MCT, MMT  (Current: $(TEST))"
	@echo "  KEY_BITS   : 128, 192, 256  (Current: $(KEY_BITS))"
	@echo "  SBOX_IMPL  : LUT, CANRIGHT  (Current: $(SBOX_IMPL))"
	@echo "  DUPLEX     : HALF, FULL     (Current: $(DUPLEX))"
	@echo "  MODE       : ECB            (Current: $(MODE))"
	@echo ""
	@echo "Examples:"
	@echo "  make TEST=MCT KEY_BITS=256"
	@echo "  make TEST=KAT DUPLEX=FULL SBOX_IMPL=CANRIGHT"
	@echo ""

# 5. Cleanup
clean:
	@echo "--- Cleaning up ---"
	rm -rf obj_dir
	rm -f *.vcd
	rm -f $(VECTORS_H)
