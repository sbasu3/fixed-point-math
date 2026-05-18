#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "fp16_cordic.h"
#include "util.h"

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define NUM_TEST_VALUES 10
#define BENCHMARK_ITERATIONS 100000
#define TEST_TOLERANCE 0.01

int main(void)
{
    int passed = 0;
    int failed = 0;

    printf("fp16_cordic CORDIC trigonometric tests\n");
    printf("========================================\n\n");
    printf("Testing CORDIC-based sin, cos, and atan2 functions\n\n");

    /* ========== CORDIC SIN TESTS ========== */
    printf("=== cordic_sin Tests ===\n\n");

    /* Test case 1: sin(0) = 0 */
    {
        fp16_t angle = double_to_fp16(0.0);
        fp16_t result = cordic_sin(angle);
        double result_d = fp16_to_double(result);
        double expected = sin(0.0);
        double error = fabs(result_d - expected);

        printf("Test 1: sin(0.0) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* Test case 2: sin(π/6) ≈ 0.5 */
    {
        fp16_t angle = double_to_fp16(M_PI / 6.0);
        fp16_t result = cordic_sin(angle);
        double result_d = fp16_to_double(result);
        double expected = sin(M_PI / 6.0);
        double error = fabs(result_d - expected);

        printf("Test 2: sin(π/6) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* Test case 3: sin(π/4) ≈ 0.707 */
    {
        fp16_t angle = double_to_fp16(M_PI / 4.0);
        fp16_t result = cordic_sin(angle);
        double result_d = fp16_to_double(result);
        double expected = sin(M_PI / 4.0);
        double error = fabs(result_d - expected);

        printf("Test 3: sin(π/4) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* Test case 4: sin(π/3) ≈ 0.866 */
    {
        fp16_t angle = double_to_fp16(M_PI / 3.0);
        fp16_t result = cordic_sin(angle);
        double result_d = fp16_to_double(result);
        double expected = sin(M_PI / 3.0);
        double error = fabs(result_d - expected);

        printf("Test 4: sin(π/3) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* Test case 5: sin(π/2) ≈ 1.0 */
    {
        fp16_t angle = double_to_fp16(M_PI / 2.0);
        fp16_t result = cordic_sin(angle);
        double result_d = fp16_to_double(result);
        double expected = sin(M_PI / 2.0);
        double error = fabs(result_d - expected);

        printf("Test 5: sin(π/2) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* ========== CORDIC COS TESTS ========== */
    printf("=== cordic_cos Tests ===\n\n");

    /* Test case 6: cos(0) = 1 */
    {
        fp16_t angle = double_to_fp16(0.0);
        fp16_t result = cordic_cos(angle);
        double result_d = fp16_to_double(result);
        double expected = cos(0.0);
        double error = fabs(result_d - expected);

        printf("Test 6: cos(0.0) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* Test case 7: cos(π/6) ≈ 0.866 */
    {
        fp16_t angle = double_to_fp16(M_PI / 6.0);
        fp16_t result = cordic_cos(angle);
        double result_d = fp16_to_double(result);
        double expected = cos(M_PI / 6.0);
        double error = fabs(result_d - expected);

        printf("Test 7: cos(π/6) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* Test case 8: cos(π/4) ≈ 0.707 */
    {
        fp16_t angle = double_to_fp16(M_PI / 4.0);
        fp16_t result = cordic_cos(angle);
        double result_d = fp16_to_double(result);
        double expected = cos(M_PI / 4.0);
        double error = fabs(result_d - expected);

        printf("Test 8: cos(π/4) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* Test case 9: cos(π/2) ≈ 0 */
    {
        fp16_t angle = double_to_fp16(M_PI / 2.0);
        fp16_t result = cordic_cos(angle);
        double result_d = fp16_to_double(result);
        double expected = cos(M_PI / 2.0);
        double error = fabs(result_d - expected);

        printf("Test 9: cos(π/2) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* Test case 10: cos(π) = -1 */
    {
        fp16_t angle = double_to_fp16(M_PI);
        fp16_t result = cordic_cos(angle);
        double result_d = fp16_to_double(result);
        double expected = cos(M_PI);
        double error = fabs(result_d - expected);

        printf("Test 10: cos(π) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* ========== CORDIC ATAN2 TESTS ========== */
    printf("=== cordic_atan2 Tests ===\n\n");

    /* Test case 11: atan2(0, 1) = 0 (angle to positive x-axis) */
    {
        fp16_t y = double_to_fp16(0.0);
        fp16_t x = double_to_fp16(1.0);
        fp16_t result = cordic_atan2(y, x);
        double result_d = fp16_to_double(result);
        double expected = atan2(0.0, 1.0);
        double error = fabs(result_d - expected);

        printf("Test 11: atan2(0, 1) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* Test case 12: atan2(1, 1) = π/4 (45 degrees) */
    {
        fp16_t y = double_to_fp16(1.0);
        fp16_t x = double_to_fp16(1.0);
        fp16_t result = cordic_atan2(y, x);
        double result_d = fp16_to_double(result);
        double expected = atan2(1.0, 1.0);
        double error = fabs(result_d - expected);

        printf("Test 12: atan2(1, 1) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* Test case 13: atan2(1, 0) = π/2 (90 degrees) */
    {
        fp16_t y = double_to_fp16(1.0);
        fp16_t x = double_to_fp16(0.0);
        fp16_t result = cordic_atan2(y, x);
        double result_d = fp16_to_double(result);
        double expected = atan2(1.0, 0.0);
        double error = fabs(result_d - expected);

        printf("Test 13: atan2(1, 0) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    /* Test case 14: atan2(0.5, 0.866) ≈ π/6 (30 degrees) */
    {
        fp16_t y = double_to_fp16(0.5);
        fp16_t x = double_to_fp16(0.866);
        fp16_t result = cordic_atan2(y, x);
        double result_d = fp16_to_double(result);
        double expected = atan2(0.5, 0.866);
        double error = fabs(result_d - expected);

        printf("Test 14: atan2(0.5, 0.866) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < TEST_TOLERANCE)
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

    printf("\n========== Test Summary ==========\n");
    printf("Passed: %d / 14\n", passed);
    printf("Failed: %d / 14\n", failed);

    /* ============ PERFORMANCE BENCHMARKS ============ */
    printf("\n========== Performance Benchmarks ==========\n");

    /* Benchmark cordic_sin */
    {
        printf("\n--- cordic_sin Benchmark ---\n");
        double test_values[NUM_TEST_VALUES] = {
            0.0, M_PI / 6.0, M_PI / 4.0, M_PI / 3.0, M_PI / 2.0,
            2.0 * M_PI / 3.0, 3.0 * M_PI / 4.0, 5.0 * M_PI / 6.0, M_PI, -M_PI / 4.0};

        fp16_t fp16_test_values[NUM_TEST_VALUES];
        for (int i = 0; i < NUM_TEST_VALUES; i++)
        {
            fp16_test_values[i] = double_to_fp16(test_values[i]);
        }

        /* Warmup */
        for (int iter = 0; iter < 1000; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                cordic_sin(fp16_test_values[i]);
            }
        }

        /* Benchmark */
        clock_t start = clock();
        for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                cordic_sin(fp16_test_values[i]);
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

    /* Benchmark cordic_cos */
    {
        printf("\n--- cordic_cos Benchmark ---\n");
        double test_values[NUM_TEST_VALUES] = {
            0.0, M_PI / 6.0, M_PI / 4.0, M_PI / 3.0, M_PI / 2.0,
            2.0 * M_PI / 3.0, 3.0 * M_PI / 4.0, 5.0 * M_PI / 6.0, M_PI, -M_PI / 4.0};

        fp16_t fp16_test_values[NUM_TEST_VALUES];
        for (int i = 0; i < NUM_TEST_VALUES; i++)
        {
            fp16_test_values[i] = double_to_fp16(test_values[i]);
        }

        /* Warmup */
        for (int iter = 0; iter < 1000; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                cordic_cos(fp16_test_values[i]);
            }
        }

        /* Benchmark */
        clock_t start = clock();
        for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                cordic_cos(fp16_test_values[i]);
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

    /* Benchmark cordic_atan2 */
    {
        printf("\n--- cordic_atan2 Benchmark ---\n");
        double y_values[NUM_TEST_VALUES] = {
            0.0, 0.5, 0.707, 0.866, 1.0,
            0.866, 0.707, 0.5, 0.0, -0.707};
        double x_values[NUM_TEST_VALUES] = {
            1.0, 0.866, 0.707, 0.5, 0.0,
            -0.5, -0.707, -0.866, -1.0, 0.707};

        fp16_t fp16_y[NUM_TEST_VALUES];
        fp16_t fp16_x[NUM_TEST_VALUES];
        for (int i = 0; i < NUM_TEST_VALUES; i++)
        {
            fp16_y[i] = double_to_fp16(y_values[i]);
            fp16_x[i] = double_to_fp16(x_values[i]);
        }

        /* Warmup */
        for (int iter = 0; iter < 1000; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                cordic_atan2(fp16_y[i], fp16_x[i]);
            }
        }

        /* Benchmark */
        clock_t start = clock();
        for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        {
            for (int i = 0; i < NUM_TEST_VALUES; i++)
            {
                cordic_atan2(fp16_y[i], fp16_x[i]);
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
