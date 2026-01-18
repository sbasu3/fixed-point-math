#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "defines.h"
#include "fixed-point-math.h"
#include "util.h"

/* Define M_E if not available */
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

/* Benchmark configuration */
#define BENCHMARK_ITERATIONS 100000
#define NUM_TEST_VALUES 11

int main(void)
{
    printf("fp16_ln range tests (-0.5 to 0.5)\n");
    printf("==================================\n\n");
    printf("Testing ln(1+x) polynomial approximation for x in [-0.5, 0.5]\n\n");

    int passed = 0;
    int failed = 0;

    /* Test case 1: ln(1+0) = ln(1) = 0 */
    {
        fp16_t input = 0; /* x = 0, so ln(1+0) = ln(1) = 0 */
        fp16_t result = fp16_ln(input);
        double result_d = fp16_to_double(result);
        double expected = log(1.0); /* 0 */
        double error = fabs(result_d - expected);

        printf("Test 1: ln(1.0) via ln(1+0) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.05)
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

    /* Test case 2: ln(1.1) via ln(1+0.1) */
    {
        fp16_t input = double_to_fp16(0.1);
        fp16_t result = fp16_ln(input);
        double result_d = fp16_to_double(result);
        double expected = log(1.1);
        double error = fabs(result_d - expected);

        printf("Test 2: ln(1.1) via ln(1+0.1) = %.6f (expected %.6f, error: %.6f)\n",
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

    /* Test case 3: ln(1.2) via ln(1+0.2) */
    {
        fp16_t input = double_to_fp16(0.2);
        fp16_t result = fp16_ln(input);
        double result_d = fp16_to_double(result);
        double expected = log(1.2);
        double error = fabs(result_d - expected);

        printf("Test 3: ln(1.2) via ln(1+0.2) = %.6f (expected %.6f, error: %.6f)\n",
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

    /* Test case 4: ln(1.3) via ln(1+0.3) */
    {
        fp16_t input = double_to_fp16(0.3);
        fp16_t result = fp16_ln(input);
        double result_d = fp16_to_double(result);
        double expected = log(1.3);
        double error = fabs(result_d - expected);

        printf("Test 4: ln(1.3) via ln(1+0.3) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.025)
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

    /* Test case 5: ln(1.4) via ln(1+0.4) */
    {
        fp16_t input = double_to_fp16(0.4);
        fp16_t result = fp16_ln(input);
        double result_d = fp16_to_double(result);
        double expected = log(1.4);
        double error = fabs(result_d - expected);

        printf("Test 5: ln(1.4) via ln(1+0.4) = %.6f (expected %.6f, error: %.6f)\n",
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

    /* Test case 6: ln(1.5) via ln(1+0.5) */
    {
        fp16_t input = double_to_fp16(0.5);
        fp16_t result = fp16_ln(input);
        double result_d = fp16_to_double(result);
        double expected = log(1.5);
        double error = fabs(result_d - expected);

        printf("Test 6: ln(1.5) via ln(1+0.5) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.035)
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

    /* Test case 7: ln(0.9) via ln(1+(-0.1)) */
    {
        fp16_t input = double_to_fp16(-0.1);
        fp16_t result = fp16_ln(input);
        double result_d = fp16_to_double(result);
        double expected = log(0.9);
        double error = fabs(result_d - expected);

        printf("Test 7: ln(0.9) via ln(1-0.1) = %.6f (expected %.6f, error: %.6f)\n",
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

    /* Test case 8: ln(0.8) via ln(1+(-0.2)) */
    {
        fp16_t input = double_to_fp16(-0.2);
        fp16_t result = fp16_ln(input);
        double result_d = fp16_to_double(result);
        double expected = log(0.8);
        double error = fabs(result_d - expected);

        printf("Test 8: ln(0.8) via ln(1-0.2) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.025)
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

    /* Test case 9: ln(0.7) via ln(1+(-0.3)) */
    {
        fp16_t input = double_to_fp16(-0.3);
        fp16_t result = fp16_ln(input);
        double result_d = fp16_to_double(result);
        double expected = log(0.7);
        double error = fabs(result_d - expected);

        printf("Test 9: ln(0.7) via ln(1-0.3) = %.6f (expected %.6f, error: %.6f)\n",
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

    /* Test case 10: ln(0.6) via ln(1+(-0.4)) */
    {
        fp16_t input = double_to_fp16(-0.4);
        fp16_t result = fp16_ln(input);
        double result_d = fp16_to_double(result);
        double expected = log(0.6);
        double error = fabs(result_d - expected);

        printf("Test 10: ln(0.6) via ln(1-0.4) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.035)
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

    /* Test case 11: ln(0.5) via ln(1+(-0.5)) */
    {
        fp16_t input = double_to_fp16(-0.5);
        fp16_t result = fp16_ln(input);
        double result_d = fp16_to_double(result);
        double expected = log(0.5);
        double error = fabs(result_d - expected);

        printf("Test 11: ln(0.5) via ln(1-0.5) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.04)
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

    /* Test case 12: Monotonicity - values should be ordered */
    {
        fp16_t vals[5];
        double results[5];
        double expected[5];

        vals[0] = double_to_fp16(-0.4);
        vals[1] = double_to_fp16(-0.2);
        vals[2] = double_to_fp16(0.0);
        vals[3] = double_to_fp16(0.2);
        vals[4] = double_to_fp16(0.4);

        for (int i = 0; i < 5; i++)
        {
            results[i] = fp16_to_double(fp16_ln(vals[i]));
            expected[i] = log(1.0 + fp16_to_double(vals[i]));
        }

        printf("Test 12: Monotonicity check\n");
        printf("  ln(0.6) = %.6f (expected %.6f)\n", results[0], expected[0]);
        printf("  ln(0.8) = %.6f (expected %.6f)\n", results[1], expected[1]);
        printf("  ln(1.0) = %.6f (expected %.6f)\n", results[2], expected[2]);
        printf("  ln(1.2) = %.6f (expected %.6f)\n", results[3], expected[3]);
        printf("  ln(1.4) = %.6f (expected %.6f)\n", results[4], expected[4]);

        int is_monotonic = 1;
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
    printf("Running %d iterations of fp16_ln across %d test values...\n\n",
           BENCHMARK_ITERATIONS, NUM_TEST_VALUES);

    /* Test values spanning the full domain */
    double test_values[NUM_TEST_VALUES] = {
        -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5};

    fp16_t fp16_test_values[NUM_TEST_VALUES];
    for (int i = 0; i < NUM_TEST_VALUES; i++)
    {
        fp16_test_values[i] = double_to_fp16(test_values[i]);
    }

    /* Actual benchmark */
    clock_t start_time = clock();
    for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
    {
        for (int i = 0; i < NUM_TEST_VALUES; i++)
        {
            fp16_ln(fp16_test_values[i]);
        }
    }
    clock_t end_time = clock();

    /* Calculate statistics */
    double total_calls = (double)BENCHMARK_ITERATIONS * NUM_TEST_VALUES;
    double elapsed_seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    double calls_per_second = total_calls / elapsed_seconds;
    double nanoseconds_per_call = (elapsed_seconds * 1e9) / total_calls;

    printf("Total function calls: %.0f\n", total_calls);
    printf("Elapsed time: %.6f seconds\n", elapsed_seconds);
    printf("Throughput: %.0f calls/sec\n", calls_per_second);
    printf("Per-call latency: %.2f nanoseconds\n\n", nanoseconds_per_call);

    /* Per-value benchmark */
    printf("Per-value latency breakdown:\n");
    printf("Input Value | Decimal |  Latency (ns)\n");
    printf("------------|---------|---------------\n");

    for (int i = 0; i < NUM_TEST_VALUES; i++)
    {
        clock_t val_start = clock();
        for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        {
            fp16_ln(fp16_test_values[i]);
        }
        clock_t val_end = clock();

        double val_elapsed = (double)(val_end - val_start) / CLOCKS_PER_SEC;
        double val_latency = (val_elapsed * 1e9) / BENCHMARK_ITERATIONS;

        printf("   %6.1f   |  %.1f   |   %.3f\n",
               test_values[i], 1.0 + test_values[i], val_latency);
    }

    printf("\n========== Benchmark Complete ==========\n");

    return failed > 0 ? 1 : 0;
}
