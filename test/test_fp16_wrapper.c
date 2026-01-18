#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fp16_wrapper.h"

/* Define M_E if not available */
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

/* Benchmark configuration */
#define BENCHMARK_ITERATIONS 100000
#define NUM_TEST_VALUES 10

int main(void)
{
    printf("fp16_wrapper function tests\n");
    printf("============================\n\n");
    printf("Testing range-extended wrapper functions for exp and ln\n\n");

    int passed = 0;
    int failed = 0;

    /* ========== EXPONENTIAL FUNCTION TESTS (FLOAT) ========== */
    printf("=== fp16_float_exp Tests ===\n\n");

    /* Test case 1: exp(0) = 1 */
    {
        float input = 0.0f;
        float result = fp16_float_exp(input);
        float expected = expf(input);
        float error = fabsf(result - expected);

        printf("Test 1: exp(%.2f) = %.6f (expected %.6f, error: %.6f)\n",
               input, result, expected, error);
        if (error < 0.01f)
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

    /* Test case 2: exp(1) = e */
    {
        float input = 1.0f;
        float result = fp16_float_exp(input);
        float expected = expf(input);
        float error = fabsf(result - expected);

        printf("Test 2: exp(%.2f) = %.6f (expected %.6f, error: %.6f)\n",
               input, result, expected, error);
        if (error < 0.05f)
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

    /* Test case 3: exp(-1) = 1/e */
    {
        float input = -1.0f;
        float result = fp16_float_exp(input);
        float expected = expf(input);
        float error = fabsf(result - expected);

        printf("Test 3: exp(%.2f) = %.6f (expected %.6f, error: %.6f)\n",
               input, result, expected, error);
        if (error < 0.05f)
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

    /* Test case 4: exp(2) - larger value */
    {
        float input = 2.0f;
        float result = fp16_float_exp(input);
        float expected = expf(input);
        float error = fabsf(result - expected);

        printf("Test 4: exp(%.2f) = %.6f (expected %.6f, error: %.6f)\n",
               input, result, expected, error);
        if (error < 0.5f)
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

    /* ========== LOGARITHM FUNCTION TESTS (FLOAT) ========== */
    printf("\n=== fp16_float_ln Tests ===\n\n");

    /* Test case 5: ln(1) = 0 */
    {
        float input = 1.0f;
        float result = fp16_float_ln(input);
        float expected = logf(input);
        float error = fabsf(result - expected);

        printf("Test 5: ln(%.2f) = %.6f (expected %.6f, error: %.6f)\n",
               input, result, expected, error);
        if (error < 0.01f)
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

    /* Test case 6: ln(e) = 1 */
    {
        float input = M_E;
        float result = fp16_float_ln(input);
        float expected = logf(input);
        float error = fabsf(result - expected);

        printf("Test 6: ln(%.6f) = %.6f (expected %.6f, error: %.6f)\n",
               input, result, expected, error);
        if (error < 0.05f)
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

    /* Test case 7: ln(2) - edge case at range boundary */
    {
        float input = 2.0f;
        float result = fp16_float_ln(input);
        float expected = logf(input);
        float error = fabsf(result - expected);

        printf("Test 7: ln(%.2f) = %.6f (expected %.6f, error: %.6f)\n",
               input, result, expected, error);
        if (error < 0.15f) /* Increased tolerance for range boundary */
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

    /* Test case 8: ln(10) - larger value */
    {
        float input = 10.0f;
        float result = fp16_float_ln(input);
        float expected = logf(input);
        float error = fabsf(result - expected);

        printf("Test 8: ln(%.2f) = %.6f (expected %.6f, error: %.6f)\n",
               input, result, expected, error);
        if (error < 0.1f)
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

    /* ========== EXPONENTIAL FUNCTION TESTS (DOUBLE) ========== */
    printf("\n=== fp16_double_exp Tests ===\n\n");

    /* Test case 9: exp(0) = 1 */
    {
        double input = 0.0;
        double result = fp16_double_exp(input);
        double expected = exp(input);
        double error = fabs(result - expected);

        printf("Test 9: exp(%.2f) = %.6f (expected %.6f, error: %.6f)\n",
               input, result, expected, error);
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

    /* Test case 10: exp(1.5) */
    {
        double input = 1.5;
        double result = fp16_double_exp(input);
        double expected = exp(input);
        double error = fabs(result - expected);

        printf("Test 10: exp(%.2f) = %.6f (expected %.6f, error: %.6f)\n",
               input, result, expected, error);
        if (error < 0.1)
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

    /* ========== LOGARITHM FUNCTION TESTS (DOUBLE) ========== */
    printf("\n=== fp16_double_ln Tests ===\n\n");

    /* Test case 11: ln(1) = 0 */
    {
        double input = 1.0;
        double result = fp16_double_ln(input);
        double expected = log(input);
        double error = fabs(result - expected);

        printf("Test 11: ln(%.2f) = %.6f (expected %.6f, error: %.6f)\n",
               input, result, expected, error);
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

    /* Test case 12: ln(5) */
    {
        double input = 5.0;
        double result = fp16_double_ln(input);
        double expected = log(input);
        double error = fabs(result - expected);

        printf("Test 12: ln(%.2f) = %.6f (expected %.6f, error: %.6f)\n",
               input, result, expected, error);
        if (error < 0.1)
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

    /* Test case 13: Error handling - ln(0) */
    {
        float input = 0.0f;
        float result = fp16_float_ln(input);

        printf("Test 13: ln(0.0) = %.6f (should return large negative error value)\n",
               result);
        if (result < -1e20f)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (should return error value)\n\n");
            failed++;
        }
    }

    /* Test case 14: Error handling - ln(-1) */
    {
        double input = -1.0;
        double result = fp16_double_ln(input);

        printf("Test 14: ln(-1.0) = %.6e (should return large negative error value)\n",
               result);
        if (result < -1e200)
        {
            printf("PASS\n\n");
            passed++;
        }
        else
        {
            printf("FAIL (should return error value)\n\n");
            failed++;
        }
    }

    printf("\n========== Test Summary ==========\n");
    printf("Passed: %d / %d\n", passed, 14);
    printf("Failed: %d / %d\n", failed, 14);

    /* ============ PERFORMANCE BENCHMARKS ============ */
    printf("\n========== Performance Benchmarks ==========\n");

    /* Benchmark fp16_float_exp */
    {
        printf("\n--- fp16_float_exp Benchmark ---\n");
        float test_values[NUM_TEST_VALUES] = {
            -2.0f, -1.5f, -1.0f, -0.5f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f};

        /* Warmup */
        for (int iter = 0; iter < 1000; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                fp16_float_exp(test_values[i]);
            }
        }

        /* Benchmark */
        clock_t start = clock();
        for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                fp16_float_exp(test_values[i]);
            }
        }
        clock_t end = clock();

        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        double total_calls = (double)BENCHMARK_ITERATIONS * NUM_TEST_VALUES;
        double calls_per_sec = total_calls / elapsed;
        double ns_per_call = (elapsed * 1e9) / total_calls;

        printf("Total calls: %.0f\n", total_calls);
        printf("Elapsed time: %.6f seconds\n", elapsed);
        printf("Throughput: %.0f calls/sec\n", calls_per_sec);
        printf("Per-call latency: %.2f nanoseconds\n", ns_per_call);
    }

    /* Benchmark fp16_float_ln */
    {
        printf("\n--- fp16_float_ln Benchmark ---\n");
        float test_values[NUM_TEST_VALUES] = {
            0.1f, 0.5f, 1.0f, 1.5f, 2.0f, 3.0f, 5.0f, 8.0f, 10.0f, 15.0f};

        /* Warmup */
        for (int iter = 0; iter < 1000; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                fp16_float_ln(test_values[i]);
            }
        }

        /* Benchmark */
        clock_t start = clock();
        for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                fp16_float_ln(test_values[i]);
            }
        }
        clock_t end = clock();

        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        double total_calls = (double)BENCHMARK_ITERATIONS * NUM_TEST_VALUES;
        double calls_per_sec = total_calls / elapsed;
        double ns_per_call = (elapsed * 1e9) / total_calls;

        printf("Total calls: %.0f\n", total_calls);
        printf("Elapsed time: %.6f seconds\n", elapsed);
        printf("Throughput: %.0f calls/sec\n", calls_per_sec);
        printf("Per-call latency: %.2f nanoseconds\n", ns_per_call);
    }

    /* Benchmark fp16_double_exp */
    {
        printf("\n--- fp16_double_exp Benchmark ---\n");
        double test_values[NUM_TEST_VALUES] = {
            -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5};

        /* Warmup */
        for (int iter = 0; iter < 1000; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                fp16_double_exp(test_values[i]);
            }
        }

        /* Benchmark */
        clock_t start = clock();
        for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                fp16_double_exp(test_values[i]);
            }
        }
        clock_t end = clock();

        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        double total_calls = (double)BENCHMARK_ITERATIONS * NUM_TEST_VALUES;
        double calls_per_sec = total_calls / elapsed;
        double ns_per_call = (elapsed * 1e9) / total_calls;

        printf("Total calls: %.0f\n", total_calls);
        printf("Elapsed time: %.6f seconds\n", elapsed);
        printf("Throughput: %.0f calls/sec\n", calls_per_sec);
        printf("Per-call latency: %.2f nanoseconds\n", ns_per_call);
    }

    /* Benchmark fp16_double_ln */
    {
        printf("\n--- fp16_double_ln Benchmark ---\n");
        double test_values[NUM_TEST_VALUES] = {
            0.1, 0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 8.0, 10.0, 15.0};

        /* Warmup */
        for (int iter = 0; iter < 1000; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                fp16_double_ln(test_values[i]);
            }
        }

        /* Benchmark */
        clock_t start = clock();
        for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                fp16_double_ln(test_values[i]);
            }
        }
        clock_t end = clock();

        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        double total_calls = (double)BENCHMARK_ITERATIONS * NUM_TEST_VALUES;
        double calls_per_sec = total_calls / elapsed;
        double ns_per_call = (elapsed * 1e9) / total_calls;

        printf("Total calls: %.0f\n", total_calls);
        printf("Elapsed time: %.6f seconds\n", elapsed);
        printf("Throughput: %.0f calls/sec\n", calls_per_sec);
        printf("Per-call latency: %.2f nanoseconds\n", ns_per_call);
    }

    printf("\n========== Benchmark Complete ==========\n");

    return failed > 0 ? 1 : 0;
}
