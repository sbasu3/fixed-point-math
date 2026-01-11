#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include "fixed-point-math.h"

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
        q1_6_t fixed = q1_6_from_float(f_values[i]);
        float back = q1_6_to_float(fixed);
        printf("  float %.2f -> Q1.6 %d -> float %.4f (error: %.4f)\n",
               f_values[i], (int)fixed, back, fabsf(f_values[i] - back));
    }

    /* Test double conversions */
    printf("\n");
    double d_values[] = {0.3333, 0.6666, 1.25, -0.875};
    int num_d_values = sizeof(d_values) / sizeof(d_values[0]);

    for (int i = 0; i < num_d_values; i++)
    {
        q1_6_t fixed = q1_6_from_double(d_values[i]);
        double back = q1_6_to_double(fixed);
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
        q1_14_t fixed = q1_14_from_float(f_values[i]);
        float back = q1_14_to_float(fixed);
        printf("  float %.3f -> Q1.14 %d -> float %.6f (error: %.6f)\n",
               f_values[i], (int)fixed, back, fabsf(f_values[i] - back));
    }

    /* Test double conversions */
    printf("\n");
    double d_values[] = {0.3333333, 0.6666666, 1.414213, -0.707106};
    int num_d_values = sizeof(d_values) / sizeof(d_values[0]);

    for (int i = 0; i < num_d_values; i++)
    {
        q1_14_t fixed = q1_14_from_double(d_values[i]);
        double back = q1_14_to_double(fixed);
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
        q1_30_t fixed = q1_30_from_float(f_values[i]);
        float back = q1_30_to_float(fixed);
        printf("  float %.6f -> Q1.30 %" PRId32 " -> float %.8f (error: %.8f)\n",
               f_values[i], fixed, back, fabsf(f_values[i] - back));
    }

    /* Test double conversions */
    printf("\n");
    double d_values[] = {0.3333333333, 0.6666666666, 1.41421356, -0.70710678, 1.23456789};
    int num_d_values = sizeof(d_values) / sizeof(d_values[0]);

    for (int i = 0; i < num_d_values; i++)
    {
        q1_30_t fixed = q1_30_from_double(d_values[i]);
        double back = q1_30_to_double(fixed);
        printf("  double %.10f -> Q1.30 %" PRId32 " -> double %.12f (error: %.12f)\n",
               d_values[i], fixed, back, fabs(d_values[i] - back));
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

    /* Test Q1.6 functions */
    printf("Testing Q1.6 format functions:\n");
    q1_6_t q6_result = q1_6_sin(0);
    printf("  q1_6_sin(0) = %d\n", (int)q6_result);

    /* Test Q1.14 functions */
    printf("\nTesting Q1.14 format functions:\n");
    q1_14_t q14_result = q1_14_sin(0);
    printf("  q1_14_sin(0) = %d\n", (int)q14_result);

    /* Test Q1.30 functions */
    printf("\nTesting Q1.30 format functions:\n");
    q1_30_t q30_result = q1_30_sin(0);
    printf("  q1_30_sin(0) = %" PRId32 "\n", q30_result);

    printf("\nAll function templates are accessible.\n");
    printf("Conversion tests completed.\n");
    printf("TODO: Implement actual function logic and comprehensive tests.\n");

    return 0;
}
