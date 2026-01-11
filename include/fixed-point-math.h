#ifndef FIXED_POINT_MATH_H
#define FIXED_POINT_MATH_H

#include "defines.h"

/*
 * Fixed-Point Math Library
 * Processor-independent mathematical functions for fixed-point arithmetic
 * Supports Q1.6, Q1.14, and Q1.30 formats
 */

/* ========================================================================
 * Generic Function Template Macros
 * These macros generate function declarations for all fixed-point formats
 * ======================================================================== */

#define DECLARE_FIXED_POINT_FUNCTIONS(Q_FORMAT)          \
    /* Conversion functions */                           \
    Q_FORMAT##_t Q_FORMAT##_from_float(float value);     \
    Q_FORMAT##_t Q_FORMAT##_from_double(double value);   \
    float Q_FORMAT##_to_float(Q_FORMAT##_t value);       \
    double Q_FORMAT##_to_double(Q_FORMAT##_t value);     \
                                                         \
    /* Trigonometric functions */                        \
    Q_FORMAT##_t Q_FORMAT##_sin(Q_FORMAT##_t angle);     \
    Q_FORMAT##_t Q_FORMAT##_cos(Q_FORMAT##_t angle);     \
    Q_FORMAT##_t Q_FORMAT##_tan(Q_FORMAT##_t angle);     \
                                                         \
    /* Inverse trigonometric functions */                \
    Q_FORMAT##_t Q_FORMAT##_asin(Q_FORMAT##_t value);    \
    Q_FORMAT##_t Q_FORMAT##_acos(Q_FORMAT##_t value);    \
    Q_FORMAT##_t Q_FORMAT##_atan(Q_FORMAT##_t value);    \
                                                         \
    /* Other mathematical functions */                   \
    Q_FORMAT##_t Q_FORMAT##_sqrt(Q_FORMAT##_t value);    \
    Q_FORMAT##_t Q_FORMAT##_inverse(Q_FORMAT##_t value); \
    Q_FORMAT##_t Q_FORMAT##_log(Q_FORMAT##_t value);     \
    Q_FORMAT##_t Q_FORMAT##_exp(Q_FORMAT##_t value);

/* ========================================================================
 * Q1.6 Format Functions
 * ======================================================================== */
DECLARE_FIXED_POINT_FUNCTIONS(q1_6)

/* ========================================================================
 * Q1.14 Format Functions
 * ======================================================================== */
DECLARE_FIXED_POINT_FUNCTIONS(q1_14)

/* ========================================================================
 * Q1.30 Format Functions
 * ======================================================================== */
DECLARE_FIXED_POINT_FUNCTIONS(q1_30)

#endif /* FIXED_POINT_MATH_H */
