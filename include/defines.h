#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>

#define FIXED_POINT_MATH_VERSION_MAJOR 1
#define FIXED_POINT_MATH_VERSION_MINOR 0

#define LN2_APPROX 0.6931471805599453
#define INV_LN2_APPROX 1.4426950408889634

#define CONCAT(a, b) a##b
#define STRINGIFY(x) #x

/*
 * Fixed-Point Format Definitions
 * Q format: Qm.n where m = integer bits, n = fractional bits
 * Total bits = m + n + 1 (sign bit)
 */

/* Q1.6 format: 1 sign bit, 1 integer bit, 6 fractional bits (8-bit total) */
typedef int8_t Q1_6_t;
typedef int16_t DOUBLE_Q1_6_t; /* For intermediate calculations */
#define Q1_6_FRACTIONAL_BITS 6
#define DOUBLE_Q1_6_FRACTIONAL_BITS (2 * Q1_6_FRACTIONAL_BITS)
#define Q1_6_FRACTIONAL_MASK ((1 << Q1_6_FRACTIONAL_BITS) - 1)
#define DOUBLE_Q1_6_FRACTIONAL_MASK ((1 << DOUBLE_Q1_6_FRACTIONAL_BITS) - 1)
#define Q1_6_ONE (1 << Q1_6_FRACTIONAL_BITS)
#define DOUBLE_Q1_6_ONE (1 << DOUBLE_Q1_6_FRACTIONAL_BITS)
#define Q1_6_MAX_VALUE ((1 << (1 + 6)) - 1)            /* 0b01111111 = 127 */
#define DOUBLE_Q1_6_MAX_VALUE ((1 << (1 + 2 * 6)) - 1) /* 0b011111111111111 = 16383 */
#define Q1_6_MIN_VALUE (-(1 << (1 + 6)))               /* 0b10000000 = -128 */
#define DOUBLE_Q1_6_MIN_VALUE (-(1 << (1 + 2 * 6)))    /* 0b100000000000000 = -16384 */
#define Q1_6_EPSILON (1.0f / (1 << Q1_6_FRACTIONAL_BITS))
#define DOUBLE_Q1_6_EPSILON (1.0f / (1 << DOUBLE_Q1_6_FRACTIONAL_BITS))
#define Q1_6_LN2_APPROX (Q1_6_t)(LN2_APPROX * Q1_6_ONE)
#define Q1_6_INV_LN2_APPROX (Q1_6_t)(INV_LN2_APPROX * Q1_6_ONE)

/* Q1.14 format: 1 sign bit, 1 integer bit, 14 fractional bits (16-bit total) */
typedef int16_t Q1_14_t;
typedef int32_t DOUBLE_Q1_14_t; /* For intermediate calculations */
#define Q1_14_FRACTIONAL_BITS 14
#define DOUBLE_Q1_14_FRACTIONAL_BITS (2 * Q1_14_FRACTIONAL_BITS)
#define Q1_14_FRACTIONAL_MASK ((1 << Q1_14_FRACTIONAL_BITS) - 1)
#define DOUBLE_Q1_14_FRACTIONAL_MASK ((1 << DOUBLE_Q1_14_FRACTIONAL_BITS) - 1)
#define Q1_14_ONE (1 << Q1_14_FRACTIONAL_BITS)
#define DOUBLE_Q1_14_ONE (1 << DOUBLE_Q1_14_FRACTIONAL_BITS)
#define Q1_14_MAX_VALUE ((1 << (1 + 14)) - 1)            /* 0b0111111111111111 = 32767 */
#define DOUBLE_Q1_14_MAX_VALUE ((1 << (1 + 2 * 14)) - 1) /* 0b01111111111111111111111111111111 = 1073741823 */
#define Q1_14_MIN_VALUE (-(1 << (1 + 14)))               /* 0b1000000000000000 = -32768 */
#define DOUBLE_Q1_14_MIN_VALUE (-(1 << (1 + 2 * 14)))    /* 0b10000000000000000000000000000000 = -1073741824 */
#define Q1_14_EPSILON (1.0f / (1 << Q1_14_FRACTIONAL_BITS))
#define DOUBLE_Q1_14_EPSILON (1.0f / (1 << DOUBLE_Q1_14_FRACTIONAL_BITS))
#define Q1_14_LN2_APPROX (Q1_14_t)(LN2_APPROX * Q1_14_ONE)
#define Q1_14_INV_LN2_APPROX (Q1_14_t)(INV_LN2_APPROX * Q1_14_ONE)

/* Q1.30 format: 1 sign bit, 1 integer bit, 30 fractional bits (32-bit total) */
typedef int32_t Q1_30_t;
typedef int64_t DOUBLE_Q1_30_t; /* Alias for Q1.30 format */
#define Q1_30_FRACTIONAL_BITS 30
#define DOUBLE_Q1_30_FRACTIONAL_BITS (2 * Q1_30_FRACTIONAL_BITS)
#define Q1_30_FRACTIONAL_MASK ((1 << Q1_30_FRACTIONAL_BITS) - 1)
#define DOUBLE_Q1_30_FRACTIONAL_MASK ((1LL << DOUBLE_Q1_30_FRACTIONAL_BITS) - 1)
#define Q1_30_ONE (1 << Q1_30_FRACTIONAL_BITS)
#define DOUBLE_Q1_30_ONE (1LL << DOUBLE_Q1_30_FRACTIONAL_BITS)
#define Q1_30_MAX_VALUE ((1LL << (1 + 30)) - 1) /* 0b01111111111111111111111111111111 = 1073741823 */
#define DOUBLE_Q1_30_MAX_VALUE ((1LL << (1 + 2 * 30)) - 1)
#define Q1_30_MIN_VALUE (-(1LL << (1 + 30)))
#define DOUBLE_Q1_30_MIN_VALUE (-(1LL << (1 + 2 * 30)))
#define Q1_30_EPSILON (1.0f / (1 << Q1_30_FRACTIONAL_BITS))
#define DOUBLE_Q1_30_EPSILON (1.0f / (1LL << DOUBLE_Q1_30_FRACTIONAL_BITS))
#define Q1_30_LN2_APPROX (Q1_30_t)(LN2_APPROX * Q1_30_ONE)
#define Q1_30_INV_LN2_APPROX (Q1_30_t)(INV_LN2_APPROX * Q1_30_ONE)

#endif /* DEFINES_H */
