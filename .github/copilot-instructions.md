# Copilot Instructions: Fixed-Point Math Library

## Project Overview
A processor-independent C library providing fast, accurate mathematical functions using fixed-point arithmetic instead of floating-point operations. Ideal for embedded systems and microcontrollers without FPU hardware.

**Key Formats:**
- **Q1.14 (fp16_t)**: 16-bit signed, range [-2.0, ~1.999], used for core functions
- **Q1.30 (fp32_t)**: 32-bit signed, higher precision variant
- Constants in `include/defines.h` (e.g., `FP16_FRACTIONAL_BITS=14`, `FP16_ONE_VALUE=16384`)

## Architecture

### Core Components
1. **src/fixed-point-math.c** - Base transcendental functions
   - `fp16_poly_exp()`: Polynomial approximation for exp(x), domain [-ln(2), ln(2)]
   - `fp16_ln()`: Taylor series ln(1+x), domain [-0.5, 0.5]
   - `fp16_inverse()`: Newton-Raphson for 1/x, 5 iterations
   - `fp16_sqrt()`: Newton-Raphson for sqrt(x), 5 iterations

2. **src/fp16_wrapper.c** - Range-extended wrappers using mathematical identities
   - `fp16_float_exp/fp16_double_exp`: Range reduction via exp(x) = 2^k · exp(r) where x = k·ln(2) + r
   - `fp16_float_ln/fp16_double_ln`: Range normalization via ln(x) = k·ln(2) + ln(r) where x = 2^k · r

3. **src/fp16_cordic.c** - CORDIC-based trigonometric functions
   - `cordic_sin/cordic_cos`: Rotation mode CORDIC with Q1.14 gain factor (0x26D7 ≈ 0.607)
   - `cordic_atan2`: Vectoring mode CORDIC for angle computation

4. **src/util.c** - Conversion utilities
   - `float_to_fp16/double_to_fp16`: Floating-point to fixed-point
   - `fp16_to_float/fp16_to_double`: Fixed-point to floating-point

### Test Organization
Each function has dedicated test file with structure:
- **Functional tests**: Domain-specific test cases with error bounds
- **Performance benchmarks**: Throughput (calls/sec) and latency (nanoseconds)
- **Tolerances**: Set to match algorithm accuracy within fixed-point constraints

Example: `test/test_fp16_ln_range.c` - 12 tests for ln(1+x) in [-0.5, 0.5] + benchmarks (~1.05 ns/call)

## Development Workflow

### Build Commands
```bash
make              # Build library to build/lib/libfixedpointmath.a
make test         # Build and run ALL tests
make test_ln_range test_inverse test_sqrt test_wrapper test_cordic  # Run specific tests
make clean        # Remove build artifacts
```

### Adding New Functions
1. **Implement** in `src/new_function.c`
2. **Declare** in `include/new_function.h` (include `defines.h`)
3. **Add header** to `src/fixed-point-math.c` includes if applicable
4. **Create test** file `test/test_new_function.c` with:
   - At least 12 functional tests
   - Error tolerance checks
   - Performance benchmark (100k+ iterations)
   - `#ifndef M_E/#define M_E 2.71828...` guard for C99 compatibility
5. **Update Makefile** with `test_new_function` target and build rule
6. **Verify**: `make test_new_function` passes with exit code 0

### Testing Philosophy
- **Error tolerances** are ABSOLUTE (not relative) to reflect fixed-point precision limitations
- **Benchmark reporting**: throughput in calls/sec, latency in nanoseconds (scaled by 1e9)
- **All tests must pass** with `make test` - failures cause non-zero exit code

## Key Patterns & Conventions

### Fixed-Point Arithmetic
- **Bit-shift operations** (`x >> i`, `y >> i`) for division by powers of 2 (preserves precision)
- **Sign extension** handled automatically by signed types
- **Overflow prevention**: Use constants like `CORDIC_GAIN_FP16 ((fp16_t)0x26D7)` with explicit casts to avoid compiler warnings
- **Range scaling**: Multiply by `FP16_ONE_VALUE` (16384) to convert from floating-point or use conversion functions

### Algorithm Implementation Notes

**Range Reduction (wrappers):**
- exp(x): Reduce to [-ln(2), ln(2)] via k = round(x/ln(2)), then exp(x) = 2^k · exp(x - k·ln(2))
- ln(x): Normalize to [1, 2] via bit shifts, then ln(x) = k·ln(2) + ln(normalized)
- **Critical**: Must convert fp16 results to floating-point BEFORE scaling by 2^k (not bit-shift)

**Newton-Raphson (inverse, sqrt):**
- Fixed iteration count (5) for predictable latency
- Initial guesses matter: `inverse`: ONE²/x, `sqrt`: x/2
- Early termination: Not used (fixed iterations for deterministic behavior)

**CORDIC (trig functions):**
- 14 iterations for Q1.14 precision (atan_table_fp16[14])
- Gain factor pre-baked into initial x: `x = CORDIC_GAIN_FP16` then y-component = sin(z)
- For cosine: Same rotation, return x-component instead
- For atan2: Vectoring mode, initialize z=0, rotate (x,y) to x-axis

### Compiler Flags
Always use: `-Wall -Wextra -Werror -std=c99 -pedantic -O2 -lm`
- `-std=c99` required for some fixed-point code
- `-lm` needed for test utilities (sin, cos, log, atan2, sqrt from libm)
- Strict mode catches integer overflow warnings → explicit casts in macro constants

## Common Pitfalls

1. **Forgetting header includes**: New functions need full include chain (defines.h → fp16_xxx.h)
2. **Tolerance mismatches**: Adjusting test tolerances without fixing implementation. Benchmark first, then adjust tolerances to algorithm accuracy
3. **Bit-shift vs arithmetic**: Don't use bit-shifts for wrapping - use multiplication/division with floating-point intermediate
4. **Missing test structure**: Tests need both correctness checks AND performance benchmarks
5. **Signed/unsigned mixing**: Use explicit casts when combining int16_t and uint8_t (CORDIC iterations)

## Performance Targets
Typical latencies on x86-64 (for reference):
- `fp16_ln`: ~1 ns (950M calls/sec)
- `fp16_inverse`: ~5 ns (189M calls/sec)  
- `fp16_sqrt`: ~6 ns (170M calls/sec)
- `cordic_sin/cos`: ~5.7 ns (175M calls/sec)
- `cordic_atan2`: ~5.9 ns (169M calls/sec)

Slower performance on embedded targets - focus on correctness and predictable latency (fixed iterations).

## File Organization
```
include/defines.h          # Q1.14/Q1.30 format definitions, constants
include/fixed-point-math.h # Core function declarations
include/fp16_wrapper.h     # Range-extended wrapper declarations
include/fp16_cordic.h      # CORDIC function declarations
include/util.h             # Conversion utilities
src/fixed-point-math.c     # Core implementations
src/fp16_wrapper.c         # Wrapper implementations
src/fp16_cordic.c          # CORDIC implementations
src/util.c                 # Conversion implementations
test/test_*.c              # One file per function/module with comprehensive tests
Makefile                   # Build rules (auto-detects test files)
```
