#include "defines.h"
#include "fixed-point-math.h"
#include <stdint.h>
// #include <math.h>

/*
 * Fixed-Point Math Library Implementation
 * Processor-independent mathematical functions for fixed-point arithmetic
 * Using generic macros to avoid code duplication across formats
 */

/* ========================================================================
 * Lookup Tables
 * ======================================================================== */
#define LUT_SZ 16
#define HALF_LUT_SZ (LUT_SZ / 2)

/*
 * 16-element LUT with equidistant values from -ln(2) to 7*ln(2)/8
 * Q1.14 format: 1 sign bit, 1 integer bit, 14 fractional bits
 * Range: [-0.693147, 0.606504] in decimal
 * Step size: 0.086643
 * ln(2) ≈ 0.693147180559945309417232121458
 * Conversion: value * 2^14 = value * 16384
 */
static const fp16_t fp16_lut_ln2_range[LUT_SZ] = {
    -11356, /* -ln(2) = -0.693147 */
    -9937,  /* -ln(2) + 1*(7*ln(2)/8 + ln(2))/15 = -0.606504 */
    -8517,  /* -ln(2) + 2*(7*ln(2)/8 + ln(2))/15 = -0.519860 */
    -7097,  /* -ln(2) + 3*(7*ln(2)/8 + ln(2))/15 = -0.433217 */
    -5678,  /* -ln(2) + 4*(7*ln(2)/8 + ln(2))/15 = -0.346574 */
    -4258,  /* -ln(2) + 5*(7*ln(2)/8 + ln(2))/15 = -0.259930 */
    -2838,  /* -ln(2) + 6*(7*ln(2)/8 + ln(2))/15 = -0.173287 */
    -1419,  /* -ln(2) + 7*(7*ln(2)/8 + ln(2))/15 = -0.086644 */
    0,      /* -ln(2) + 8*(7*ln(2)/8 + ln(2))/15 = 0.0 */
    1419,   /* -ln(2) + 9*(7*ln(2)/8 + ln(2))/15 = 0.086644 */
    2838,   /* -ln(2) + 10*(7*ln(2)/8 + ln(2))/15 = 0.173287 */
    4258,   /* -ln(2) + 11*(7*ln(2)/8 + ln(2))/15 = 0.259930 */
    5678,   /* -ln(2) + 12*(7*ln(2)/8 + ln(2))/15 = 0.346574 */
    7097,   /* -ln(2) + 13*(7*ln(2)/8 + ln(2))/15 = 0.433217 */
    8517,   /* -ln(2) + 14*(7*ln(2)/8 + ln(2))/15 = 0.519860 */
    9937    /* 7*ln(2)/8 = 0.606504 */
};

fp16_t fp16_exp(fp16_t value)
{
    if (value == 0)
    {
        return (fp16_t)FP16_ONE_VALUE;
    }
    /* Exponential function using LUT and linear interpolation - integer only */
    /* LUT range: [-ln(2), 7*ln(2)/8] approximately [-0.693, 0.607] */
    /* Handles both positive and negative arguments with separate flows */

    /* Scale input value by INV_LN2: addr = value * (1/ln(2)) * 2^3 */
    int32_t scaled = ((int32_t)value * FP16_INV_LN2_APPROX) << 3;

    /* Extract fractional part for linear interpolation (lower bits) */
    fp32_t frac = (fp32_t)(scaled & (FP32_FRACTIONAL_MASK));

    int8_t addr_int;

    /* ============================================================= */
    /* FLOW FOR POSITIVE ARGUMENTS */
    /* ============================================================= */
    if (value >= 0)
    {
        /* For positive values: direct right-shift for integer part */
        addr_int = scaled >> (FP32_FRACTIONAL_BITS);
    }
    /* ============================================================= */
    /* FLOW FOR NEGATIVE ARGUMENTS */
    /* ============================================================= */
    else
    {
        /* For negative values: floor behavior (round toward -infinity) */
        /* This ensures symmetric binning of indices around zero */
        frac = (value < 0) ? (fp32_t)(frac | ~FP32_FRACTIONAL_MASK) : frac;
        addr_int = (scaled - FP32_ONE_VALUE) >> (FP32_FRACTIONAL_BITS);
    }
    /* Map to LUT centered at 8 (middle of 16-element LUT) */
    int8_t index = 8 + addr_int;
    /* Clamp index to valid LUT range [0, 15] to prevent out-of-bounds access */
    if (index >= 15)
        index = 15;
    else if (index < 0)
        index = 0;

    /* ============================================================= */
    /* LINEAR INTERPOLATION (works for both positive/negative) */
    /* ============================================================= */
    /* Get LUT values at current and next index */
    fp16_t y0 = (fp16_t)fp16_lut_ln2_range[index];
    fp16_t y1 = (fp16_t)fp16_lut_ln2_range[index + 1];

    /* Compute slope: dy = y1 - y0 */
    fp16_t dy = y1 - y0;

    /* Scale interpolation by fractional part: delta = dy * frac */
    fp16_t delta = ((fp32_t)(dy * frac)) >> (FP16_FRACTIONAL_BITS);

    /* Final result: y = y0 + delta */
    fp16_t result = y0 + delta;

    return (fp16_t)result;
}
