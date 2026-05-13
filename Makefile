# Fixed-Point Math Library Makefile
# Processor-agnostic C library build system

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -O2
INCLUDES = -Iinclude
LDFLAGS = 

# Directories
SRC_DIR = src
INC_DIR = include
TEST_DIR = test
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
LIB_DIR = $(BUILD_DIR)/lib

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Test files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_BINARIES = $(patsubst $(TEST_DIR)/%.c,$(BIN_DIR)/%,$(TEST_SOURCES))

# Library name
LIBRARY = $(LIB_DIR)/libfixedpointmath.a

# Default target
.PHONY: all
all: $(LIBRARY)

# Create directories
$(OBJ_DIR) $(BIN_DIR) $(LIB_DIR):
	mkdir -p $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create static library
$(LIBRARY): $(OBJECTS) | $(LIB_DIR)
	ar rcs $@ $^
	@echo "Library created: $@"

# Build tests
.PHONY: tests
tests: $(LIBRARY) $(TEST_BINARIES)

# Compile test executables
$(BIN_DIR)/%: $(TEST_DIR)/%.c $(LIBRARY) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $< $(LIBRARY) -o $@ -lm
	@echo "Test binary created: $@"

# Run tests
.PHONY: test
test: tests
	@echo "Running tests..."
	@for test in $(TEST_BINARIES); do \
		echo "Running $$test..."; \
		$$test || exit 1; \
	done
	@echo "All tests completed."

# Build and run addition tests
.PHONY: test_add
test_add: $(LIBRARY) $(BIN_DIR)/test_q1_6_add $(BIN_DIR)/test_q_add_all $(BIN_DIR)/test_q_arith_ops
	@echo "Running test_q1_6_add..."
	$(BIN_DIR)/test_q1_6_add
	@echo "Running test_q_add_all..."
	$(BIN_DIR)/test_q_add_all
	@echo "Running test_q_arith_ops..."
	$(BIN_DIR)/test_q_arith_ops

# Build and run util conversion tests
.PHONY: test_util
test_util: $(LIBRARY) $(BIN_DIR)/test_util_conversions
	@echo "Running util conversion tests..."
	$(BIN_DIR)/test_util_conversions

# Build and run fp16_exp tests
.PHONY: test_exp
test_exp: $(LIBRARY) $(BIN_DIR)/test_fp16_exp
	@echo "Running fp16_exp tests..."
	$(BIN_DIR)/test_fp16_exp

# Build and run fp16_poly_exp tests
.PHONY: test_poly_exp
test_poly_exp: $(LIBRARY) $(BIN_DIR)/test_fp16_poly_exp
	@echo "Running fp16_poly_exp tests..."
	$(BIN_DIR)/test_fp16_poly_exp

# Build and run fp16_ln tests
.PHONY: test_ln
test_ln: $(LIBRARY) $(BIN_DIR)/test_fp16_ln
	@echo "Running fp16_ln tests..."
	$(BIN_DIR)/test_fp16_ln

# Build and run fp16_ln range tests (restricted to -0.5 to 0.5)
.PHONY: test_ln_range
test_ln_range: $(LIBRARY) $(BIN_DIR)/test_fp16_ln_range
	@echo "Running fp16_ln range tests (-0.5 to 0.5)..."
	$(BIN_DIR)/test_fp16_ln_range

# Build rule for test_fp16_ln_range
$(BIN_DIR)/test_fp16_ln_range: $(TEST_DIR)/test_fp16_ln_range.c $(LIBRARY) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< $(LIBRARY) -lm

# Build and run fp16_inverse tests
.PHONY: test_inverse
test_inverse: $(LIBRARY) $(BIN_DIR)/test_fp16_inverse
	@echo "Running fp16_inverse tests..."
	$(BIN_DIR)/test_fp16_inverse

# Build rule for test_fp16_inverse
$(BIN_DIR)/test_fp16_inverse: $(TEST_DIR)/test_fp16_inverse.c $(LIBRARY) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< $(LIBRARY) -lm

# Build and run fp16_sqrt tests
.PHONY: test_sqrt
test_sqrt: $(LIBRARY) $(BIN_DIR)/test_fp16_sqrt
	@echo "Running fp16_sqrt tests..."
	$(BIN_DIR)/test_fp16_sqrt

# Build rule for test_fp16_sqrt
$(BIN_DIR)/test_fp16_sqrt: $(TEST_DIR)/test_fp16_sqrt.c $(LIBRARY) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< $(LIBRARY) -lm

# Build and run fp16_wrapper tests
.PHONY: test_wrapper
test_wrapper: $(LIBRARY) $(BIN_DIR)/test_fp16_wrapper
	@echo "Running fp16_wrapper tests..."
	$(BIN_DIR)/test_fp16_wrapper

# Build rule for test_fp16_wrapper
$(BIN_DIR)/test_fp16_wrapper: $(TEST_DIR)/test_fp16_wrapper.c $(LIBRARY) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< $(LIBRARY) -lm

# Build and run fp16_cordic tests
.PHONY: test_cordic
test_cordic: $(LIBRARY) $(BIN_DIR)/test_fp16_cordic
	@echo "Running fp16_cordic tests..."
	$(BIN_DIR)/test_fp16_cordic

# Build rule for test_fp16_cordic
$(BIN_DIR)/test_fp16_cordic: $(TEST_DIR)/test_fp16_cordic.c $(LIBRARY) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< $(LIBRARY) -lm

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	@echo "Build artifacts cleaned."

# Install library (optional, requires sudo)
.PHONY: install
install: $(LIBRARY)
	@echo "Installing library to /usr/local/lib and headers to /usr/local/include..."
	install -d /usr/local/lib
	install -m 644 $(LIBRARY) /usr/local/lib/
	install -d /usr/local/include/fixedpointmath
	install -m 644 $(INC_DIR)/*.h /usr/local/include/fixedpointmath/
	@echo "Installation complete."

# Uninstall library
.PHONY: uninstall
uninstall:
	rm -f /usr/local/lib/libfixedpointmath.a
	rm -rf /usr/local/include/fixedpointmath
	@echo "Uninstallation complete."

# Help target
.PHONY: help
help:
	@echo "Fixed-Point Math Library Makefile"
	@echo "Available targets:"
	@echo "  all          - Build the library (default)"
	@echo "  tests        - Build test executables"
	@echo "  test         - Build and run all tests"
	@echo "  test_ln_range - Build and run ln range tests"
	@echo "  test_inverse - Build and run inverse function tests"
	@echo "  test_sqrt    - Build and run sqrt function tests"
	@echo "  test_wrapper - Build and run wrapper function tests"
	@echo "  test_cordic  - Build and run CORDIC trigonometric tests"
	@echo "  clean        - Remove build artifacts"
	@echo "  install      - Install library and headers to /usr/local"
	@echo "  uninstall    - Remove installed library and headers"
	@echo "  help         - Show this help message"
