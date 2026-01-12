#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>
// #include <stdbool.h>

#define FIXED_POINT_MATH_VERSION_MAJOR 1
#define FIXED_POINT_MATH_VERSION_MINOR 0

#define LN2_APPROX 0.6931471805599453
#define INV_LN2_APPROX 1.4426950408889634

/*
 * Fixed-Point Format Definitions
 * Q format: Qm.n where m = integer bits, n = fractional bits
 * Total bits = m + n + 1 (sign bit)
 */

/* Q1.14 or fp16 format*/

typedef int16_t fp16_t;
#define FP16_FRACTIONAL_BITS 14
#define FP16_INTEGER_BITS 1
#define FP16_TOTAL_BITS (1 + FP16_INTEGER_BITS + FP16_FRACTIONAL_BITS)
#define FP16_FRACTIONAL_MASK ((1u << FP16_FRACTIONAL_BITS) - 1u)
#define FP16_ONE_VALUE (1 << FP16_FRACTIONAL_BITS)
#define FP16_MAX_VALUE ((1 << (FP16_INTEGER_BITS + FP16_FRACTIONAL_BITS)) - 1)
#define FP16_MIN_VALUE (-(1 << (FP16_INTEGER_BITS + FP16_FRACTIONAL_BITS)))
#define FP16_INV_LN2_APPROX 23637 /* Approximation of (1/ln(2)) * 2^14 */
#define FP16_LN2_APPROX 11356     /* Approximation of ln(2) * 2^14 */

/* Q1.30 or fp32 format */
typedef int32_t fp32_t;
#define FP32_FRACTIONAL_BITS 30
#define FP32_INTEGER_BITS 1
#define FP32_TOTAL_BITS (1 + FP32_INTEGER_BITS + FP32_FRACTIONAL_BITS)
#define FP32_FRACTIONAL_MASK ((1u << FP32_FRACTIONAL_BITS) - 1u)
#define FP32_ONE_VALUE (1 << FP32_FRACTIONAL_BITS)
#define FP32_MAX_VALUE ((1 << (FP32_INTEGER_BITS + FP32_FRACTIONAL_BITS)) - 1)
#define FP32_MIN_VALUE (-(1 << (FP32_INTEGER_BITS + FP32_FRACTIONAL_BITS)))
#define FP32_INV_LN2_APPROX 1547425049 /* Approximation of (1/ln(2)) * 2^30 */
#define FP32_LN2_APPROX 742487         // Approximation of ln(2) * 2^30
#endif                                 /* DEFINES_H */
