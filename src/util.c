#include "util.h"
#include "defines.h"
#include <stdint.h>

/*
 * Utility functions for fixed-point conversions
 * Supports conversion between float, double, fp16 (Q1.14), and fp32 (Q1.30)
 */

/* ========================================================================
 * Float to Fixed-Point Conversions
 * ======================================================================== */

fp16_t float_to_fp16(float input)
{
    /* Convert float to Q1.14 format by multiplying by 2^14 */
    return (fp16_t)(input * (float)FP16_ONE_VALUE);
}

fp32_t float_to_fp32(float input)
{
    /* Convert float to Q1.30 format by multiplying by 2^30 */
    return (fp32_t)(input * (float)FP32_ONE_VALUE);
}

/* ========================================================================
 * Fixed-Point to Float Conversions
 * ======================================================================== */

float fp16_to_float(fp16_t input)
{
    /* Convert Q1.14 to float by dividing by 2^14 */
    return (float)input / (float)FP16_ONE_VALUE;
}

float fp32_to_float(fp32_t input)
{
    /* Convert Q1.30 to float by dividing by 2^30 */
    return (float)input / (float)FP32_ONE_VALUE;
}

/* ========================================================================
 * Double to Fixed-Point Conversions
 * ======================================================================== */

fp16_t double_to_fp16(double input)
{
    /* Convert double to Q1.14 format by multiplying by 2^14 */
    return (fp16_t)(input * (double)FP16_ONE_VALUE);
}

fp32_t double_to_fp32(double input)
{
    /* Convert double to Q1.30 format by multiplying by 2^30 */
    return (fp32_t)(input * (double)FP32_ONE_VALUE);
}

/* ========================================================================
 * Fixed-Point to Double Conversions
 * ======================================================================== */

double fp16_to_double(fp16_t input)
{
    /* Convert Q1.14 to double by dividing by 2^14 */
    return (double)input / (double)FP16_ONE_VALUE;
}

double fp32_to_double(fp32_t input)
{
    /* Convert Q1.30 to double by dividing by 2^30 */
    return (double)input / (double)FP32_ONE_VALUE;
}

/* ========================================================================
 * Fixed-Point to Fixed-Point Conversions
 * ======================================================================== */

fp32_t fp16_to_fp32(fp16_t input)
{
    /* Convert Q1.14 to Q1.30 by left-shifting by (30-14) = 16 bits */
    return (fp32_t)input << (FP32_FRACTIONAL_BITS - FP16_FRACTIONAL_BITS);
}

fp16_t fp32_to_fp16(fp32_t input)
{
    /* Convert Q1.30 to Q1.14 by right-shifting by (30-14) = 16 bits */
    return (fp16_t)(input >> (FP32_FRACTIONAL_BITS - FP16_FRACTIONAL_BITS));
}
