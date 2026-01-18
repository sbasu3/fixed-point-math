#ifndef FIXED_POINT_MATH_H
#define FIXED_POINT_MATH_H

#include "defines.h"

/*
 * Fixed-Point Math Library
 * Processor-independent mathematical functions for fixed-point arithmetic
 * Supports Q1.14 (fp16) and Q1.30 (fp32) formats
 */

/* ========================================================================
 * Function Declarations
 * ======================================================================== */
// Exponential Function using Polynomial Approximation
// Using 3rd-degree polynomial approximation
// Input: x in Q1.14 format (fp16_t)
// Output: exp(x) in Q1.14 format (fp16_t)
// Range: x in [-ln(2), ln(2)]
fp16_t fp16_poly_exp(fp16_t x);
// Natural Logarithm Function using Polynomial Approximation
// Using 4th-degree polynomial approximation for ln(1+x)
// Input: x in Q1.14 format (fp16_t), representing values in (-1, 1]
// Output: ln(1+x) in Q1.14 format (fp16_t)
// Range: x in (-0.5, 0.5]
fp16_t fp16_ln(fp16_t x);
// Inverse Function using Newton-Raphson Method
// Input: x in Q1.14 format (fp16_t)
// Output: 1/x in Q1.14 format (fp16_t)
// Range: x in [FP16_MIN_VALUE, FP16_MAX_VALUE] excluding [-0.5, 0.5]
fp16_t fp16_inverse(fp16_t x);
// Square Root Function using Newton-Raphson Method
// Input: x in Q1.14 format (fp16_t), x >= 0
// Output: sqrt(x) in Q1.14 format (fp16_t)
fp16_t fp16_sqrt(fp16_t x);
#endif /* FIXED_POINT_MATH_H */
