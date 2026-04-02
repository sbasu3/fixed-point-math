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
 * Note: Currently used by fp16_exp, kept for reference/future optimization
 */
static const fp16_t fp16_lut_ln2_range[LUT_SZ] __attribute__((unused)) = {
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

/* ========================================================================
 * Function Implementations
 * ======================================================================== */
/* Exponential Function using Polynomial Approximation */
/* Using 3rd-degree polynomial approximation */
/* Input: x in Q1.14 format (fp16_t) */
/* Output: exp(x) in Q1.14 format (fp16_t) */
fp16_t fp16_poly_exp(fp16_t value)
{
    /* Exponential function using 3rd-degree polynomial approximation */
    /* Coefficients for polynomial approximation of exp(x) around 0 */
    const fp16_t c0 = (fp16_t)(16384); /* 1.0 in Q1.14 */
    const fp16_t c1 = (fp16_t)(16384); /* 1.0 in Q1.14 */
    const fp16_t c2 = (fp16_t)(8192);  /* 0.5 in Q1.14 */
    const fp16_t c3 = (fp16_t)(2731);  /* 1/6 ≈ 0.166667 in Q1.14 */

    /* Compute polynomial: exp(x) ≈ c0 + c1*x + c2*x^2 + c3*x^3 */
    fp32_t x = (fp32_t)value;
    fp32_t x2 = (x * x) >> FP16_FRACTIONAL_BITS;  /* x^2 in Q1.14 */
    fp32_t x3 = (x2 * x) >> FP16_FRACTIONAL_BITS; /* x^3 in Q1.14 */

    fp32_t term1 = (fp32_t)c1 * x;  /* c1*x in Q1.14 */
    fp32_t term2 = (fp32_t)c2 * x2; /* c2*x^2 in Q1.14 */
    fp32_t term3 = (fp32_t)c3 * x3; /* c3*x^3 in Q1.14 */

    fp32_t result = (fp32_t)c0 + (term1 >> FP16_FRACTIONAL_BITS) + (term2 >> FP16_FRACTIONAL_BITS) + (term3 >> FP16_FRACTIONAL_BITS);

    return (fp16_t)result;
}
/* Natural Logarithm Function */
/* Using Taylor series expansion of ln(1+x) */
/* Input: x in Q1.14 format (fp16_t) */
/* Output: ln(1+x) in Q1.14 format (fp16_t) */
/* Domain: -0.5 ≤ x ≤ 0.5 */
/* Taylor series: ln(1+x) = x - x²/2 + x³/3 - x⁴/4 + ... */
fp16_t fp16_ln(fp16_t x)
{
    if (x == 0)
    {
        /* ln(1) = 0 */
        return (fp16_t)0;
    }

    /* Coefficients for Taylor series of ln(1+x) */
    const fp16_t c1 = (fp16_t)(16384); /* 1.0 in Q1.14 */
    const fp16_t c2 = (fp16_t)(-8192); /* -0.5 in Q1.14 */
    const fp16_t c3 = (fp16_t)(5461);  /* 1/3 ≈ 0.333333 in Q1.14 */
    const fp16_t c4 = (fp16_t)(-4096); /* -0.25 in Q1.14 */

    /* Compute polynomial: ln(1+x) ≈ c1*x + c2*x^2 + c3*x^3 + c4*x^4 */
    fp32_t x_fp32 = (fp32_t)x;
    fp32_t x2 = (x_fp32 * x_fp32) >> FP16_FRACTIONAL_BITS; /* x^2 in Q1.14 */
    fp32_t x3 = (x2 * x_fp32) >> FP16_FRACTIONAL_BITS;     /* x^3 in Q1.14 */
    fp32_t x4 = (x2 * x2) >> FP16_FRACTIONAL_BITS;         /* x^4 in Q1.14 */

    fp32_t term1 = (fp32_t)c1 * x_fp32; /* c1*x */
    fp32_t term2 = (fp32_t)c2 * x2;     /* c2*x^2 */
    fp32_t term3 = (fp32_t)c3 * x3;     /* c3*x^3 */
    fp32_t term4 = (fp32_t)c4 * x4;     /* c4*x^4 */

    fp32_t result = (term1 >> FP16_FRACTIONAL_BITS) +
                    (term2 >> FP16_FRACTIONAL_BITS) +
                    (term3 >> FP16_FRACTIONAL_BITS) +
                    (term4 >> FP16_FRACTIONAL_BITS);

    return (fp16_t)result;
}

/* Inverse Function using Newton-Raphson Method */
/* Input: x in Q1.14 format (fp16_t) */
/* Output: 1/x in Q1.14 format (fp16_t) */
/* x != 0 */
/* Range: x in [FP16_MIN_VALUE, FP16_MAX_VALUE] excluding [-0.5, 0.5] */
fp16_t fp16_inverse(fp16_t x)
{
    /* Handle division by zero or values too close to zero */
    if (x <= FP16_ONE_VALUE / 2 && x >= -FP16_ONE_VALUE / 2)
    {
        return FP16_MAX_VALUE;
    }

    /* Extract sign */
    int8_t sign = (x < 0) ? -1 : 1;
    int16_t x_abs = (x < 0) ? -x : x;

    /* Initial guess for Newton-Raphson: start with a simple division */
    fp32_t guess = ((fp32_t)FP16_ONE_VALUE * FP16_ONE_VALUE) / (fp32_t)x_abs;

    /* Clamp initial guess */
    if (guess > ((fp32_t)FP16_MAX_VALUE << 4))
        guess = (fp32_t)FP16_MAX_VALUE << 4;

    /* Newton-Raphson: x_new = x_old * (2 - a * x_old) where a is input */
    fp32_t x_abs_fp32 = (fp32_t)x_abs;
    for (int i = 0; i < 5; i++)
    {
        fp32_t product = (x_abs_fp32 * guess) >> FP16_FRACTIONAL_BITS;
        fp32_t delta = (2 * (fp32_t)FP16_ONE_VALUE) - product;
        guess = (guess * delta) >> FP16_FRACTIONAL_BITS;
    }

    /* Clamp result */
    if (guess > (fp32_t)FP16_MAX_VALUE)
        guess = (fp32_t)FP16_MAX_VALUE;
    if (guess < (fp32_t)FP16_MIN_VALUE)
        guess = (fp32_t)FP16_MIN_VALUE;

    fp16_t result = (fp16_t)guess;
    return (sign < 0) ? -result : result;
}

/* Square Root Function using Newton-Raphson Method */
/* Input: x in Q1.14 format (fp16_t), x >= 0 */
/* Output: sqrt(x) in Q1.14 format (fp16_t) */
fp16_t fp16_sqrt(fp16_t x)
{
    if (x < 0)
    {
        return (fp16_t)FP16_MIN_VALUE;
    }
    if (x == 0)
    {
        return (fp16_t)0;
    }
    /* Initial guess: x / 2 */
    fp32_t guess = ((fp32_t)x) >> 1;
    if (guess == 0)
    {
        guess = 1 << FP16_FRACTIONAL_BITS;
    }
    /* Newton-Raphson: x_new = 0.5 * (x_old + S / x_old) */
    for (int i = 0; i < 5; i++)
    {
        fp32_t div = (((fp32_t)x) << FP16_FRACTIONAL_BITS) / guess;
        guess = (guess + div) >> 1;
    }
    if (guess > (fp32_t)FP16_MAX_VALUE)
        guess = (fp32_t)FP16_MAX_VALUE;
    return (fp16_t)guess;
}

/* ========================================================================
 * CORDIC Functions
 * ======================================================================== */

/* CORDIC arctangent lookup table in Q1.14 format
 * atan_lut[i] = round(atan(2^-i) × 2^14) for i = 0..13 */
static const int16_t fp16_cordic_atan_lut[FP16_CORDIC_ITERATIONS] = {
    12868, /* i=0:  atan(1)      = 0.785398 rad */
    7596,  /* i=1:  atan(2^-1)  = 0.463648 rad */
    4014,  /* i=2:  atan(2^-2)  = 0.244979 rad */
    2037,  /* i=3:  atan(2^-3)  = 0.124355 rad */
    1023,  /* i=4:  atan(2^-4)  = 0.062419 rad */
    512,   /* i=5:  atan(2^-5)  = 0.031240 rad */
    256,   /* i=6:  atan(2^-6)  = 0.015624 rad */
    128,   /* i=7:  atan(2^-7)  = 0.007812 rad */
    64,    /* i=8:  atan(2^-8)  = 0.003906 rad */
    32,    /* i=9:  atan(2^-9)  = 0.001953 rad */
    16,    /* i=10: atan(2^-10) = 0.000977 rad */
    8,     /* i=11: atan(2^-11) = 0.000488 rad */
    4,     /* i=12: atan(2^-12) = 0.000244 rad */
    2      /* i=13: atan(2^-13) = 0.000122 rad */
};

/* Internal CORDIC rotation helper
 * Rotates the initial vector (A, 0) by angle z using the CORDIC algorithm.
 * A = FP16_CORDIC_GAIN compensates for the CORDIC amplification factor K,
 * so that |output| == 1 when the input angle is valid.
 * Input: angle in Q1.14 radians, range [-pi/2, pi/2]
 * Output: cos_out = cos(angle), sin_out = sin(angle), both in Q1.14 */
static void fp16_cordic_rotate(fp16_t angle, fp16_t *cos_out, fp16_t *sin_out)
{
    int32_t x = (int32_t)FP16_CORDIC_GAIN; /* pre-scaled by 1/K */
    int32_t y = 0;
    int32_t z = (int32_t)angle;
    int i;

    for (i = 0; i < FP16_CORDIC_ITERATIONS; i++)
    {
        int32_t d = (z >= 0) ? 1 : -1;
        int32_t x_new = x - d * (y >> i);
        int32_t y_new = y + d * (x >> i);
        int32_t z_new = z - d * (int32_t)fp16_cordic_atan_lut[i];
        x = x_new;
        y = y_new;
        z = z_new;
    }

    /* Clamp to Q1.14 range before narrowing to fp16_t */
    if (x > (int32_t)FP16_MAX_VALUE)
        x = (int32_t)FP16_MAX_VALUE;
    if (x < (int32_t)FP16_MIN_VALUE)
        x = (int32_t)FP16_MIN_VALUE;
    if (y > (int32_t)FP16_MAX_VALUE)
        y = (int32_t)FP16_MAX_VALUE;
    if (y < (int32_t)FP16_MIN_VALUE)
        y = (int32_t)FP16_MIN_VALUE;

    *cos_out = (fp16_t)x;
    *sin_out = (fp16_t)y;
}

/* Sine Function using CORDIC algorithm */
/* Input: angle in Q1.14 radians, range [-pi/2, pi/2] */
/* Output: sin(angle) in Q1.14 format */
fp16_t fp16_sin(fp16_t angle)
{
    fp16_t cos_val, sin_val;
    fp16_cordic_rotate(angle, &cos_val, &sin_val);
    return sin_val;
}

/* Cosine Function using CORDIC algorithm */
/* Input: angle in Q1.14 radians, range [-pi/2, pi/2] */
/* Output: cos(angle) in Q1.14 format */
fp16_t fp16_cos(fp16_t angle)
{
    fp16_t cos_val, sin_val;
    fp16_cordic_rotate(angle, &cos_val, &sin_val);
    return cos_val;
}

/* Arctangent Function using CORDIC vectoring mode */
/* Input: y and x in Q1.14 format; x must be > 0 */
/* Output: atan2(y, x) in Q1.14 radians, range [-pi/2, pi/2] */
fp16_t fp16_atan2(fp16_t y_in, fp16_t x_in)
{
    if (x_in <= 0)
    {
        /* Degenerate: x <= 0 is outside the valid domain for this function.
         * Return +/-pi/2 for x==0 (based on y sign), or FP16_MIN_VALUE as an
         * error sentinel for x < 0.  atan2(0,0) is undefined: return 0. */
        if (x_in == 0)
        {
            if (y_in > 0) return (fp16_t)FP16_HALF_PI;
            if (y_in < 0) return (fp16_t)(-FP16_HALF_PI);
            return (fp16_t)0; /* atan2(0,0): undefined, return 0 */
        }
        return (fp16_t)FP16_MIN_VALUE;
    }

    int32_t x = (int32_t)x_in;
    int32_t y = (int32_t)y_in;
    int32_t z = 0;
    int i;

    for (i = 0; i < FP16_CORDIC_ITERATIONS; i++)
    {
        /* d = -sign(y): rotate to drive y toward zero */
        int32_t d = (y >= 0) ? -1 : 1;
        int32_t x_new = x - d * (y >> i);
        int32_t y_new = y + d * (x >> i);
        int32_t z_new = z - d * (int32_t)fp16_cordic_atan_lut[i];
        x = x_new;
        y = y_new;
        z = z_new;
    }

    /* Clamp to Q1.14 range */
    if (z > (int32_t)FP16_MAX_VALUE)
        z = (int32_t)FP16_MAX_VALUE;
    if (z < (int32_t)FP16_MIN_VALUE)
        z = (int32_t)FP16_MIN_VALUE;

    return (fp16_t)z;
}
/* End of fixed-point-math.c */