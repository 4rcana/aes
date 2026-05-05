# --- Parameters (Default values) ---
KEY_BITS   ?= 128
SBOX_ARCH  ?= LUT
DUPLEX     ?= HALF
PIPE_DEPTH ?= 1
MODE       ?= ECB
TEST       ?= KAT

# =================================================================
# Parameter Mapping (Convert text to Enum Integers for RTL)
# =================================================================

# SBOX_ARCH: LUT=0, CANRIGHT=1
ifeq ($(SBOX_ARCH),CANRIGHT)
    SBOX_VAL = 1
else
    SBOX_VAL = 0
endif

# DUPLEX: HALF=0, FULL=1
ifeq ($(DUPLEX),FULL)
    DUP_VAL = 1
else
    DUP_VAL = 0
endif

# MODE: ECB=0, CBC=1
ifeq ($(MODE),CBC)
    MODE_VAL = 1
else
    MODE_VAL = 0
endif

# =================================================================

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
V_SRCS      = $(wildcard $(V_DIR)/*.sv)
CPP_SRCS    = tb_aes_top_iterative.cpp

# --- Logic to select .rsp files based on TEST type ---
ifeq ($(TEST),MCT)
    RSP_FILES = $(VECTOR_DIR)/$(MODE)MCT$(KEY_BITS).rsp
else ifeq ($(TEST),MMT)
    RSP_FILES = $(VECTOR_DIR)/$(MODE)MMT$(KEY_BITS).rsp
else
    RSP_FILES = $(VECTOR_DIR)/$(MODE)Var*$(KEY_BITS).rsp
endif

# --- Verilator Flags ---
VFLAGS      = --cc --exe --build -j 0 --trace
VFLAGS     += -y $(V_DIR)
VFLAGS     += --top-module $(TOP_MODULE)
VFLAGS     += --trace-max-array 1024

# Pass the MAPPED INTEGER values to Verilog Parameters
VFLAGS     += -GKEY_BITS=$(KEY_BITS) 
VFLAGS     += -GSBOX_ARCH=$(SBOX_VAL) 
VFLAGS     += -GDUPLEX=$(DUP_VAL)
VFLAGS     += -GMODE=$(MODE_VAL)

# Pass string defines to C++ (Keep these as strings for C++ logic if needed)
CPP_DEFINES += -DKEY_BITS=$(KEY_BITS)
CPP_DEFINES += -DSBOX_ARCH=\"$(SBOX_ARCH)\"
CPP_DEFINES += -DDUPLEX=\"$(DUPLEX)\"
CPP_DEFINES += -DMODE=\"$(MODE)\"
CPP_DEFINES += -DTEST_$(TEST)

VFLAGS 		+= -CFLAGS "$(CPP_DEFINES)"

# The generated executable
TARGET     = obj_dir/V$(TOP_MODULE)

# --- Targets ---
.PHONY: all build run clean help

all: build run

# 1. Generate the header file via Python
$(VECTORS_H): $(PARSE_SCRIPT) $(RSP_FILES)
	@echo "--- Generating Test Vectors: [$(TEST)] $(MODE) $(KEY_BITS)-bit ---"
	@if [ -z "$(RSP_FILES)" ]; then echo "Error: No .rsp files found for $(TEST)"; exit 1; fi
	$(PYTHON) $(PARSE_SCRIPT) $(RSP_FILES) > $(VECTORS_H)

# 2. Build depends on vectors.h and source files
build: $(VECTORS_H) $(TARGET)

$(TARGET): $(V_SRCS) $(CPP_SRCS) $(VECTORS_H)
	@echo "--- Building Simulation for $(DUPLEX) Duplex / $(SBOX_ARCH) ---"
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
	@echo "  SBOX_ARCH  : LUT, CANRIGHT  (Current: $(SBOX_ARCH))"
	@echo "  DUPLEX     : HALF, FULL     (Current: $(DUPLEX))"
	@echo "  MODE       : ECB, CBC       (Current: $(MODE))"
	@echo ""
	@echo "Examples:"
	@echo "  make TEST=MCT KEY_BITS=256"
	@echo "  make TEST=KAT DUPLEX=FULL SBOX_ARCH=CANRIGHT"
	@echo ""

# 5. Cleanup
clean:
	@echo "--- Cleaning up ---"
	rm -rf obj_dir
	rm -f *.vcd
	rm -f $(VECTORS_H)
