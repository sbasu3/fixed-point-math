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