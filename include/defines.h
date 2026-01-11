#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>

/*
 * Fixed-Point Format Definitions
 * Q format: Qm.n where m = integer bits, n = fractional bits
 * Total bits = m + n + 1 (sign bit)
 */

/* Q1.7 format: 1 sign bit, 1 integer bit, 7 fractional bits (8-bit total) */
typedef int8_t q1_7_t;
#define Q1_7_FRACTIONAL_BITS 7
#define Q1_7_ONE (1 << Q1_7_FRACTIONAL_BITS)

/* Q1.14 format: 1 sign bit, 1 integer bit, 14 fractional bits (16-bit total) */
typedef int16_t q1_14_t;
#define Q1_14_FRACTIONAL_BITS 14
#define Q1_14_ONE (1 << Q1_14_FRACTIONAL_BITS)

/* Q1.30 format: 1 sign bit, 1 integer bit, 30 fractional bits (32-bit total) */
typedef int32_t q1_30_t;
#define Q1_30_FRACTIONAL_BITS 30
#define Q1_30_ONE (1 << Q1_30_FRACTIONAL_BITS)

#endif /* DEFINES_H */
