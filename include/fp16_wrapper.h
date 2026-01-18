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
#endif /* FP16_WRAPPER_H */