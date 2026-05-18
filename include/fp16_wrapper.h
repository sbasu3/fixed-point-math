#ifndef FP16_WRAPPER_H
#define FP16_WRAPPER_H
#include <stdint.h>
/*
 * Utility functions for fixed-point conversions
 * Supports conversion between float, double, fp16 (Q1.14), and fp32 (Q1.30)
 */
// ========================================================================
#include "util.h"
#include "defines.h"
#include "fixed-point-math.h"
/* ========================================================================
 * Float to Fixed-Point Conversions
 * ======================================================================== */

float fp16_float_exp(float x);
float fp16_float_ln(float x);
float fp16_float_inverse(float x);
float fp16_float_sqrt(float x);

/* ========================================================================
 * Double to Fixed-Point Conversions
 * ======================================================================== */
double fp16_double_exp(double x);
double fp16_double_ln(double x);
double fp16_double_inverse(double x);
double fp16_double_sqrt(double x);

/* ========================================================================
 * CORDIC Trigonometric Wrappers
 * Float and double wrappers for sin, cos, and atan2.
 * These perform range reduction to support angles beyond [-pi/2, pi/2].
 * ======================================================================== */
float fp16_float_sin(float angle);
float fp16_float_cos(float angle);
float fp16_float_atan2(float y, float x);

double fp16_double_sin(double angle);
double fp16_double_cos(double angle);
double fp16_double_atan2(double y, double x);

#endif /* FP16_WRAPPER_H */