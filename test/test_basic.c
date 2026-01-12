#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include "fixed-point-math.h"
#include "utilities.h"

/*
 * Basic test file to verify the library structure
 * TODO: Add comprehensive unit tests
 */

void test_q1_6_conversions(void)
{
    printf("Testing Q1.6 Conversion Functions:\n");
    printf("----------------------------------\n");

    /* Test float conversions */
    float f_values[] = {0.5f, 0.75f, 1.0f, -0.5f, -1.0f, 0.25f, 1.5f};
    int num_values = sizeof(f_values) / sizeof(f_values[0]);

    for (int i = 0; i < num_values; i++)
    {
        Q1_6_t fixed = Q1_6_from_float(f_values[i]);
        float back = Q1_6_to_float(fixed);
        printf("  float %.2f -> Q1.6 %d -> float %.4f (error: %.4f)\n",
               f_values[i], (int)fixed, back, fabsf(f_values[i] - back));
    }

    /* Test double conversions */
    printf("\n");
    double d_values[] = {0.3333, 0.6666, 1.25, -0.875};
    int num_d_values = sizeof(d_values) / sizeof(d_values[0]);

    for (int i = 0; i < num_d_values; i++)
    {
        Q1_6_t fixed = Q1_6_from_double(d_values[i]);
        double back = Q1_6_to_double(fixed);
        printf("  double %.4f -> Q1.6 %d -> double %.6f (error: %.6f)\n",
               d_values[i], (int)fixed, back, fabs(d_values[i] - back));
    }
    printf("\n");
}

void test_q1_14_conversions(void)
{
    printf("Testing Q1.14 Conversion Functions:\n");
    printf("-----------------------------------\n");

    /* Test float conversions */
    float f_values[] = {0.5f, 0.75f, 1.0f, -0.5f, -1.0f, 0.123f, 1.999f};
    int num_values = sizeof(f_values) / sizeof(f_values[0]);

    for (int i = 0; i < num_values; i++)
    {
        Q1_14_t fixed = Q1_14_from_float(f_values[i]);
        float back = Q1_14_to_float(fixed);
        printf("  float %.3f -> Q1.14 %d -> float %.6f (error: %.6f)\n",
               f_values[i], (int)fixed, back, fabsf(f_values[i] - back));
    }

    /* Test double conversions */
    printf("\n");
    double d_values[] = {0.3333333, 0.6666666, 1.414213, -0.707106};
    int num_d_values = sizeof(d_values) / sizeof(d_values[0]);

    for (int i = 0; i < num_d_values; i++)
    {
        Q1_14_t fixed = Q1_14_from_double(d_values[i]);
        double back = Q1_14_to_double(fixed);
        printf("  double %.6f -> Q1.14 %d -> double %.8f (error: %.8f)\n",
               d_values[i], (int)fixed, back, fabs(d_values[i] - back));
    }
    printf("\n");
}

void test_q1_30_conversions(void)
{
    printf("Testing Q1.30 Conversion Functions:\n");
    printf("-----------------------------------\n");

    /* Test float conversions */
    float f_values[] = {0.5f, 0.75f, 1.0f, -0.5f, -1.0f, 0.987654f, 1.5f};
    int num_values = sizeof(f_values) / sizeof(f_values[0]);

    for (int i = 0; i < num_values; i++)
    {
        Q1_30_t fixed = Q1_30_from_float(f_values[i]);
        float back = Q1_30_to_float(fixed);
        printf("  float %.6f -> Q1.30 %" PRId32 " -> float %.8f (error: %.8f)\n",
               f_values[i], fixed, back, fabsf(f_values[i] - back));
    }

    /* Test double conversions */
    printf("\n");
    double d_values[] = {0.3333333333, 0.6666666666, 1.41421356, -0.70710678, 1.23456789};
    int num_d_values = sizeof(d_values) / sizeof(d_values[0]);

    for (int i = 0; i < num_d_values; i++)
    {
        Q1_30_t fixed = Q1_30_from_double(d_values[i]);
        double back = Q1_30_to_double(fixed);
        printf("  double %.10f -> Q1.30 %" PRId32 " -> double %.12f (error: %.12f)\n",
               d_values[i], fixed, back, fabs(d_values[i] - back));
    }
    printf("\n");
}

void test_scaled_conversions(void)
{
    printf("Testing Scaled Conversion Functions:\n");
    printf("====================================\n\n");

    /* Test Q1.14 scaled conversions with temperature range */
    printf("Q1.14: Temperature range [0°C, 100°C]:\n");
    printf("---------------------------------------\n");
    float temps[] = {0.0f, 25.0f, 50.0f, 75.0f, 100.0f, 37.5f, 98.6f};
    int num_temps = sizeof(temps) / sizeof(temps[0]);

    for (int i = 0; i < num_temps; i++)
    {
        Q1_14_t fixed = Q1_14_from_float_scaled(temps[i], 0.0f, 100.0f);
        float back = Q1_14_to_float_scaled(fixed, 0.0f, 100.0f);
        printf("  %.1f°C -> Q1.14 %d -> %.2f°C (error: %.4f°C)\n",
               temps[i], (int)fixed, back, fabsf(temps[i] - back));
    }

    /* Test Q1.30 scaled conversions with angle range */
    printf("\nQ1.30: Angle range [-180°, 180°]:\n");
    printf("----------------------------------\n");
    double angles[] = {-180.0, -90.0, 0.0, 45.0, 90.0, 135.0, 180.0, -123.456};
    int num_angles = sizeof(angles) / sizeof(angles[0]);

    for (int i = 0; i < num_angles; i++)
    {
        Q1_30_t fixed = Q1_30_from_double_scaled(angles[i], -180.0, 180.0);
        double back = Q1_30_to_double_scaled(fixed, -180.0, 180.0);
        printf("  %.3f° -> Q1.30 %" PRId32 " -> %.6f° (error: %.6f°)\n",
               angles[i], fixed, back, fabs(angles[i] - back));
    }

    /* Test Q1.30 scaled conversions with percentage range */
    printf("\nQ1.30: Percentage range [0%%, 100%%]:\n");
    printf("------------------------------------\n");
    double percentages[] = {0.0, 12.5, 25.0, 50.0, 75.0, 87.5, 100.0, 33.333};
    int num_pcts = sizeof(percentages) / sizeof(percentages[0]);

    for (int i = 0; i < num_pcts; i++)
    {
        Q1_30_t fixed = Q1_30_from_double_scaled(percentages[i], 0.0, 100.0);
        double back = Q1_30_to_double_scaled(fixed, 0.0, 100.0);
        printf("  %.3f%% -> Q1.30 %" PRId32 " -> %.6f%% (error: %.8f%%)\n",
               percentages[i], fixed, back, fabs(percentages[i] - back));
    }

    /* Test Q1.14 scaled conversions with voltage range */
    printf("\nQ1.14: Voltage range [-5.0V, 5.0V]:\n");
    printf("-----------------------------------\n");
    float voltages[] = {-5.0f, -2.5f, 0.0f, 1.25f, 2.5f, 3.75f, 5.0f, -3.3f};
    int num_volts = sizeof(voltages) / sizeof(voltages[0]);

    for (int i = 0; i < num_volts; i++)
    {
        Q1_14_t fixed = Q1_14_from_float_scaled(voltages[i], -5.0f, 5.0f);
        float back = Q1_14_to_float_scaled(fixed, -5.0f, 5.0f);
        printf("  %.2fV -> Q1.14 %d -> %.4fV (error: %.6fV)\n",
               voltages[i], (int)fixed, back, fabsf(voltages[i] - back));
    }

    printf("\n");
}

void test_exp_functions(void)
{
    printf("Testing Exponential (exp) Functions:\n");
    printf("====================================\n\n");

    /* Define ln(2) for test range */
    const double LN2 = 0.693147180559945;

    /* Test values in range [-ln(2), ln(2)] */
    double test_values[] = {
        -LN2, /* -ln(2) */
        -0.6,
        -0.5,
        -0.4,
        -LN2 / 2, /* -ln(2)/2 */
        -0.25,
        -0.1,
        0.0,
        0.1,
        0.25,
        LN2 / 2, /* ln(2)/2 */
        0.4,
        0.5,
        0.6,
        LN2 /* ln(2) */
    };
    int num_values = sizeof(test_values) / sizeof(test_values[0]);

    /* Test Q1.6 exp function */
    printf("Q1.6 exp function:\n");
    printf("------------------\n");
    for (int i = 0; i < num_values; i++)
    {
        Q1_6_t input = Q1_6_from_double(test_values[i]);
        Q1_6_t result = Q1_6_exp(input);
        double result_double = Q1_6_to_double(result);
        double expected = exp(test_values[i]);
        double error = fabs(expected - result_double);
        double relative_error = (expected != 0.0) ? (error / fabs(expected)) * 100.0 : 0.0;

        printf("  exp(%.6f) -> expected: %.6f, got: %.6f (abs err: %.6f, rel err: %.2f%%)\n",
               test_values[i], expected, result_double, error, relative_error);
    }

    /* Test Q1.14 exp function */
    printf("\nQ1.14 exp function:\n");
    printf("-------------------\n");
    for (int i = 0; i < num_values; i++)
    {
        Q1_14_t input = Q1_14_from_double(test_values[i]);
        Q1_14_t result = Q1_14_exp(input);
        double result_double = Q1_14_to_double(result);
        double expected = exp(test_values[i]);
        double error = fabs(expected - result_double);
        double relative_error = (expected != 0.0) ? (error / fabs(expected)) * 100.0 : 0.0;

        printf("  exp(%.6f) -> expected: %.8f, got: %.8f (abs err: %.8f, rel err: %.4f%%)\n",
               test_values[i], expected, result_double, error, relative_error);
    }

    /* Test Q1.30 exp function */
    printf("\nQ1.30 exp function:\n");
    printf("-------------------\n");
    for (int i = 0; i < num_values; i++)
    {
        Q1_30_t input = Q1_30_from_double(test_values[i]);
        Q1_30_t result = Q1_30_exp(input);
        double result_double = Q1_30_to_double(result);
        double expected = exp(test_values[i]);
        double error = fabs(expected - result_double);
        double relative_error = (expected != 0.0) ? (error / fabs(expected)) * 100.0 : 0.0;

        printf("  exp(%.6f) -> expected: %.10f, got: %.10f (abs err: %.10f, rel err: %.6f%%)\n",
               test_values[i], expected, result_double, error, relative_error);
    }

    printf("\n");
}

int main(void)
{
    printf("Fixed-Point Math Library Test\n");
    printf("==============================\n\n");

    /* Test conversion functions */
    test_q1_6_conversions();
    test_q1_14_conversions();
    test_q1_30_conversions();

    /* Test scaled conversion functions */
    test_scaled_conversions();

    /* Test Q1.6 addition utility */
    {
        printf("\nTesting Q1.6 add utility:\n");
        printf("-------------------------\n");
        /* Helper lambda-like macros to build Q1_6 values */
        Q1_6_t a, b, r;

        /* Case 1: 0.50 + 0.25 = 0.75 */
        a.sign = 0;
        a.integer = 0;
        a.fractional = 32; /* 0.50 -> 32/64 */
        b.sign = 0;
        b.integer = 0;
        b.fractional = 16; /* 0.25 -> 16/64 */
        r = Q1_6_add(a, b);
        printf("  0.50 + 0.25 => sign=%u, int=%u, frac=%u (expect 0,0,48)\n",
               (unsigned)r.sign, (unsigned)r.integer, (unsigned)r.fractional);

        /* Case 2: 1.00 + 0.50 => clamp integer to 1 (overflow) */
        a.sign = 0;
        a.integer = 1;
        a.fractional = 0; /* 1.00 */
        b.sign = 0;
        b.integer = 0;
        b.fractional = 32; /* 0.50 */
        r = Q1_6_add(a, b);
        printf("  1.00 + 0.50 => sign=%u, int=%u, frac=%u (clamped int<=1)\n",
               (unsigned)r.sign, (unsigned)r.integer, (unsigned)r.fractional);

        /* Case 3: -0.75 + 0.50 = -0.25 */
        a.sign = 1;
        a.integer = 0;
        a.fractional = 48; /* -0.75 */
        b.sign = 0;
        b.integer = 0;
        b.fractional = 32; /* 0.50 */
        r = Q1_6_add(a, b);
        printf("  -0.75 + 0.50 => sign=%u, int=%u, frac=%u (expect 1,0,16)\n",
               (unsigned)r.sign, (unsigned)r.integer, (unsigned)r.fractional);

        /* Case 4: -0.25 + -0.50 = -0.75 */
        a.sign = 1;
        a.integer = 0;
        a.fractional = 16; /* -0.25 */
        b.sign = 1;
        b.integer = 0;
        b.fractional = 32; /* -0.50 */
        r = Q1_6_add(a, b);
        printf("  -0.25 + -0.50 => sign=%u, int=%u, frac=%u (expect 1,0,48)\n",
               (unsigned)r.sign, (unsigned)r.integer, (unsigned)r.fractional);
    }

    /* Test exponential functions */
    test_exp_functions();

    /* Test Q1.6 functions */
    printf("Testing Q1.6 format functions:\n");
    Q1_6_t q6_result = Q1_6_sin(0);
    printf("  Q1_6_sin(0) = %d\n", (int)q6_result);

    /* Test Q1.14 functions */
    printf("\nTesting Q1.14 format functions:\n");
    Q1_14_t q14_result = Q1_14_sin(0);
    printf("  Q1_14_sin(0) = %d\n", (int)q14_result);

    /* Test Q1.30 functions */
    printf("\nTesting Q1.30 format functions:\n");
    Q1_30_t q30_result = Q1_30_sin(0);
    printf("  Q1_30_sin(0) = %" PRId32 "\n", q30_result);

    printf("\nAll function templates are accessible.\n");
    printf("Conversion tests completed.\n");
    printf("TODO: Implement actual function logic and comprehensive tests.\n");

    return 0;
}
