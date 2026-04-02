#include "fp16_wrapper.h"
#include <math.h>

// Range conversion wrapper for fp16 exponential function
// Uses range reduction: exp(x) = exp(k*ln(2) + r) = 2^k * exp(r)
float fp16_float_exp(float x)
{
    int32_t k = 0;
    if (x < -LN2_APPROX || x > LN2_APPROX)
    {
        k = (int32_t)(x * INV_LN2_APPROX);
        x = x - k * LN2_APPROX;
    }
    fp16_t x_fp16 = float_to_fp16(x);
    fp16_t result_fp16 = fp16_poly_exp(x_fp16);
    float result = fp16_to_float(result_fp16);
    // Scale result by 2^k
    if (k > 0)
    {
        result *= (float)(1 << k);
    }
    else if (k < 0)
    {
        result /= (float)(1 << (-k));
    }
    return result;
}

double fp16_double_exp(double x)
{
    int32_t k = 0;
    if (x < -LN2_APPROX || x > LN2_APPROX)
    {
        k = (int32_t)(x * INV_LN2_APPROX);
        x = x - k * LN2_APPROX;
    }
    fp16_t x_fp16 = double_to_fp16(x);
    fp16_t result_fp16 = fp16_poly_exp(x_fp16);
    double result = fp16_to_double(result_fp16);
    // Scale result by 2^k
    if (k > 0)
    {
        result *= (double)(1 << k);
    }
    else if (k < 0)
    {
        result /= (double)(1 << (-k));
    }
    return result;
}

// Range conversion wrapper for fp16 natural logarithm function
// Uses: ln(x) = ln(2^k * r) = k*ln(2) + ln(r) where r is in [1, 2]
float fp16_float_ln(float x)
{
    if (x <= 0.0f)
    {
        // Handle domain error for ln(x) where x <= 0
        return -1e30f; // Return a large negative number to indicate error
    }
    int32_t k = 0;
    while (x > 2.0f)
    {
        x *= 0.5f;
        k++;
    }
    while (x < 1.0f)
    {
        x *= 2.0f;
        k--;
    }
    fp16_t x_fp16 = float_to_fp16(x - 1.0f);
    fp16_t result_fp16 = fp16_ln(x_fp16);
    float result = fp16_to_float(result_fp16);
    // Adjust result by adding k * ln(2)
    result += k * LN2_APPROX;
    return result;
}

double fp16_double_ln(double x)
{
    if (x <= 0.0)
    {
        // Handle domain error for ln(x) where x <= 0
        return -1e300; // Return a large negative number to indicate error
    }
    int32_t k = 0;
    while (x > 2.0)
    {
        x *= 0.5;
        k++;
    }
    while (x < 1.0)
    {
        x *= 2.0;
        k--;
    }
    fp16_t x_fp16 = double_to_fp16(x - 1.0);
    fp16_t result_fp16 = fp16_ln(x_fp16);
    double result = fp16_to_double(result_fp16);
    // Adjust result by adding k * ln(2)
    result += k * LN2_APPROX;
    return result;
}

/* ========================================================================
 * CORDIC Trigonometric Wrappers
 * ======================================================================== */

/* Range-reduction helper: reduce angle to [-pi, pi] */
static float reduce_to_pi_f(float a)
{
    const float TWO_PI = 2.0f * (float)PI_APPROX;
    while (a > (float)PI_APPROX)
        a -= TWO_PI;
    while (a < -(float)PI_APPROX)
        a += TWO_PI;
    return a;
}

static double reduce_to_pi_d(double a)
{
    const double TWO_PI = 2.0 * PI_APPROX;
    while (a > PI_APPROX)
        a -= TWO_PI;
    while (a < -PI_APPROX)
        a += TWO_PI;
    return a;
}

/* Sine wrapper: supports any angle (in radians).
 * Range reduction: sin(pi - x) = sin(x), sin(-pi - x) = sin(x) with sign. */
float fp16_float_sin(float angle)
{
    int sign = 1;
    angle = reduce_to_pi_f(angle);
    if (angle > (float)HALF_PI_APPROX)
    {
        angle = (float)PI_APPROX - angle;
    }
    else if (angle < -(float)HALF_PI_APPROX)
    {
        angle = -(float)PI_APPROX - angle;
        sign = -1;
    }
    fp16_t angle_fp16 = float_to_fp16(angle);
    fp16_t sin_fp16 = fp16_sin(angle_fp16);
    float result = fp16_to_float(sin_fp16);
    return sign < 0 ? -result : result;
}

/* Cosine wrapper: supports any angle (in radians).
 * cos(pi - x) = -cos(x), cos(-pi - x) = -cos(x). */
float fp16_float_cos(float angle)
{
    int neg = 0;
    angle = reduce_to_pi_f(angle);
    if (angle > (float)HALF_PI_APPROX)
    {
        angle = (float)PI_APPROX - angle;
        neg = 1;
    }
    else if (angle < -(float)HALF_PI_APPROX)
    {
        angle = -(float)PI_APPROX - angle;
        neg = 1;
    }
    fp16_t angle_fp16 = float_to_fp16(angle);
    fp16_t cos_fp16 = fp16_cos(angle_fp16);
    float result = fp16_to_float(cos_fp16);
    return neg ? -result : result;
}

/* Atan2 wrapper: full four-quadrant arctangent, returns radians.
 * Scales inputs to fit Q1.14, adjusts for x < 0. */
float fp16_float_atan2(float y, float x)
{
    float adj = 0.0f;
    if (x == 0.0f)
    {
        if (y > 0.0f)
            return (float)HALF_PI_APPROX;
        if (y < 0.0f)
            return -(float)HALF_PI_APPROX;
        return 0.0f;
    }
    if (x < 0.0f)
    {
        x = -x;
        y = -y;
        adj = (y >= 0.0f) ? -(float)PI_APPROX : (float)PI_APPROX;
    }
    /* Scale both x and y so the larger fits within Q1.14 (< ~1.9) */
    float mag = (x > (y < 0.0f ? -y : y)) ? x : (y < 0.0f ? -y : y);
    if (mag > 1.9f)
    {
        float scale = mag / 1.9f;
        x /= scale;
        y /= scale;
    }
    fp16_t y_fp16 = float_to_fp16(y);
    fp16_t x_fp16 = float_to_fp16(x);
    fp16_t result_fp16 = fp16_atan2(y_fp16, x_fp16);
    return fp16_to_float(result_fp16) + adj;
}

/* Double-precision variants */
double fp16_double_sin(double angle)
{
    int sign = 1;
    angle = reduce_to_pi_d(angle);
    if (angle > HALF_PI_APPROX)
    {
        angle = PI_APPROX - angle;
    }
    else if (angle < -HALF_PI_APPROX)
    {
        angle = -PI_APPROX - angle;
        sign = -1;
    }
    fp16_t angle_fp16 = double_to_fp16(angle);
    fp16_t sin_fp16 = fp16_sin(angle_fp16);
    double result = fp16_to_double(sin_fp16);
    return sign < 0 ? -result : result;
}

double fp16_double_cos(double angle)
{
    int neg = 0;
    angle = reduce_to_pi_d(angle);
    if (angle > HALF_PI_APPROX)
    {
        angle = PI_APPROX - angle;
        neg = 1;
    }
    else if (angle < -HALF_PI_APPROX)
    {
        angle = -PI_APPROX - angle;
        neg = 1;
    }
    fp16_t angle_fp16 = double_to_fp16(angle);
    fp16_t cos_fp16 = fp16_cos(angle_fp16);
    double result = fp16_to_double(cos_fp16);
    return neg ? -result : result;
}

double fp16_double_atan2(double y, double x)
{
    double adj = 0.0;
    if (x == 0.0)
    {
        if (y > 0.0)
            return HALF_PI_APPROX;
        if (y < 0.0)
            return -HALF_PI_APPROX;
        return 0.0;
    }
    if (x < 0.0)
    {
        x = -x;
        y = -y;
        adj = (y >= 0.0) ? -PI_APPROX : PI_APPROX;
    }
    /* Scale both x and y so the larger fits within Q1.14 (< ~1.9) */
    double mag = (x > (y < 0.0 ? -y : y)) ? x : (y < 0.0 ? -y : y);
    if (mag > 1.9)
    {
        double scale = mag / 1.9;
        x /= scale;
        y /= scale;
    }
    fp16_t y_fp16 = double_to_fp16(y);
    fp16_t x_fp16 = double_to_fp16(x);
    fp16_t result_fp16 = fp16_atan2(y_fp16, x_fp16);
    return fp16_to_double(result_fp16) + adj;
}