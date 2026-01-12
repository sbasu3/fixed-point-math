#define _POSIX_C_SOURCE 199309L
#include "util.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

#define NUM_ITERATIONS 10000
#define TEST_RANGE 1.5        /* Test range for Q1.14 and Q1.30 formats */
#define EPSILON_FP16 0.0001   /* Tolerance for fp16 (Q1.14) */
#define EPSILON_FP32 0.000001 /* Tolerance for fp32 (Q1.30) */

/* Statistics structure */
typedef struct
{
    double max_error;
    double avg_error;
    double total_time_ns;
    int num_tests;
} test_stats_t;

/* Helper function to calculate absolute error */
static inline double abs_error(double a, double b)
{
    double diff = a - b;
    return diff < 0 ? -diff : diff;
}

/* Test float to fp16 and back */
void test_float_fp16_conversions(test_stats_t *stats)
{
    struct timespec start, end;
    double total_error = 0.0;
    double max_error = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        /* Generate test value in valid range [-1.5, 1.5] */
        float test_val = ((float)i / (NUM_ITERATIONS - 1)) * 2.0f * TEST_RANGE - TEST_RANGE;

        /* Convert float -> fp16 -> float */
        fp16_t fp_val = float_to_fp16(test_val);
        float result = fp16_to_float(fp_val);

        /* Calculate error */
        double error = abs_error(test_val, result);
        total_error += error;
        if (error > max_error)
            max_error = error;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    /* Calculate timing */
    uint64_t elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000ULL +
                          (end.tv_nsec - start.tv_nsec);

    stats->max_error = max_error;
    stats->avg_error = total_error / NUM_ITERATIONS;
    stats->total_time_ns = (double)elapsed_ns;
    stats->num_tests = NUM_ITERATIONS;
}

/* Test double to fp16 and back */
void test_double_fp16_conversions(test_stats_t *stats)
{
    struct timespec start, end;
    double total_error = 0.0;
    double max_error = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        /* Generate test value in valid range [-1.5, 1.5] */
        double test_val = ((double)i / (NUM_ITERATIONS - 1)) * 2.0 * TEST_RANGE - TEST_RANGE;

        /* Convert double -> fp16 -> double */
        fp16_t fp_val = double_to_fp16(test_val);
        double result = fp16_to_double(fp_val);

        /* Calculate error */
        double error = abs_error(test_val, result);
        total_error += error;
        if (error > max_error)
            max_error = error;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    /* Calculate timing */
    uint64_t elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000ULL +
                          (end.tv_nsec - start.tv_nsec);

    stats->max_error = max_error;
    stats->avg_error = total_error / NUM_ITERATIONS;
    stats->total_time_ns = (double)elapsed_ns;
    stats->num_tests = NUM_ITERATIONS;
}

/* Test float to fp32 and back */
void test_float_fp32_conversions(test_stats_t *stats)
{
    struct timespec start, end;
    double total_error = 0.0;
    double max_error = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        /* Generate test value in valid range [-1.5, 1.5] */
        float test_val = ((float)i / (NUM_ITERATIONS - 1)) * 2.0f * TEST_RANGE - TEST_RANGE;

        /* Convert float -> fp32 -> float */
        fp32_t fp_val = float_to_fp32(test_val);
        float result = fp32_to_float(fp_val);

        /* Calculate error */
        double error = abs_error(test_val, result);
        total_error += error;
        if (error > max_error)
            max_error = error;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    /* Calculate timing */
    uint64_t elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000ULL +
                          (end.tv_nsec - start.tv_nsec);

    stats->max_error = max_error;
    stats->avg_error = total_error / NUM_ITERATIONS;
    stats->total_time_ns = (double)elapsed_ns;
    stats->num_tests = NUM_ITERATIONS;
}

/* Test double to fp32 and back */
void test_double_fp32_conversions(test_stats_t *stats)
{
    struct timespec start, end;
    double total_error = 0.0;
    double max_error = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        /* Generate test value in valid range [-1.5, 1.5] */
        double test_val = ((double)i / (NUM_ITERATIONS - 1)) * 2.0 * TEST_RANGE - TEST_RANGE;

        /* Convert double -> fp32 -> double */
        fp32_t fp_val = double_to_fp32(test_val);
        double result = fp32_to_double(fp_val);

        /* Calculate error */
        double error = abs_error(test_val, result);
        total_error += error;
        if (error > max_error)
            max_error = error;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    /* Calculate timing */
    uint64_t elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000ULL +
                          (end.tv_nsec - start.tv_nsec);

    stats->max_error = max_error;
    stats->avg_error = total_error / NUM_ITERATIONS;
    stats->total_time_ns = (double)elapsed_ns;
    stats->num_tests = NUM_ITERATIONS;
}

/* Test fp16 to fp32 and back */
void test_fp16_fp32_conversions(test_stats_t *stats)
{
    struct timespec start, end;
    double total_error = 0.0;
    double max_error = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        /* Generate test value in valid range for fp16 */
        double test_val = ((double)i / (NUM_ITERATIONS - 1)) * 2.0 * TEST_RANGE - TEST_RANGE;
        fp16_t fp16_val = double_to_fp16(test_val);

        /* Convert fp16 -> fp32 -> fp16 */
        fp32_t fp32_val = fp16_to_fp32(fp16_val);
        fp16_t result = fp32_to_fp16(fp32_val);

        /* Calculate error in double precision */
        double orig = fp16_to_double(fp16_val);
        double res = fp16_to_double(result);
        double error = abs_error(orig, res);

        total_error += error;
        if (error > max_error)
            max_error = error;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    /* Calculate timing */
    uint64_t elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000ULL +
                          (end.tv_nsec - start.tv_nsec);

    stats->max_error = max_error;
    stats->avg_error = total_error / NUM_ITERATIONS;
    stats->total_time_ns = (double)elapsed_ns;
    stats->num_tests = NUM_ITERATIONS;
}

/* Print test results */
void print_results(const char *test_name, const test_stats_t *stats)
{
    double ns_per_calc = stats->total_time_ns / stats->num_tests;

    printf("\n%s:\n", test_name);
    printf("  Iterations:       %d\n", stats->num_tests);
    printf("  Max Error:        %.9e\n", stats->max_error);
    printf("  Average Error:    %.9e\n", stats->avg_error);
    printf("  Total Time:       %.2f ms\n", stats->total_time_ns / 1000000.0);
    printf("  Time per calc:    %.2f ns\n", ns_per_calc);
    printf("  Throughput:       %.2f M calcs/sec\n", 1000.0 / ns_per_calc);
}

int main(void)
{
    test_stats_t stats;
    int passed = 0;
    int failed = 0;

    printf("==========================================================\n");
    printf("Fixed-Point Conversion Functions Test Suite\n");
    printf("==========================================================\n");
    printf("Testing with %d iterations per test\n", NUM_ITERATIONS);
    printf("Test range: [%.1f, %.1f]\n", -TEST_RANGE, TEST_RANGE);
    printf("==========================================================\n");

    /* Test 1: float <-> fp16 conversions */
    test_float_fp16_conversions(&stats);
    print_results("Float <-> FP16 (Q1.14) Conversion", &stats);
    if (stats.max_error < EPSILON_FP16)
    {
        printf("  ✓ PASSED\n");
        passed++;
    }
    else
    {
        printf("  ✗ FAILED (max error exceeds threshold)\n");
        failed++;
    }

    /* Test 2: double <-> fp16 conversions */
    test_double_fp16_conversions(&stats);
    print_results("Double <-> FP16 (Q1.14) Conversion", &stats);
    if (stats.max_error < EPSILON_FP16)
    {
        printf("  ✓ PASSED\n");
        passed++;
    }
    else
    {
        printf("  ✗ FAILED (max error exceeds threshold)\n");
        failed++;
    }

    /* Test 3: float <-> fp32 conversions */
    test_float_fp32_conversions(&stats);
    print_results("Float <-> FP32 (Q1.30) Conversion", &stats);
    if (stats.max_error < EPSILON_FP32)
    {
        printf("  ✓ PASSED\n");
        passed++;
    }
    else
    {
        printf("  ✗ FAILED (max error exceeds threshold)\n");
        failed++;
    }

    /* Test 4: double <-> fp32 conversions */
    test_double_fp32_conversions(&stats);
    print_results("Double <-> FP32 (Q1.30) Conversion", &stats);
    if (stats.max_error < EPSILON_FP32)
    {
        printf("  ✓ PASSED\n");
        passed++;
    }
    else
    {
        printf("  ✗ FAILED (max error exceeds threshold)\n");
        failed++;
    }

    /* Test 5: fp16 <-> fp32 conversions */
    test_fp16_fp32_conversions(&stats);
    print_results("FP16 <-> FP32 Conversion", &stats);
    if (stats.max_error < EPSILON_FP16)
    {
        printf("  ✓ PASSED\n");
        passed++;
    }
    else
    {
        printf("  ✗ FAILED (max error exceeds threshold)\n");
        failed++;
    }

    /* Summary */
    printf("\n==========================================================\n");
    printf("Test Summary:\n");
    printf("  Passed: %d\n", passed);
    printf("  Failed: %d\n", failed);
    printf("==========================================================\n");

    return (failed == 0) ? 0 : 1;
}
