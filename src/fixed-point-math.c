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
 * Q1.6 format: 1 sign bit, 1 integer bit, 6 fractional bits
 * Range: [-0.693147, 0.606504] in decimal
 * Step size: 0.086643
 * ln(2) ≈ 0.693147180559945309417232121458
 * Conversion: value * 2^6 = value * 64
 */
static const Q1_6_t lut_ln2_range_Q1_6[LUT_SZ] = {
    -44, /* -ln(2) = -0.693147 */
    -39, /* -ln(2) + 1*(7*ln(2)/8 + ln(2))/15 = -0.606504 */
    -33, /* -ln(2) + 2*(7*ln(2)/8 + ln(2))/15 = -0.519860 */
    -28, /* -ln(2) + 3*(7*ln(2)/8 + ln(2))/15 = -0.433217 */
    -22, /* -ln(2) + 4*(7*ln(2)/8 + ln(2))/15 = -0.346574 */
    -17, /* -ln(2) + 5*(7*ln(2)/8 + ln(2))/15 = -0.259930 */
    -11, /* -ln(2) + 6*(7*ln(2)/8 + ln(2))/15 = -0.173287 */
    -6,  /* -ln(2) + 7*(7*ln(2)/8 + ln(2))/15 = -0.086644 */
    0,   /* -ln(2) + 8*(7*ln(2)/8 + ln(2))/15 = 0.0 */
    6,   /* -ln(2) + 9*(7*ln(2)/8 + ln(2))/15 = 0.086644 */
    11,  /* -ln(2) + 10*(7*ln(2)/8 + ln(2))/15 = 0.173287 */
    17,  /* -ln(2) + 11*(7*ln(2)/8 + ln(2))/15 = 0.259930 */
    22,  /* -ln(2) + 12*(7*ln(2)/8 + ln(2))/15 = 0.346574 */
    28,  /* -ln(2) + 13*(7*ln(2)/8 + ln(2))/15 = 0.433217 */
    33,  /* -ln(2) + 14*(7*ln(2)/8 + ln(2))/15 = 0.519860 */
    39   /* 7*ln(2)/8 = 0.606504 */
};

#define LUT_LN2_Q1_6_SIZE 16
#define LUT_LN2_MIN_Q1_6 (-44) /* -ln(2) in Q1.6 */
#define LUT_LN2_MAX_Q1_6 (39)  /* 7*ln(2)/8 in Q1.6 */
#define LUT_LN2_STEP_Q1_6 (6)  /* Step size in Q1.6 */

/*
 * 16-element LUT with equidistant values from -ln(2) to 7*ln(2)/8
 * Q1.14 format: 1 sign bit, 1 integer bit, 14 fractional bits
 * Range: [-0.693147, 0.606504] in decimal
 * Step size: 0.086643
 * ln(2) ≈ 0.693147180559945309417232121458
 * Conversion: value * 2^14 = value * 16384
 */
static const Q1_14_t lut_ln2_range_Q1_14[LUT_SZ] = {
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

#define LUT_LN2_Q1_14_SIZE 16
#define LUT_LN2_MIN_Q1_14 (-11356) /* -ln(2) in Q1.14 */
#define LUT_LN2_MAX_Q1_14 (9937)   /* 7*ln(2)/8 in Q1.14 */
#define LUT_LN2_STEP_Q1_14 (1419)  /* Step size in Q1.14 */

/*
 * 16-element LUT with equidistant values from -ln(2) to 7*ln(2)/8
 * Q1.30 format: 1 sign bit, 1 integer bit, 30 fractional bits
 * Range: [-0.693147, 0.606504] in decimal
 * Step size: 0.086643
 * ln(2) ≈ 0.693147180559945309417232121458
 * Conversion: value * 2^30 = value * 1073741824
 */
static const Q1_30_t lut_ln2_range_Q1_30[LUT_SZ] = {
    -744261118, /* -ln(2) = -0.693147 */
    -651286270, /* -ln(2) + 1*(7*ln(2)/8 + ln(2))/15 = -0.606504 */
    -558311421, /* -ln(2) + 2*(7*ln(2)/8 + ln(2))/15 = -0.519860 */
    -465336572, /* -ln(2) + 3*(7*ln(2)/8 + ln(2))/15 = -0.433217 */
    -372361724, /* -ln(2) + 4*(7*ln(2)/8 + ln(2))/15 = -0.346574 */
    -279386875, /* -ln(2) + 5*(7*ln(2)/8 + ln(2))/15 = -0.259930 */
    -186412026, /* -ln(2) + 6*(7*ln(2)/8 + ln(2))/15 = -0.173287 */
    -93037178,  /* -ln(2) + 7*(7*ln(2)/8 + ln(2))/15 = -0.086644 */
    0,          /* -ln(2) + 8*(7*ln(2)/8 + ln(2))/15 = 0.0 */
    93037178,   /* -ln(2) + 9*(7*ln(2)/8 + ln(2))/15 = 0.086644 */
    186412026,  /* -ln(2) + 10*(7*ln(2)/8 + ln(2))/15 = 0.173287 */
    279386875,  /* -ln(2) + 11*(7*ln(2)/8 + ln(2))/15 = 0.259930 */
    372361724,  /* -ln(2) + 12*(7*ln(2)/8 + ln(2))/15 = 0.346574 */
    465336572,  /* -ln(2) + 13*(7*ln(2)/8 + ln(2))/15 = 0.433217 */
    558311421,  /* -ln(2) + 14*(7*ln(2)/8 + ln(2))/15 = 0.519860 */
    651286270   /* 7*ln(2)/8 = 0.606504 */
};

#define LUT_LN2_Q1_30_SIZE 16
#define LUT_LN2_MIN_Q1_30 (-744261118) /* -ln(2) in Q1.30 */
#define LUT_LN2_MAX_Q1_30 (651286270)  /* 7*ln(2)/8 in Q1.30 */
#define LUT_LN2_STEP_Q1_30 (93037178)  /* Step size in Q1.30 */

/* ========================================================================
 * Generic Function Implementation Templates
 * These macros generate function implementations for all fixed-point formats
 * ======================================================================== */

#define IMPLEMENT_FIXED_POINT_FUNCTIONS(Q_FORMAT, FRAC_BITS, ONE_VALUE)                                       \
    /* Get sign bit: returns 1 if negative, 0 if positive or zero */                                          \
    int                                                                                                       \
    Q_FORMAT##_get_sign_bit(Q_FORMAT##_t value)                                                               \
    {                                                                                                         \
        return (value < 0) ? 1 : 0;                                                                           \
    }                                                                                                         \
                                                                                                              \
    /* Set sign bit: returns absolute value if sign=0, negated value if sign=1 */                             \
    Q_FORMAT##_t Q_FORMAT##_set_sign_bit(Q_FORMAT##_t value, int sign)                                        \
    {                                                                                                         \
        Q_FORMAT##_t abs_value = (value < 0) ? -value : value;                                                \
        return (sign != 0) ? -abs_value : abs_value;                                                          \
    }                                                                                                         \
    /* Conversion from float */                                                                               \
    Q_FORMAT##_t                                                                                              \
    Q_FORMAT##_from_float(float value)                                                                        \
    {                                                                                                         \
        return (Q_FORMAT##_t)(value * (float)ONE_VALUE);                                                      \
    }                                                                                                         \
                                                                                                              \
    /* Conversion from double */                                                                              \
    Q_FORMAT##_t Q_FORMAT##_from_double(double value)                                                         \
    {                                                                                                         \
        return (Q_FORMAT##_t)(value * (double)ONE_VALUE);                                                     \
    }                                                                                                         \
                                                                                                              \
    /* Conversion to float */                                                                                 \
    float Q_FORMAT##_to_float(Q_FORMAT##_t value)                                                             \
    {                                                                                                         \
        return (float)value / (float)ONE_VALUE;                                                               \
    }                                                                                                         \
                                                                                                              \
    /* Conversion to double */                                                                                \
    double Q_FORMAT##_to_double(Q_FORMAT##_t value)                                                           \
    {                                                                                                         \
        return (double)value / (double)ONE_VALUE;                                                             \
    }                                                                                                         \
                                                                                                              \
    /* Scaled conversion from float (arbitrary range to fixed-point) */                                       \
    Q_FORMAT##_t Q_FORMAT##_from_float_scaled(float value, float min, float max)                              \
    {                                                                                                         \
        /* Normalize value from [min, max] to [-1.0, 1.0] range */                                            \
        float range = max - min;                                                                              \
        float normalized = ((value - min) / range) * 2.0f - 1.0f;                                             \
        return (Q_FORMAT##_t)(normalized * (float)ONE_VALUE);                                                 \
    }                                                                                                         \
                                                                                                              \
    /* Scaled conversion from double (arbitrary range to fixed-point) */                                      \
    Q_FORMAT##_t Q_FORMAT##_from_double_scaled(double value, double min, double max)                          \
    {                                                                                                         \
        /* Normalize value from [min, max] to [-1.0, 1.0] range */                                            \
        double range = max - min;                                                                             \
        double normalized = ((value - min) / range) * 2.0 - 1.0;                                              \
        return (Q_FORMAT##_t)(normalized * (double)ONE_VALUE);                                                \
    }                                                                                                         \
                                                                                                              \
    /* Scaled conversion to float (fixed-point to arbitrary range) */                                         \
    float Q_FORMAT##_to_float_scaled(Q_FORMAT##_t value, float min, float max)                                \
    {                                                                                                         \
        /* Convert fixed-point to [-1.0, 1.0] range first */                                                  \
        float normalized = (float)value / (float)ONE_VALUE;                                                   \
        /* Scale to [min, max] range */                                                                       \
        float range = max - min;                                                                              \
        return ((normalized + 1.0f) / 2.0f) * range + min;                                                    \
    }                                                                                                         \
                                                                                                              \
    /* Scaled conversion to double (fixed-point to arbitrary range) */                                        \
    double Q_FORMAT##_to_double_scaled(Q_FORMAT##_t value, double min, double max)                            \
    {                                                                                                         \
        /* Convert fixed-point to [-1.0, 1.0] range first */                                                  \
        double normalized = (double)value / (double)ONE_VALUE;                                                \
        /* Scale to [min, max] range */                                                                       \
        double range = max - min;                                                                             \
        return ((normalized + 1.0) / 2.0) * range + min;                                                      \
    }                                                                                                         \
                                                                                                              \
    Q_FORMAT##_t Q_FORMAT##_sin(Q_FORMAT##_t angle)                                                           \
    {                                                                                                         \
        (void)angle;                                                                                          \
        /* TODO: Implement sine function for Q_FORMAT format */                                               \
        /* Fractional bits: FRAC_BITS, ONE: ONE_VALUE */                                                      \
        return 0;                                                                                             \
    }                                                                                                         \
                                                                                                              \
    Q_FORMAT##_t Q_FORMAT##_cos(Q_FORMAT##_t angle)                                                           \
    {                                                                                                         \
        (void)angle;                                                                                          \
        /* TODO: Implement cosine function for Q_FORMAT format */                                             \
        /* Fractional bits: FRAC_BITS, ONE: ONE_VALUE */                                                      \
        return 0;                                                                                             \
    }                                                                                                         \
                                                                                                              \
    Q_FORMAT##_t Q_FORMAT##_tan(Q_FORMAT##_t angle)                                                           \
    {                                                                                                         \
        (void)angle;                                                                                          \
        /* TODO: Implement tangent function for Q_FORMAT format */                                            \
        /* Fractional bits: FRAC_BITS, ONE: ONE_VALUE */                                                      \
        return 0;                                                                                             \
    }                                                                                                         \
                                                                                                              \
    Q_FORMAT##_t Q_FORMAT##_asin(Q_FORMAT##_t value)                                                          \
    {                                                                                                         \
        (void)value;                                                                                          \
        /* TODO: Implement arcsine function for Q_FORMAT format */                                            \
        /* Fractional bits: FRAC_BITS, ONE: ONE_VALUE */                                                      \
        return 0;                                                                                             \
    }                                                                                                         \
                                                                                                              \
    Q_FORMAT##_t Q_FORMAT##_acos(Q_FORMAT##_t value)                                                          \
    {                                                                                                         \
        (void)value;                                                                                          \
        /* TODO: Implement arccosine function for Q_FORMAT format */                                          \
        /* Fractional bits: FRAC_BITS, ONE: ONE_VALUE */                                                      \
        return 0;                                                                                             \
    }                                                                                                         \
                                                                                                              \
    Q_FORMAT##_t Q_FORMAT##_atan(Q_FORMAT##_t value)                                                          \
    {                                                                                                         \
        (void)value;                                                                                          \
        /* TODO: Implement arctangent function for Q_FORMAT format */                                         \
        /* Fractional bits: FRAC_BITS, ONE: ONE_VALUE */                                                      \
        return 0;                                                                                             \
    }                                                                                                         \
                                                                                                              \
    Q_FORMAT##_t Q_FORMAT##_sqrt(Q_FORMAT##_t value)                                                          \
    {                                                                                                         \
        (void)value;                                                                                          \
        /* TODO: Implement square root function for Q_FORMAT format */                                        \
        /* Fractional bits: FRAC_BITS, ONE: ONE_VALUE */                                                      \
        return 0;                                                                                             \
    }                                                                                                         \
                                                                                                              \
    Q_FORMAT##_t Q_FORMAT##_inverse(Q_FORMAT##_t value)                                                       \
    {                                                                                                         \
        (void)value;                                                                                          \
        /* TODO: Implement inverse (1/x) function for Q_FORMAT format */                                      \
        /* Fractional bits: FRAC_BITS, ONE: ONE_VALUE */                                                      \
        return 0;                                                                                             \
    }                                                                                                         \
                                                                                                              \
    Q_FORMAT##_t Q_FORMAT##_log(Q_FORMAT##_t value)                                                           \
    {                                                                                                         \
        (void)value;                                                                                          \
        /* TODO: Implement natural logarithm function for Q_FORMAT format */                                  \
        /* Fractional bits: FRAC_BITS, ONE: ONE_VALUE */                                                      \
        return 0;                                                                                             \
    }                                                                                                         \
                                                                                                              \
    Q_FORMAT##_t Q_FORMAT##_exp(Q_FORMAT##_t value)                                                           \
    {                                                                                                         \
        if (value == 0)                                                                                       \
        {                                                                                                     \
            return (Q_FORMAT##_t)ONE_VALUE;                                                                   \
        }                                                                                                     \
        /* Exponential function using LUT and linear interpolation - integer only */                          \
        /* LUT range: [-ln(2), 7*ln(2)/8] approximately [-0.693, 0.607] */                                    \
        /* Handles both positive and negative arguments with separate flows */                                \
                                                                                                              \
        /* Scale input value by INV_LN2: addr = value * (1/ln(2)) * 2^3 */                                    \
        int64_t scaled = ((int64_t)value *                                                                    \
                          Q_FORMAT##_INV_LN2_APPROX)                                                          \
                         << 3;                                                                                \
                                                                                                              \
        /* Extract fractional part for linear interpolation (lower bits) */                                   \
        DOUBLE_##Q_FORMAT##_t frac = (DOUBLE_##Q_FORMAT##_t)(scaled & (DOUBLE_##Q_FORMAT##_FRACTIONAL_MASK)); \
                                                                                                              \
        int8_t index;                                                                                         \
                                                                                                              \
        /* ============================================================= */                                   \
        /* FLOW FOR POSITIVE ARGUMENTS */                                                                     \
        /* ============================================================= */                                   \
        if (value >= 0)                                                                                       \
        {                                                                                                     \
            /* For positive values: direct right-shift for integer part */                                    \
            int8_t addr_int = scaled >> (DOUBLE_##Q_FORMAT##_FRACTIONAL_BITS);                                \
            /* Map to LUT centered at 8 (middle of 16-element LUT) */                                         \
            index = 8 + (int8_t)addr_int;                                                                     \
        }                                                                                                     \
        /* ============================================================= */                                   \
        /* FLOW FOR NEGATIVE ARGUMENTS */                                                                     \
        /* ============================================================= */                                   \
        else                                                                                                  \
        {                                                                                                     \
            /* For negative values: floor behavior (round toward -infinity) */                                \
            /* This ensures symmetric binning of indices around zero */                                       \
            frac = frac + DOUBLE_##Q_FORMAT##_ONE;                                                            \
            int8_t addr_int = (scaled - DOUBLE_##Q_FORMAT##_ONE) >> (DOUBLE_##Q_FORMAT##_FRACTIONAL_BITS);    \
            /* Map to LUT centered at 8 (middle of 16-element LUT) */                                         \
            index = 8 + (int8_t)addr_int;                                                                     \
        }                                                                                                     \
                                                                                                              \
        /* Clamp index to valid LUT range [0, 15] to prevent out-of-bounds access */                          \
        if (index > 14)                                                                                       \
            index = 14;                                                                                       \
        else if (index < 0)                                                                                   \
            index = 0;                                                                                        \
                                                                                                              \
        /* ============================================================= */                                   \
        /* LINEAR INTERPOLATION (works for both positive/negative) */                                         \
        /* ============================================================= */                                   \
        /* Get LUT values at current and next index */                                                        \
        Q_FORMAT##_t y0 = (Q_FORMAT##_t)lut_ln2_range_##Q_FORMAT[index];                                      \
        Q_FORMAT##_t y1 = (Q_FORMAT##_t)lut_ln2_range_##Q_FORMAT[index + 1];                                  \
                                                                                                              \
        /* Compute slope: dy = y1 - y0 */                                                                     \
        Q_FORMAT##_t dy = y1 - y0;                                                                            \
                                                                                                              \
        /* Scale interpolation by fractional part: delta = dy * frac / 2^(FRAC_BITS+3) */                     \
        DOUBLE_##Q_FORMAT##_t delta = ((DOUBLE_##Q_FORMAT##_t)(dy * frac)) >> (Q_FORMAT##_FRACTIONAL_BITS);   \
                                                                                                              \
        /* Final result: y = y0 + delta */                                                                    \
        Q_FORMAT##_t result = (Q_FORMAT##_t)(y0 + delta);                                                     \
                                                                                                              \
        return (Q_FORMAT##_t)result;                                                                          \
    }

/* ========================================================================
 * Q1.6 Format Function Implementations
 * ======================================================================== */
IMPLEMENT_FIXED_POINT_FUNCTIONS(Q1_6, Q1_6_FRACTIONAL_BITS, Q1_6_ONE)

/* ========================================================================
 * Q1.14 Format Function Implementations
 * ======================================================================== */
IMPLEMENT_FIXED_POINT_FUNCTIONS(Q1_14, Q1_14_FRACTIONAL_BITS, Q1_14_ONE)

/* ========================================================================
 * Q1.30 Format Function Implementations
 * ======================================================================== */
IMPLEMENT_FIXED_POINT_FUNCTIONS(Q1_30, Q1_30_FRACTIONAL_BITS, Q1_30_ONE)
