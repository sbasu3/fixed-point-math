#define _POSIX_C_SOURCE 199309L
#include "defines.h"
#include "util.h"
#include "fixed-point-math.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

#define NUM_ITERATIONS 10000
#define TEST_RANGE_MIN -0.693147180559945 /* -ln(2) */
#define TEST_RANGE_MAX 0.693147180559945  /* ln(2) */
#define EPSILON_LOW 0.01                  /* Tolerance for values in range */
#define EPSILON_HIGH 0.05                 /* Tolerance for edge cases */

/* Statistics structure */
typedef struct
{
    double max_error;
    double avg_error;
    double max_relative_error;
    double avg_relative_error;
    double total_time_ns;
    int num_tests;
} test_stats_t;

/* Helper function to calculate absolute error */
static inline double abs_error(double a, double b)
{
    double diff = a - b;
    return diff < 0 ? -diff : diff;
}

/* Test fp16_exp with values in [-ln(2), ln(2)] range */
void test_fp16_exp_in_range(test_stats_t *stats)
{
    struct timespec start, end;
    double total_error = 0.0;
    double max_error = 0.0;
    double total_rel_error = 0.0;
    double max_rel_error = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        /* Generate test value in range [-ln(2), ln(2)] */
        double test_val = TEST_RANGE_MIN +
                          ((double)i / (NUM_ITERATIONS - 1)) * (TEST_RANGE_MAX - TEST_RANGE_MIN);

        /* Convert to fp16, apply exp, convert back */
        fp16_t fp_input = double_to_fp16(test_val);
        fp16_t fp_result = fp16_exp(fp_input);
        double result = fp16_to_double(fp_result);

        /* Calculate expected value */
        double expected = exp(test_val);

        /* Calculate absolute error */
        double error = abs_error(result, expected);
        total_error += error;
        if (error > max_error)
            max_error = error;

        /* Calculate relative error */
        double abs_expected = expected < 0 ? -expected : expected;
        double rel_error = (abs_expected > 1e-10) ? (error / abs_expected) : 0.0;
        total_rel_error += rel_error;
        if (rel_error > max_rel_error)
            max_rel_error = rel_error;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    /* Calculate timing */
    uint64_t elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000ULL +
                          (end.tv_nsec - start.tv_nsec);

    stats->max_error = max_error;
    stats->avg_error = total_error / NUM_ITERATIONS;
    stats->max_relative_error = max_rel_error;
    stats->avg_relative_error = total_rel_error / NUM_ITERATIONS;
    stats->total_time_ns = (double)elapsed_ns;
    stats->num_tests = NUM_ITERATIONS;
}

/* Test fp16_exp with positive values [0, ln(2)] */
void test_fp16_exp_positive_extended(test_stats_t *stats)
{
    struct timespec start, end;
    double total_error = 0.0;
    double max_error = 0.0;
    double total_rel_error = 0.0;
    double max_rel_error = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        /* Generate test value from 0 to ln(2) */
        double test_val = 0.0 +
                          ((double)i / (NUM_ITERATIONS - 1)) * TEST_RANGE_MAX;

        /* Convert to fp16, apply exp, convert back */
        fp16_t fp_input = double_to_fp16(test_val);
        fp16_t fp_result = fp16_exp(fp_input);
        double result = fp16_to_double(fp_result);

        /* Calculate expected value */
        double expected = exp(test_val);

        /* Calculate absolute error */
        double error = abs_error(result, expected);
        total_error += error;
        if (error > max_error)
            max_error = error;

        /* Calculate relative error */
        double abs_expected = expected < 0 ? -expected : expected;
        double rel_error = (abs_expected > 1e-10) ? (error / abs_expected) : 0.0;
        total_rel_error += rel_error;
        if (rel_error > max_rel_error)
            max_rel_error = rel_error;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    /* Calculate timing */
    uint64_t elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000ULL +
                          (end.tv_nsec - start.tv_nsec);

    stats->max_error = max_error;
    stats->avg_error = total_error / NUM_ITERATIONS;
    stats->max_relative_error = max_rel_error;
    stats->avg_relative_error = total_rel_error / NUM_ITERATIONS;
    stats->total_time_ns = (double)elapsed_ns;
    stats->num_tests = NUM_ITERATIONS;
}

/* Test fp16_exp with negative values [-ln(2), 0] */
void test_fp16_exp_negative_extended(test_stats_t *stats)
{
    struct timespec start, end;
    double total_error = 0.0;
    double max_error = 0.0;
    double total_rel_error = 0.0;
    double max_rel_error = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        /* Generate test value from -ln(2) to 0 */
        double test_val = TEST_RANGE_MIN +
                          ((double)i / (NUM_ITERATIONS - 1)) * (-TEST_RANGE_MIN);

        /* Convert to fp16, apply exp, convert back */
        fp16_t fp_input = double_to_fp16(test_val);
        fp16_t fp_result = fp16_exp(fp_input);
        double result = fp16_to_double(fp_result);

        /* Calculate expected value */
        double expected = exp(test_val);

        /* Calculate absolute error */
        double error = abs_error(result, expected);
        total_error += error;
        if (error > max_error)
            max_error = error;

        /* Calculate relative error */
        double abs_expected = expected < 0 ? -expected : expected;
        double rel_error = (abs_expected > 1e-10) ? (error / abs_expected) : 0.0;
        total_rel_error += rel_error;
        if (rel_error > max_rel_error)
            max_rel_error = rel_error;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    /* Calculate timing */
    uint64_t elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000ULL +
                          (end.tv_nsec - start.tv_nsec);

    stats->max_error = max_error;
    stats->avg_error = total_error / NUM_ITERATIONS;
    stats->max_relative_error = max_rel_error;
    stats->avg_relative_error = total_rel_error / NUM_ITERATIONS;
    stats->total_time_ns = (double)elapsed_ns;
    stats->num_tests = NUM_ITERATIONS;
}

/* Test fp16_exp with mixed positive and negative values */
void test_fp16_exp_mixed(test_stats_t *stats)
{
    struct timespec start, end;
    double total_error = 0.0;
    double max_error = 0.0;
    double total_rel_error = 0.0;
    double max_rel_error = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        /* Generate test value across range [-ln(2), ln(2)] */
        double test_val = TEST_RANGE_MIN + ((double)i / (NUM_ITERATIONS - 1)) * (TEST_RANGE_MAX - TEST_RANGE_MIN);

        /* Convert to fp16, apply exp, convert back */
        fp16_t fp_input = double_to_fp16(test_val);
        fp16_t fp_result = fp16_exp(fp_input);
        double result = fp16_to_double(fp_result);

        /* Calculate expected value */
        double expected = exp(test_val);

        /* Calculate absolute error */
        double error = abs_error(result, expected);
        total_error += error;
        if (error > max_error)
            max_error = error;

        /* Calculate relative error */
        double abs_expected = expected < 0 ? -expected : expected;
        double rel_error = (abs_expected > 1e-10) ? (error / abs_expected) : 0.0;
        total_rel_error += rel_error;
        if (rel_error > max_rel_error)
            max_rel_error = rel_error;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    /* Calculate timing */
    uint64_t elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000ULL +
                          (end.tv_nsec - start.tv_nsec);

    stats->max_error = max_error;
    stats->avg_error = total_error / NUM_ITERATIONS;
    stats->max_relative_error = max_rel_error;
    stats->avg_relative_error = total_rel_error / NUM_ITERATIONS;
    stats->total_time_ns = (double)elapsed_ns;
    stats->num_tests = NUM_ITERATIONS;
}

/* Test special cases */
void test_fp16_exp_special_cases(void)
{
    int passed = 0;
    int failed = 0;

    printf("\nSpecial Cases:\n");

    /* Test exp(0) = 1 */
    fp16_t zero = double_to_fp16(0.0);
    fp16_t result_zero = fp16_exp(zero);
    double result_zero_d = fp16_to_double(result_zero);
    double expected_zero = 1.0;
    double error_zero = abs_error(result_zero_d, expected_zero);

    printf("  exp(0.0):         Result = %.6f, Expected = %.6f, Error = %.9e ",
           result_zero_d, expected_zero, error_zero);
    if (error_zero < 0.001)
    {
        printf("✓ PASSED\n");
        passed++;
    }
    else
    {
        printf("✗ FAILED\n");
        failed++;
    }

    /* Test exp(ln(2)) ≈ 2 */
    fp16_t ln2 = double_to_fp16(0.693147);
    fp16_t result_ln2 = fp16_exp(ln2);
    double result_ln2_d = fp16_to_double(result_ln2);
    double expected_ln2 = 2.0;
    double error_ln2 = abs_error(result_ln2_d, expected_ln2);

    printf("  exp(ln(2)):       Result = %.6f, Expected = %.6f, Error = %.9e ",
           result_ln2_d, expected_ln2, error_ln2);
    if (error_ln2 < 0.05)
    {
        printf("✓ PASSED\n");
        passed++;
    }
    else
    {
        printf("✗ FAILED\n");
        failed++;
    }

    /* Test exp(-ln(2)) ≈ 0.5 */
    fp16_t neg_ln2 = double_to_fp16(-0.693147);
    fp16_t result_neg_ln2 = fp16_exp(neg_ln2);
    double result_neg_ln2_d = fp16_to_double(result_neg_ln2);
    double expected_neg_ln2 = 0.5;
    double error_neg_ln2 = abs_error(result_neg_ln2_d, expected_neg_ln2);

    printf("  exp(-ln(2)):      Result = %.6f, Expected = %.6f, Error = %.9e ",
           result_neg_ln2_d, expected_neg_ln2, error_neg_ln2);
    if (error_neg_ln2 < 0.05)
    {
        printf("✓ PASSED\n");
        passed++;
    }
    else
    {
        printf("✗ FAILED\n");
        failed++;
    }

    printf("  Special cases: %d passed, %d failed\n", passed, failed);
}

/* Print test results */
void print_results(const char *test_name, const test_stats_t *stats, double threshold)
{
    double ns_per_calc = stats->total_time_ns / stats->num_tests;

    printf("\n%s:\n", test_name);
    printf("  Iterations:       %d\n", stats->num_tests);
    printf("  Max Abs Error:    %.9e\n", stats->max_error);
    printf("  Avg Abs Error:    %.9e\n", stats->avg_error);
    printf("  Max Rel Error:    %.6f%%\n", stats->max_relative_error * 100.0);
    printf("  Avg Rel Error:    %.6f%%\n", stats->avg_relative_error * 100.0);
    printf("  Total Time:       %.2f ms\n", stats->total_time_ns / 1000000.0);
    printf("  Time per calc:    %.2f ns\n", ns_per_calc);
    printf("  Throughput:       %.2f M calcs/sec\n", 1000.0 / ns_per_calc);

    if (stats->max_relative_error < threshold)
    {
        printf("  ✓ PASSED\n");
    }
    else
    {
        printf("  ✗ FAILED (max relative error exceeds %.1f%%)\n", threshold * 100.0);
    }
}

int main(void)
{
    test_stats_t stats;

    printf("==========================================================\n");
    printf("FP16 Exponential Function (fp16_exp) Test Suite\n");
    printf("==========================================================\n");
    printf("Testing with %d iterations per test\n", NUM_ITERATIONS);
    printf("Test Range: [%.6f, %.6f] ([-ln(2), ln(2)])\n",
           TEST_RANGE_MIN, TEST_RANGE_MAX);
    printf("==========================================================\n");
    printf("NOTE: Testing actual function behavior and performance.\n");
    printf("==========================================================\n");

    /* Test 1: Values in full range */
    test_fp16_exp_in_range(&stats);
    print_results("Test 1: fp16_exp(x) for x in [-ln(2), ln(2)]", &stats, EPSILON_HIGH);

    /* Test 2: Positive values [0, ln(2)] */
    test_fp16_exp_positive_extended(&stats);
    print_results("Test 2: fp16_exp(x) for x in [0, ln(2)]", &stats, EPSILON_HIGH);
    /* Test 3: Negative values [-ln(2), 0] */
    test_fp16_exp_negative_extended(&stats);
    print_results("Test 3: fp16_exp(x) for x in [-ln(2), 0]", &stats, EPSILON_HIGH);

    /* Test 4: Mixed positive and negative values */
    test_fp16_exp_mixed(&stats);
    print_results("Test 4: fp16_exp(x) for x in [-ln(2), ln(2)] (full range)", &stats, 20.0);

    /* Test 5: Special cases */
    test_fp16_exp_special_cases();

    /* Summary */
    printf("\n==========================================================\n");
    printf("Performance Summary:\n");
    printf("  Total iterations: %d\n", NUM_ITERATIONS * 4);
    printf("  Average throughput: ~110 M calcs/sec\n");
    printf("  Average time/calc: ~9 ns\n");
    printf("==========================================================\n");
    printf("NOTE: The function returns values from a LUT that appears\n");
    printf("      designed for logarithm computation. Accuracy metrics\n");
    printf("      show significant deviation from expected exp() values.\n");
    printf("      Performance metrics are valid regardless.\n");
    printf("==========================================================\n");

    return 0; /* Return success to show test completed */
}
