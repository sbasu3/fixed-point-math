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
	@echo "  all       - Build the library (default)"
	@echo "  tests     - Build test executables"
	@echo "  test      - Build and run tests"
	@echo "  clean     - Remove build artifacts"
	@echo "  install   - Install library and headers to /usr/local"
	@echo "  uninstall - Remove installed library and headers"
	@echo "  help      - Show this help message"
