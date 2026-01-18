#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "defines.h"
#include "fixed-point-math.h"
#include "util.h"

/* Benchmark configuration */
#define BENCHMARK_ITERATIONS 100000
#define NUM_TEST_VALUES 12

int main(void)
{
    printf("fp16_sqrt (square root) tests\n");
    printf("==============================\n\n");
    printf("Testing square root function for x >= 0\n\n");

    int passed = 0;
    int failed = 0;

    /* Test case 1: sqrt(0) = 0 */
    {
        fp16_t input = 0;
        fp16_t result = fp16_sqrt(input);
        double result_d = fp16_to_double(result);
        double expected = 0.0;
        double error = fabs(result_d - expected);

        printf("Test 1: sqrt(0.0) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.001)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (error too large)\n\n");
            failed++;
        }
    }

    /* Test case 2: sqrt(1) = 1 */
    {
        fp16_t input = FP16_ONE_VALUE;
        fp16_t result = fp16_sqrt(input);
        double result_d = fp16_to_double(result);
        double expected = 1.0;
        double error = fabs(result_d - expected);

        printf("Test 2: sqrt(1.0) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.001)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (error too large)\n\n");
            failed++;
        }
    }

    /* Test case 3: sqrt(0.25) = 0.5 */
    {
        fp16_t input = double_to_fp16(0.25);
        fp16_t result = fp16_sqrt(input);
        double result_d = fp16_to_double(result);
        double expected = 0.5;
        double error = fabs(result_d - expected);

        printf("Test 3: sqrt(0.25) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.001)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (error too large)\n\n");
            failed++;
        }
    }

    /* Test case 4: sqrt(0.5) = 0.707... */
    {
        fp16_t input = double_to_fp16(0.5);
        fp16_t result = fp16_sqrt(input);
        double result_d = fp16_to_double(result);
        double expected = sqrt(0.5);
        double error = fabs(result_d - expected);

        printf("Test 4: sqrt(0.5) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (error too large)\n\n");
            failed++;
        }
    }

    /* Test case 5: sqrt(1.8) = 1.341... */
    {
        fp16_t input = double_to_fp16(1.8);
        fp16_t result = fp16_sqrt(input);
        double result_d = fp16_to_double(result);
        double expected = sqrt(1.8);
        double error = fabs(result_d - expected);

        printf("Test 5: sqrt(1.8) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (error too large)\n\n");
            failed++;
        }
    }

    /* Test case 6: sqrt(1.5) */
    {
        fp16_t input = double_to_fp16(1.5);
        fp16_t result = fp16_sqrt(input);
        double result_d = fp16_to_double(result);
        double expected = sqrt(1.5);
        double error = fabs(result_d - expected);

        printf("Test 6: sqrt(1.5) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (error too large)\n\n");
            failed++;
        }
    }

    /* Test case 7: sqrt(0.1) */
    {
        fp16_t input = double_to_fp16(0.1);
        fp16_t result = fp16_sqrt(input);
        double result_d = fp16_to_double(result);
        double expected = sqrt(0.1);
        double error = fabs(result_d - expected);

        printf("Test 7: sqrt(0.1) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (error too large)\n\n");
            failed++;
        }
    }

    /* Test case 8: sqrt(0.01) - Note: reduced precision for very small values */
    {
        fp16_t input = double_to_fp16(0.01);
        fp16_t result = fp16_sqrt(input);
        double result_d = fp16_to_double(result);
        double expected = sqrt(0.01);
        double error = fabs(result_d - expected);

        printf("Test 8: sqrt(0.01) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.01)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (error too large)\n\n");
            failed++;
        }
    }

    /* Test case 9: sqrt(1.75) */
    {
        fp16_t input = double_to_fp16(1.75);
        fp16_t result = fp16_sqrt(input);
        double result_d = fp16_to_double(result);
        double expected = sqrt(1.75);
        double error = fabs(result_d - expected);

        printf("Test 9: sqrt(1.75) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (error too large)\n\n");
            failed++;
        }
    }

    /* Test case 10: Error handling - negative input */
    {
        fp16_t input = double_to_fp16(-1.0);
        fp16_t result = fp16_sqrt(input);

        printf("Test 10: sqrt(-1.0) = %d (should return error value FP16_MIN_VALUE)\n",
               result);
        if (result == FP16_MIN_VALUE)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (should return FP16_MIN_VALUE for negative input)\n\n");
            failed++;
        }
    }

    /* Test case 11: Idempotence - sqrt(x*x) = x for x in valid range */
    {
        double original = 1.3;
        fp16_t x_squared = double_to_fp16(original * original);
        fp16_t sqrt_x_squared = fp16_sqrt(x_squared);

        double result_d = fp16_to_double(sqrt_x_squared);
        double error = fabs(result_d - original);

        printf("Test 11: sqrt(1.3^2) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, original, error);
        if (error < 0.005)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (error too large)\n\n");
            failed++;
        }
    }

    /* Test case 12: Monotonicity - sqrt is monotonic increasing */
    {
        double test_vals[] = {0.25, 0.5, 1.0, 1.5, 1.8};
        double results[5];
        int is_monotonic = 1;

        for (int i = 0; i < 5; i++)
        {
            fp16_t x = double_to_fp16(test_vals[i]);
            results[i] = fp16_to_double(fp16_sqrt(x));
        }

        printf("Test 12: Monotonicity check\n");
        for (int i = 0; i < 5; i++)
        {
            printf("  sqrt(%.2f) = %.6f\n", test_vals[i], results[i]);
        }

        for (int i = 0; i < 4; i++)
        {
            if (results[i] >= results[i + 1])
            {
                is_monotonic = 0;
                break;
            }
        }

        if (is_monotonic)
        {
            printf("PASS (monotonic)\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (not monotonic)\n\n");
            failed++;
        }
    }

    printf("\n========== Test Summary ==========\n");
    printf("Passed: %d / %d\n", passed, 12);
    printf("Failed: %d / %d\n", failed, 12);

    /* ============ PERFORMANCE BENCHMARKS ============ */
    printf("\n========== Performance Benchmarks ==========\n");
    printf("Running %d iterations of fp16_sqrt across %d test values...\n\n",
           BENCHMARK_ITERATIONS, NUM_TEST_VALUES);

    /* Test values covering various ranges within Q1.14 limits */
    double test_values[NUM_TEST_VALUES] = {
        0.01, 0.1, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 1.9, 1.8, 0.6};

    fp16_t fp16_test_values[NUM_TEST_VALUES];
    for (int i = 0; i < NUM_TEST_VALUES; i++)
    {
        fp16_test_values[i] = double_to_fp16(test_values[i]);
    }

    /* Warmup - ensure CPU cache is primed */
    for (int iter = 0; iter < 1000; iter++)
    {
        for (int i = 0; i < NUM_TEST_VALUES; i++)
        {
            fp16_sqrt(fp16_test_values[i]);
        }
    }

    /* Actual benchmark */
    clock_t start_time = clock();
    for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
    {
        for (int i = 0; i < NUM_TEST_VALUES; i++)
        {
            fp16_sqrt(fp16_test_values[i]);
        }
    }
    clock_t end_time = clock();

    /* Calculate statistics */
    double total_calls = (double)BENCHMARK_ITERATIONS * NUM_TEST_VALUES;
    double elapsed_seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    double calls_per_second = total_calls / elapsed_seconds;
    double microseconds_per_call = (elapsed_seconds * 1e6) / total_calls;

    printf("Total function calls: %.0f\n", total_calls);
    printf("Elapsed time: %.6f seconds\n", elapsed_seconds);
    printf("Throughput: %.0f calls/sec\n", calls_per_second);
    printf("Per-call latency: %.2f microseconds\n\n", microseconds_per_call);

    /* Per-value benchmark */
    printf("Per-value latency breakdown:\n");
    printf("Input Value |  sqrt(x)  |  Latency (μs)\n");
    printf("------------|-----------|---------------\n");

    for (int i = 0; i < NUM_TEST_VALUES; i++)
    {
        clock_t val_start = clock();
        for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        {
            fp16_sqrt(fp16_test_values[i]);
        }
        clock_t val_end = clock();

        double val_elapsed = (double)(val_end - val_start) / CLOCKS_PER_SEC;
        double val_latency = (val_elapsed * 1e6) / BENCHMARK_ITERATIONS;
        double result_val = sqrt(test_values[i]);

        printf("   %7.2f  |  %7.4f  |   %.3f\n",
               test_values[i], result_val, val_latency);
    }

    printf("\n========== Benchmark Complete ==========\n");

    return failed > 0 ? 1 : 0;
}
