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
    printf("fp16_inverse (reciprocal 1/x) tests\n");
    printf("=====================================\n\n");
    printf("Testing reciprocal function for x in valid range (|x| > 0.5, |x| < 2.0)\n");
    printf("Note: Q1.14 format has limited range; best for values near 1.0\n\n");

    int passed = 0;
    int failed = 0;

    /* Test case 1: inverse(1) = 1 */
    {
        fp16_t input = FP16_ONE_VALUE;
        fp16_t result = fp16_inverse(input);
        double result_d = fp16_to_double(result);
        double expected = 1.0;
        double error = fabs(result_d - expected);

        printf("Test 1: 1/1.0 = %.6f (expected %.6f, error: %.6f)\n",
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

    /* Test case 2: inverse(2) = 0.5 */
    {
        fp16_t input = double_to_fp16(2.0);
        fp16_t result = fp16_inverse(input);
        double result_d = fp16_to_double(result);
        double expected = 0.5;
        double error = fabs(result_d - expected);

        printf("Test 2: 1/2.0 = %.6f (expected %.6f, error: %.6f)\n",
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

    /* Test case 3: inverse(0.75) = 1.333... */
    {
        fp16_t input = double_to_fp16(0.75);
        fp16_t result = fp16_inverse(input);
        double result_d = fp16_to_double(result);
        double expected = 1.0 / 0.75;
        double error = fabs(result_d - expected);

        printf("Test 3: 1/0.75 = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.02)
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

    /* Test case 4: inverse(1.5) = 0.666... */
    {
        fp16_t input = double_to_fp16(1.5);
        fp16_t result = fp16_inverse(input);
        double result_d = fp16_to_double(result);
        double expected = 1.0 / 1.5;
        double error = fabs(result_d - expected);

        printf("Test 4: 1/1.5 = %.6f (expected %.6f, error: %.6f)\n",
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

    /* Test case 5: inverse(1.75) = 0.571... */
    {
        fp16_t input = double_to_fp16(1.75);
        fp16_t result = fp16_inverse(input);
        double result_d = fp16_to_double(result);
        double expected = 1.0 / 1.75;
        double error = fabs(result_d - expected);

        printf("Test 5: 1/1.75 = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.02)
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

    /* Test case 6: inverse(-1) = -1 */
    {
        fp16_t input = double_to_fp16(-1.0);
        fp16_t result = fp16_inverse(input);
        double result_d = fp16_to_double(result);
        double expected = -1.0;
        double error = fabs(result_d - expected);

        printf("Test 6: 1/(-1.0) = %.6f (expected %.6f, error: %.6f)\n",
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

    /* Test case 7: inverse(-1.75) = -0.571... */
    {
        fp16_t input = double_to_fp16(-1.75);
        fp16_t result = fp16_inverse(input);
        double result_d = fp16_to_double(result);
        double expected = -1.0 / 1.75;
        double error = fabs(result_d - expected);

        printf("Test 7: 1/(-1.75) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.02)
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

    /* Test case 8: inverse(-1.5) = -0.666... */
    {
        fp16_t input = double_to_fp16(-1.5);
        fp16_t result = fp16_inverse(input);
        double result_d = fp16_to_double(result);
        double expected = -1.0 / 1.5;
        double error = fabs(result_d - expected);

        printf("Test 8: 1/(-1.5) = %.6f (expected %.6f, error: %.6f)\n",
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

    /* Test case 9: inverse(0.6) = 1.667 */
    {
        fp16_t input = double_to_fp16(0.6);
        fp16_t result = fp16_inverse(input);
        double result_d = fp16_to_double(result);
        double expected = 1.0 / 0.6;
        double error = fabs(result_d - expected);

        printf("Test 9: 1/0.6 = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.03)
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

    /* Test case 10: inverse(1.25) = 0.8 */
    {
        fp16_t input = double_to_fp16(1.25);
        fp16_t result = fp16_inverse(input);
        double result_d = fp16_to_double(result);
        double expected = 1.0 / 1.25;
        double error = fabs(result_d - expected);

        printf("Test 10: 1/1.25 = %.6f (expected %.6f, error: %.6f)\n",
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

    /* Test case 11: Reciprocal property - 1/x then 1/(1/x) = x */
    {
        double original = 1.4;
        fp16_t x = double_to_fp16(original);
        fp16_t inv_x = fp16_inverse(x);
        fp16_t inv_inv_x = fp16_inverse(inv_x);

        double result_d = fp16_to_double(inv_inv_x);
        double error = fabs(result_d - original);

        printf("Test 11: Reciprocal property: 1/(1/1.4) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, original, error);
        if (error < 0.03)
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

    /* Test case 12: Sign preservation */
    {
        double test_vals[] = {1.3, -1.3};
        int sign_ok = 1;

        for (int i = 0; i < 2; i++)
        {
            fp16_t x = double_to_fp16(test_vals[i]);
            fp16_t result = fp16_inverse(x);
            double result_d = fp16_to_double(result);

            if ((test_vals[i] > 0 && result_d <= 0) || (test_vals[i] < 0 && result_d >= 0))
            {
                sign_ok = 0;
            }
        }

        printf("Test 12: Sign preservation\n");
        printf("  1/(1.3) = %.6f (should be positive)\n", fp16_to_double(fp16_inverse(double_to_fp16(1.3))));
        printf("  1/(-1.3) = %.6f (should be negative)\n", fp16_to_double(fp16_inverse(double_to_fp16(-1.3))));

        if (sign_ok)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (sign not preserved)\n\n");
            failed++;
        }
    }

    printf("\n========== Test Summary ==========\n");
    printf("Passed: %d / %d\n", passed, 12);
    printf("Failed: %d / %d\n", failed, 12);

    /* ============ PERFORMANCE BENCHMARKS ============ */
    printf("\n========== Performance Benchmarks ==========\n");
    printf("Running %d iterations of fp16_inverse across %d test values...\n\n",
           BENCHMARK_ITERATIONS, NUM_TEST_VALUES);

    /* Test values - avoid [-0.5, 0.5] and large values exceeding Q1.14 range */
    double test_values[NUM_TEST_VALUES] = {
        0.6, 0.75, 1.0, 1.25, 1.5, 1.75, -0.6, -0.75, -1.0, -1.25, -1.5, -1.75};

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
            fp16_inverse(fp16_test_values[i]);
        }
    }

    /* Actual benchmark */
    clock_t start_time = clock();
    for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
    {
        for (int i = 0; i < NUM_TEST_VALUES; i++)
        {
            fp16_inverse(fp16_test_values[i]);
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
    printf("Input Value |  1/x Value |  Latency (μs)\n");
    printf("------------|------------|---------------\n");

    for (int i = 0; i < NUM_TEST_VALUES; i++)
    {
        clock_t val_start = clock();
        for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        {
            fp16_inverse(fp16_test_values[i]);
        }
        clock_t val_end = clock();

        double val_elapsed = (double)(val_end - val_start) / CLOCKS_PER_SEC;
        double val_latency = (val_elapsed * 1e6) / BENCHMARK_ITERATIONS;
        double result_val = 1.0 / test_values[i];

        printf("   %7.2f  |   %7.2f  |   %.3f\n",
               test_values[i], result_val, val_latency);
    }

    printf("\n========== Benchmark Complete ==========\n");

    return failed > 0 ? 1 : 0;
}
