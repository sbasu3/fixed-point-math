#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "defines.h"
#include "fixed-point-math.h"
#include "fp16_wrapper.h"
#include "util.h"

/* Benchmark configuration */
#define BENCHMARK_ITERATIONS 100000
#define NUM_TEST_VALUES 12

int main(void)
{
    printf("fp16 CORDIC (sin / cos / atan2) tests\n");
    printf("======================================\n\n");

    int passed = 0;
    int failed = 0;

    /* ------------------------------------------------------------------
     * fp16_sin tests
     * ------------------------------------------------------------------ */
    printf("--- fp16_sin (CORDIC rotation, domain [-pi/2, pi/2]) ---\n\n");

    /* Test 1: sin(0) = 0 */
    {
        fp16_t input = 0;
        fp16_t result = fp16_sin(input);
        double result_d = fp16_to_double(result);
        double expected = 0.0;
        double error = fabs(result_d - expected);

        printf("Test 1: sin(0) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.001) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 2: sin(pi/6) = 0.5 */
    {
        fp16_t input = double_to_fp16(PI_APPROX / 6.0);
        fp16_t result = fp16_sin(input);
        double result_d = fp16_to_double(result);
        double expected = 0.5;
        double error = fabs(result_d - expected);

        printf("Test 2: sin(pi/6) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 3: sin(pi/4) = sqrt(2)/2 */
    {
        fp16_t input = double_to_fp16(PI_APPROX / 4.0);
        fp16_t result = fp16_sin(input);
        double result_d = fp16_to_double(result);
        double expected = sqrt(2.0) / 2.0;
        double error = fabs(result_d - expected);

        printf("Test 3: sin(pi/4) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 4: sin(pi/3) = sqrt(3)/2 */
    {
        fp16_t input = double_to_fp16(PI_APPROX / 3.0);
        fp16_t result = fp16_sin(input);
        double result_d = fp16_to_double(result);
        double expected = sqrt(3.0) / 2.0;
        double error = fabs(result_d - expected);

        printf("Test 4: sin(pi/3) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 5: sin(pi/2) = 1 */
    {
        fp16_t input = double_to_fp16(HALF_PI_APPROX);
        fp16_t result = fp16_sin(input);
        double result_d = fp16_to_double(result);
        double expected = 1.0;
        double error = fabs(result_d - expected);

        printf("Test 5: sin(pi/2) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 6: sin(-pi/4) = -sqrt(2)/2  (negative angle) */
    {
        fp16_t input = double_to_fp16(-PI_APPROX / 4.0);
        fp16_t result = fp16_sin(input);
        double result_d = fp16_to_double(result);
        double expected = -sqrt(2.0) / 2.0;
        double error = fabs(result_d - expected);

        printf("Test 6: sin(-pi/4) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* ------------------------------------------------------------------
     * fp16_cos tests
     * ------------------------------------------------------------------ */
    printf("--- fp16_cos (CORDIC rotation, domain [-pi/2, pi/2]) ---\n\n");

    /* Test 7: cos(0) = 1 */
    {
        fp16_t input = 0;
        fp16_t result = fp16_cos(input);
        double result_d = fp16_to_double(result);
        double expected = 1.0;
        double error = fabs(result_d - expected);

        printf("Test 7: cos(0) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 8: cos(pi/3) = 0.5 */
    {
        fp16_t input = double_to_fp16(PI_APPROX / 3.0);
        fp16_t result = fp16_cos(input);
        double result_d = fp16_to_double(result);
        double expected = 0.5;
        double error = fabs(result_d - expected);

        printf("Test 8: cos(pi/3) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 9: cos(pi/4) = sqrt(2)/2 */
    {
        fp16_t input = double_to_fp16(PI_APPROX / 4.0);
        fp16_t result = fp16_cos(input);
        double result_d = fp16_to_double(result);
        double expected = sqrt(2.0) / 2.0;
        double error = fabs(result_d - expected);

        printf("Test 9: cos(pi/4) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 10: cos(pi/2) = 0 */
    {
        fp16_t input = double_to_fp16(HALF_PI_APPROX);
        fp16_t result = fp16_cos(input);
        double result_d = fp16_to_double(result);
        double expected = 0.0;
        double error = fabs(result_d - expected);

        printf("Test 10: cos(pi/2) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 11: Pythagorean identity: sin^2 + cos^2 = 1 */
    {
        double angle = PI_APPROX / 5.0;
        fp16_t a_fp16 = double_to_fp16(angle);
        double s = fp16_to_double(fp16_sin(a_fp16));
        double c = fp16_to_double(fp16_cos(a_fp16));
        double identity = s * s + c * c;
        double error = fabs(identity - 1.0);

        printf("Test 11: sin^2(pi/5) + cos^2(pi/5) = %.6f (expected 1.0, error: %.6f)\n",
               identity, error);
        if (error < 0.005) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 12: sin(-x) = -sin(x) (odd function) */
    {
        double angle = 0.8;
        fp16_t pos = double_to_fp16(angle);
        fp16_t neg = double_to_fp16(-angle);
        double s_pos = fp16_to_double(fp16_sin(pos));
        double s_neg = fp16_to_double(fp16_sin(neg));
        double error = fabs(s_pos + s_neg);

        printf("Test 12: sin(-0.8) + sin(0.8) = %.6f (expected 0.0, error: %.6f)\n",
               s_pos + s_neg, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* ------------------------------------------------------------------
     * fp16_atan2 tests
     * ------------------------------------------------------------------ */
    printf("--- fp16_atan2 (CORDIC vectoring, x > 0) ---\n\n");

    /* Test 13: atan2(0, 1) = 0 */
    {
        fp16_t result = fp16_atan2(0, FP16_ONE_VALUE);
        double result_d = fp16_to_double(result);
        double expected = 0.0;
        double error = fabs(result_d - expected);

        printf("Test 13: atan2(0, 1) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 14: atan2(1, 1) = pi/4 */
    {
        fp16_t result = fp16_atan2(FP16_ONE_VALUE, FP16_ONE_VALUE);
        double result_d = fp16_to_double(result);
        double expected = PI_APPROX / 4.0;
        double error = fabs(result_d - expected);

        printf("Test 14: atan2(1, 1) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 15: atan2(-1, 1) = -pi/4 */
    {
        fp16_t result = fp16_atan2(-FP16_ONE_VALUE, FP16_ONE_VALUE);
        double result_d = fp16_to_double(result);
        double expected = -PI_APPROX / 4.0;
        double error = fabs(result_d - expected);

        printf("Test 15: atan2(-1, 1) = %.6f (expected %.6f, error: %.6f)\n",
               result_d, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 16: atan2(0, 0) with x==0 edge case -> 0 */
    {
        fp16_t result = fp16_atan2(0, 0);
        double result_d = fp16_to_double(result);

        printf("Test 16: atan2(0, 0) = %.6f (expected 0 for undefined case)\n",
               result_d);
        if (result == 0) { printf("PASS\n\n"); passed++; }
        else             { printf("FAIL\n\n"); failed++; }
    }

    /* ------------------------------------------------------------------
     * fp16_float_sin / fp16_float_cos wrappers
     * ------------------------------------------------------------------ */
    printf("--- fp16_float_sin / fp16_float_cos (range-extended) ---\n\n");

    /* Test 17: sin(pi) = 0 (outside core domain) */
    {
        float result = fp16_float_sin((float)PI_APPROX);
        double expected = 0.0;
        double error = fabs((double)result - expected);

        printf("Test 17: fp16_float_sin(pi) = %.6f (expected %.6f, error: %.6f)\n",
               result, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 18: cos(pi) = -1 (outside core domain) */
    {
        float result = fp16_float_cos((float)PI_APPROX);
        double expected = -1.0;
        double error = fabs((double)result - expected);

        printf("Test 18: fp16_float_cos(pi) = %.6f (expected %.6f, error: %.6f)\n",
               result, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 19: sin(3*pi/4) = sqrt(2)/2 */
    {
        float result = fp16_float_sin((float)(3.0 * PI_APPROX / 4.0));
        double expected = sqrt(2.0) / 2.0;
        double error = fabs((double)result - expected);

        printf("Test 19: fp16_float_sin(3*pi/4) = %.6f (expected %.6f, error: %.6f)\n",
               result, expected, error);
        if (error < 0.003) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 20: cos(-pi/2) = 0 */
    {
        float result = fp16_float_cos(-(float)HALF_PI_APPROX);
        double expected = 0.0;
        double error = fabs((double)result - expected);

        printf("Test 20: fp16_float_cos(-pi/2) = %.6f (expected %.6f, error: %.6f)\n",
               result, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 21: periodicity — sin(2*pi + pi/4) = sin(pi/4) */
    {
        float r1 = fp16_float_sin((float)(PI_APPROX / 4.0));
        float r2 = fp16_float_sin((float)(2.0 * PI_APPROX + PI_APPROX / 4.0));
        double error = fabs((double)(r1 - r2));

        printf("Test 21: sin(pi/4) = %.6f, sin(2*pi + pi/4) = %.6f (error: %.6f)\n",
               r1, r2, error);
        if (error < 0.003) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* ------------------------------------------------------------------
     * fp16_float_atan2 wrapper
     * ------------------------------------------------------------------ */
    printf("--- fp16_float_atan2 (full four-quadrant) ---\n\n");

    /* Test 22: Q2: atan2(1, -1) = 3*pi/4 */
    {
        float result = fp16_float_atan2(1.0f, -1.0f);
        double expected = 3.0 * PI_APPROX / 4.0;
        double error = fabs((double)result - expected);

        printf("Test 22: fp16_float_atan2(1, -1) = %.6f (expected %.6f, error: %.6f)\n",
               result, expected, error);
        if (error < 0.003) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 23: Q3: atan2(-1, -1) = -3*pi/4 */
    {
        float result = fp16_float_atan2(-1.0f, -1.0f);
        double expected = -3.0 * PI_APPROX / 4.0;
        double error = fabs((double)result - expected);

        printf("Test 23: fp16_float_atan2(-1, -1) = %.6f (expected %.6f, error: %.6f)\n",
               result, expected, error);
        if (error < 0.003) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 24: atan2 consistency: atan2(y, x) == atan(y/x) for x > 0 */
    {
        float y = 0.6f, x = 0.8f;
        float result = fp16_float_atan2(y, x);
        double expected = atan2((double)y, (double)x);
        double error = fabs((double)result - expected);

        printf("Test 24: fp16_float_atan2(0.6, 0.8) = %.6f (expected %.6f, error: %.6f)\n",
               result, expected, error);
        if (error < 0.003) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* ------------------------------------------------------------------
     * fp16_double_sin / fp16_double_cos wrappers
     * ------------------------------------------------------------------ */
    printf("--- fp16_double_sin / fp16_double_cos (double precision) ---\n\n");

    /* Test 25: double sin(pi) = 0 */
    {
        double result = fp16_double_sin(PI_APPROX);
        double expected = 0.0;
        double error = fabs(result - expected);

        printf("Test 25: fp16_double_sin(pi) = %.6f (expected %.6f, error: %.6f)\n",
               result, expected, error);
        if (error < 0.002) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 26: double cos(2*pi) = 1 */
    {
        double result = fp16_double_cos(2.0 * PI_APPROX);
        double expected = 1.0;
        double error = fabs(result - expected);

        printf("Test 26: fp16_double_cos(2*pi) = %.6f (expected %.6f, error: %.6f)\n",
               result, expected, error);
        if (error < 0.003) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    /* Test 27: fp16_double_atan2(1, -1) = 3*pi/4 */
    {
        double result = fp16_double_atan2(1.0, -1.0);
        double expected = 3.0 * PI_APPROX / 4.0;
        double error = fabs(result - expected);

        printf("Test 27: fp16_double_atan2(1, -1) = %.6f (expected %.6f, error: %.6f)\n",
               result, expected, error);
        if (error < 0.003) { printf("PASS\n\n"); passed++; }
        else               { printf("FAIL (error too large)\n\n"); failed++; }
    }

    printf("\n========== Test Summary ==========\n");
    printf("Passed: %d / 27\n", passed);
    printf("Failed: %d / 27\n", failed);

    /* ============ PERFORMANCE BENCHMARKS ============ */
    printf("\n========== Performance Benchmarks ==========\n");
    printf("Running %d iterations of each CORDIC function across %d test values...\n\n",
           BENCHMARK_ITERATIONS, NUM_TEST_VALUES);

    double test_angles[NUM_TEST_VALUES] = {
        0.0, 0.1, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2,
        -0.1, -0.4, -0.8, -1.2
    };

    fp16_t fp16_angles[NUM_TEST_VALUES];
    for (int i = 0; i < NUM_TEST_VALUES; i++)
        fp16_angles[i] = double_to_fp16(test_angles[i]);

    /* Warmup */
    for (int iter = 0; iter < 1000; iter++)
        for (int i = 0; i < NUM_TEST_VALUES; i++)
        {
            fp16_sin(fp16_angles[i]);
            fp16_cos(fp16_angles[i]);
        }

    /* Benchmark fp16_sin */
    clock_t start = clock();
    for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        for (int i = 0; i < NUM_TEST_VALUES; i++)
            fp16_sin(fp16_angles[i]);
    clock_t end = clock();

    double total_calls = (double)BENCHMARK_ITERATIONS * NUM_TEST_VALUES;
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("fp16_sin  throughput: %.0f calls/sec  latency: %.2f ns\n",
           total_calls / elapsed, elapsed * 1e9 / total_calls);

    /* Benchmark fp16_cos */
    start = clock();
    for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        for (int i = 0; i < NUM_TEST_VALUES; i++)
            fp16_cos(fp16_angles[i]);
    end = clock();

    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("fp16_cos  throughput: %.0f calls/sec  latency: %.2f ns\n",
           total_calls / elapsed, elapsed * 1e9 / total_calls);

    /* Benchmark fp16_atan2 (x > 0 pairs) */
    fp16_t fp16_xs[NUM_TEST_VALUES], fp16_ys[NUM_TEST_VALUES];
    for (int i = 0; i < NUM_TEST_VALUES; i++)
    {
        fp16_xs[i] = double_to_fp16(0.8);
        fp16_ys[i] = fp16_angles[i];
    }
    start = clock();
    for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
        for (int i = 0; i < NUM_TEST_VALUES; i++)
            fp16_atan2(fp16_ys[i], fp16_xs[i]);
    end = clock();

    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("fp16_atan2 throughput: %.0f calls/sec  latency: %.2f ns\n",
           total_calls / elapsed, elapsed * 1e9 / total_calls);

    printf("\n========== Per-value accuracy (fp16_sin / fp16_cos) ==========\n");
    printf("Angle (rad) |   sin_fp16  |  sin_ref   |  cos_fp16  |  cos_ref\n");
    printf("------------|-------------|------------|------------|----------\n");

    for (int i = 0; i < NUM_TEST_VALUES; i++)
    {
        double angle = test_angles[i];
        double s = fp16_to_double(fp16_sin(fp16_angles[i]));
        double c = fp16_to_double(fp16_cos(fp16_angles[i]));
        printf("  %8.4f  |  %9.6f  | %9.6f  | %9.6f  | %9.6f\n",
               angle, s, sin(angle), c, cos(angle));
    }

    printf("\n========== Benchmark Complete ==========\n");

    return failed > 0 ? 1 : 0;
}
