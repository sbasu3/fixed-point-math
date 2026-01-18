# fixed-point-math

A processor-independent fixed-point math library suitable for microcontrollers with no FPU (Floating Point Unit).

## Overview

This library provides fast, accurate mathematical functions using fixed-point arithmetic instead of floating-point operations. It's ideal for embedded systems and microcontrollers where hardware floating-point support is unavailable or too slow.

### Features

- **Q1.14 Format (fp16_t)**: 16-bit fixed-point with 1 sign bit, 1 integer bit, 14 fractional bits (range: [-2.0, ~1.999])
- **Q1.30 Format (fp32_t)**: 32-bit fixed-point with 1 sign bit, 1 integer bit, 30 fractional bits
- **Core Functions**:
  - `fp16_poly_exp(x)` - Exponential function using polynomial approximation
  - `fp16_ln(x)` - Natural logarithm using Taylor series
  - `fp16_inverse(x)` - Reciprocal (1/x) using Newton-Raphson iteration
  - `fp16_sqrt(x)` - Square root using Newton-Raphson iteration
- **Range-Extended Wrappers**:
  - `fp16_float_exp(x)` / `fp16_double_exp(x)` - Extended range exponential
  - `fp16_float_ln(x)` / `fp16_double_ln(x)` - Extended range logarithm
- **Utility Functions**:
  - Conversions between fixed-point and floating-point formats
  - Type definitions and constants

### Performance

Benchmarks on typical x86-64 systems:
- `fp16_ln`: ~1 ns per call (954M calls/sec)
- `fp16_inverse`: ~5 ns per call (189M calls/sec)
- `fp16_sqrt`: ~6 ns per call (170M calls/sec)
- `fp16_float_exp`: ~3 ns per call (347M calls/sec)
- `fp16_float_ln`: ~3.4 ns per call (295M calls/sec)

## Dependencies

### Build Requirements

- **C Compiler**: GCC or compatible compiler with C99 support
- **Make**: GNU Make or compatible build system
- **Standard C Library**: For `<stdint.h>`, `<stdio.h>`, `<math.h>` (test only), `<time.h>` (test only)
- **Math Library**: `-lm` flag required for linking (libm)

### Runtime Requirements

- **No floating-point hardware required** for core fixed-point functions
- **No external dependencies** - fully self-contained library
- Minimal memory footprint (suitable for embedded systems)

## Installation

### Building the Library

```bash
# Build the static library
make

# Build with tests
make tests

# Run all tests
make test

# Run specific test suites
make test_ln_range      # Test ln function in range [-0.5, 0.5]
make test_inverse       # Test inverse (1/x) function
make test_sqrt          # Test square root function
make test_wrapper       # Test range-extended wrapper functions
```

The build process creates:
- `build/lib/libfixedpointmath.a` - Static library
- `build/bin/test_*` - Test executables
- `build/obj/*.o` - Object files

### Clean Build

```bash
make clean    # Remove all build artifacts
```

## Usage

### Basic Example

```c
#include "fixed-point-math.h"
#include "util.h"

int main(void) {
    // Convert floating-point to fixed-point
    fp16_t x = double_to_fp16(0.5);
    
    // Calculate ln(1 + 0.5) = ln(1.5)
    fp16_t result = fp16_ln(x);
    
    // Convert back to floating-point
    double result_double = fp16_to_double(result);
    
    printf("ln(1.5) = %.6f\n", result_double);
    // Output: ln(1.5) = 0.405465
    
    return 0;
}
```

### Using Core Functions

```c
#include "fixed-point-math.h"
#include "util.h"

// Exponential: exp(0.5)
fp16_t x = double_to_fp16(0.5);
fp16_t exp_result = fp16_poly_exp(x);

// Natural logarithm: ln(1 + 0.3)
fp16_t y = double_to_fp16(0.3);
fp16_t ln_result = fp16_ln(y);

// Inverse: 1 / 1.5
fp16_t z = double_to_fp16(1.5);
fp16_t inv_result = fp16_inverse(z);

// Square root: sqrt(1.5)
fp16_t w = double_to_fp16(1.5);
fp16_t sqrt_result = fp16_sqrt(w);
```

### Using Range-Extended Wrappers

For values outside the Q1.14 range, use the wrapper functions:

```c
#include "fp16_wrapper.h"

// Extended range exponential: exp(3.0)
float exp_3 = fp16_float_exp(3.0f);

// Extended range logarithm: ln(10.0)
float ln_10 = fp16_float_ln(10.0f);

// Double precision versions
double exp_large = fp16_double_exp(5.0);
double ln_large = fp16_double_ln(100.0);
```

### Compiling Your Application

```bash
# Compile with the static library
gcc -Wall -O2 -Iinclude -o myapp myapp.c build/lib/libfixedpointmath.a -lm

# Or link against object files directly
gcc -Wall -O2 -Iinclude -o myapp myapp.c \
    build/obj/fixed-point-math.o \
    build/obj/util.o \
    build/obj/fp16_wrapper.o -lm
```

## Function Reference

### Core Fixed-Point Functions

#### `fp16_t fp16_poly_exp(fp16_t x)`
- **Description**: Exponential function using 3rd-degree polynomial approximation
- **Input Range**: x ∈ [-ln(2), ln(2)] ≈ [-0.693, 0.693]
- **Accuracy**: Error < 0.01 within range
- **Use Case**: Fast exp() for restricted domain

#### `fp16_t fp16_ln(fp16_t x)`
- **Description**: Natural logarithm using 4th-degree Taylor series for ln(1+x)
- **Input Range**: x ∈ [-0.5, 0.5]
- **Output**: ln(1+x)
- **Accuracy**: Error < 0.01 within range
- **Use Case**: Fast ln() for values near 1.0

#### `fp16_t fp16_inverse(fp16_t x)`
- **Description**: Reciprocal using 5-iteration Newton-Raphson
- **Input Range**: Any non-zero Q1.14 value
- **Accuracy**: Error < 0.02
- **Use Case**: Division without hardware divider

#### `fp16_t fp16_sqrt(fp16_t x)`
- **Description**: Square root using 5-iteration Newton-Raphson
- **Input Range**: x ≥ 0
- **Accuracy**: Error < 0.002
- **Use Case**: Fast sqrt() for positive values

### Range-Extended Wrapper Functions

#### `float fp16_float_exp(float x)` / `double fp16_double_exp(double x)`
- **Description**: Exponential with extended range via range reduction
- **Method**: exp(x) = 2^k · exp(r) where x = k·ln(2) + r
- **Input Range**: Limited by overflow/underflow of result type
- **Use Case**: General-purpose exponential

#### `float fp16_float_ln(float x)` / `double fp16_double_ln(double x)`
- **Description**: Logarithm with extended range via normalization
- **Method**: ln(x) = k·ln(2) + ln(r) where x = 2^k · r, r ∈ [1, 2]
- **Input Range**: x > 0
- **Use Case**: General-purpose logarithm

### Utility Functions

```c
// Fixed-point to floating-point conversions
float fp16_to_float(fp16_t x);
double fp16_to_double(fp16_t x);

// Floating-point to fixed-point conversions
fp16_t float_to_fp16(float x);
fp16_t double_to_fp16(double x);
```

## Testing

The library includes comprehensive test suites with functional tests and performance benchmarks:

```bash
# Run all tests
make test

# Run individual test suites
make test_ln_range    # 12 tests for ln function
make test_inverse     # 12 tests for inverse function
make test_sqrt        # 12 tests for sqrt function
make test_wrapper     # 14 tests for wrapper functions
```

Each test suite includes:
- Functional correctness tests with error bounds
- Edge case validation
- Performance benchmarks with throughput and latency metrics
- Per-value latency breakdown

## Implementation Details

### Fixed-Point Formats

**Q1.14 (fp16_t)**:
- 1 sign bit, 1 integer bit, 14 fractional bits
- Range: [-2.0, 1.99993896484375]
- Resolution: 2^-14 ≈ 0.000061
- Integer value: `x_int = x_double * 2^14`

**Q1.30 (fp32_t)**:
- 1 sign bit, 1 integer bit, 30 fractional bits  
- Range: [-2.0, 1.9999999990686774]
- Resolution: 2^-30 ≈ 9.31e-10

### Algorithms

- **Exponential**: Polynomial approximation optimized for [-ln(2), ln(2)]
- **Logarithm**: Taylor series ln(1+x) = x - x²/2 + x³/3 - x⁴/4 + ...
- **Inverse**: Newton-Raphson x_{n+1} = x_n(2 - a·x_n)
- **Square Root**: Newton-Raphson x_{n+1} = (x_n + S/x_n)/2
- **Range Reduction**: Mathematical identities to extend operational range

## License

[Specify your license here]

## Contributing

Contributions are welcome! Please ensure:
- Code follows C99 standard
- All tests pass (`make test`)
- New functions include test coverage
- Performance benchmarks included for new operations

## Authors

[Specify authors here]
