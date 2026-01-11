#ifndef FIXED_POINT_MATH_H
#define FIXED_POINT_MATH_H

#include "defines.h"

/*
 * Fixed-Point Math Library
 * Processor-independent mathematical functions for fixed-point arithmetic
 * Supports Q1.7, Q1.14, and Q1.30 formats
 */

/* ========================================================================
 * Q1.7 Format Functions
 * ======================================================================== */

/* Trigonometric functions */
q1_7_t q1_7_sin(q1_7_t angle);
q1_7_t q1_7_cos(q1_7_t angle);
q1_7_t q1_7_tan(q1_7_t angle);

/* Inverse trigonometric functions */
q1_7_t q1_7_asin(q1_7_t value);
q1_7_t q1_7_acos(q1_7_t value);
q1_7_t q1_7_atan(q1_7_t value);

/* Other mathematical functions */
q1_7_t q1_7_sqrt(q1_7_t value);
q1_7_t q1_7_inverse(q1_7_t value);
q1_7_t q1_7_log(q1_7_t value);
q1_7_t q1_7_exp(q1_7_t value);

/* ========================================================================
 * Q1.14 Format Functions
 * ======================================================================== */

/* Trigonometric functions */
q1_14_t q1_14_sin(q1_14_t angle);
q1_14_t q1_14_cos(q1_14_t angle);
q1_14_t q1_14_tan(q1_14_t angle);

/* Inverse trigonometric functions */
q1_14_t q1_14_asin(q1_14_t value);
q1_14_t q1_14_acos(q1_14_t value);
q1_14_t q1_14_atan(q1_14_t value);

/* Other mathematical functions */
q1_14_t q1_14_sqrt(q1_14_t value);
q1_14_t q1_14_inverse(q1_14_t value);
q1_14_t q1_14_log(q1_14_t value);
q1_14_t q1_14_exp(q1_14_t value);

/* ========================================================================
 * Q1.30 Format Functions
 * ======================================================================== */

/* Trigonometric functions */
q1_30_t q1_30_sin(q1_30_t angle);
q1_30_t q1_30_cos(q1_30_t angle);
q1_30_t q1_30_tan(q1_30_t angle);

/* Inverse trigonometric functions */
q1_30_t q1_30_asin(q1_30_t value);
q1_30_t q1_30_acos(q1_30_t value);
q1_30_t q1_30_atan(q1_30_t value);

/* Other mathematical functions */
q1_30_t q1_30_sqrt(q1_30_t value);
q1_30_t q1_30_inverse(q1_30_t value);
q1_30_t q1_30_log(q1_30_t value);
q1_30_t q1_30_exp(q1_30_t value);

#endif /* FIXED_POINT_MATH_H */
