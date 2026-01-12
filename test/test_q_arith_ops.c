#include <stdio.h>
#include <stdbool.h>
#include "defines.h"
#include "utilities.h"

static void print_q1_6(const char *label, Q1_6_t v)
{
    printf("%s sign=%u int=%u frac=%u\n", label,
           (unsigned)v.sign, (unsigned)v.integer, (unsigned)v.fractional);
}

static void print_double_q1_6(const char *label, DOUBLE_Q1_6_t v)
{
    printf("%s sign=%u int=%u frac=%u\n", label,
           (unsigned)v.sign, (unsigned)v.integer, (unsigned)v.fractional);
}

static void print_q1_14(const char *label, Q1_14_t v)
{
    printf("%s sign=%u int=%u frac=%u\n", label,
           (unsigned)v.sign, (unsigned)v.integer, (unsigned)v.fractional);
}

static void print_double_q1_14(const char *label, DOUBLE_Q1_14_t v)
{
    printf("%s sign=%u int=%u frac=%u\n", label,
           (unsigned)v.sign, (unsigned)v.integer, (unsigned)v.fractional);
}

static void print_q1_30(const char *label, Q1_30_t v)
{
    printf("%s sign=%u int=%u frac=%u\n", label,
           (unsigned)v.sign, (unsigned)v.integer, (unsigned)v.fractional);
}

static void print_double_q1_30(const char *label, DOUBLE_Q1_30_t v)
{
    printf("%s sign=%u int=%u frac=%llu\n", label,
           (unsigned)v.sign, (unsigned)v.integer, (unsigned long long)v.fractional);
}

int main(void)
{
    /* ---------------- Q1.6 ---------------- */
    printf("Q1_6 arithmetic tests\n");
    printf("=====================\n\n");
    Q1_6_t a6, b6, r6;

    /* Subtraction: 0.75 - 0.25 = 0.50 */
    a6 = (Q1_6_t){0, 0, 48};
    b6 = (Q1_6_t){0, 0, 16};
    r6 = Q1_6_sub(a6, b6);
    print_q1_6("  0.75 - 0.25 =>", r6);
    if (!(r6.sign == 0 && r6.integer == 0 && r6.fractional == 32))
    {
        printf("FAIL Q1_6_sub case1\n");
        return 1;
    }

    /* Subtraction: -0.50 - 0.25 = -0.75 */
    a6 = (Q1_6_t){1, 0, 32};
    b6 = (Q1_6_t){0, 0, 16};
    r6 = Q1_6_sub(a6, b6);
    print_q1_6("  -0.50 - 0.25 =>", r6);
    if (!(r6.sign == 1 && r6.integer == 0 && r6.fractional == 48))
    {
        printf("FAIL Q1_6_sub case2\n");
        return 1;
    }

    /* Multiplication: 0.50 * 0.50 = 0.25 */
    a6 = (Q1_6_t){0, 0, 32};
    b6 = (Q1_6_t){0, 0, 32};
    r6 = Q1_6_mul(a6, b6);
    print_q1_6("  0.50 * 0.50 =>", r6);
    if (!(r6.sign == 0 && r6.integer == 0 && r6.fractional == 16))
    {
        printf("FAIL Q1_6_mul case1\n");
        return 1;
    }

    /* Multiplication: -0.75 * 0.50 = -0.375 */
    a6 = (Q1_6_t){1, 0, 48};
    b6 = (Q1_6_t){0, 0, 32};
    r6 = Q1_6_mul(a6, b6);
    print_q1_6("  -0.75 * 0.50 =>", r6);
    if (!(r6.sign == 1 && r6.integer == 0 && r6.fractional == 24))
    {
        printf("FAIL Q1_6_mul case2\n");
        return 1;
    }

    /* Division: 0.75 / 0.50 = 1.50 */
    a6 = (Q1_6_t){0, 0, 48};
    b6 = (Q1_6_t){0, 0, 32};
    r6 = Q1_6_div(a6, b6);
    print_q1_6("  0.75 / 0.50 =>", r6);
    if (!(r6.sign == 0 && r6.integer == 1 && r6.fractional == 32))
    {
        printf("FAIL Q1_6_div case1\n");
        return 1;
    }

    /* Division: -0.50 / 0.50 = -1.00 */
    a6 = (Q1_6_t){1, 0, 32};
    b6 = (Q1_6_t){0, 0, 32};
    r6 = Q1_6_div(a6, b6);
    print_q1_6("  -0.50 / 0.50 =>", r6);
    if (!(r6.sign == 1 && r6.integer == 1 && r6.fractional == 0))
    {
        printf("FAIL Q1_6_div case2\n");
        return 1;
    }

    printf("\nQ1_6 arithmetic passed.\n\n");

    /* ---------------- DOUBLE Q1.6 ---------------- */
    printf("DOUBLE_Q1_6 arithmetic tests\n");
    printf("============================\n\n");
    DOUBLE_Q1_6_t da6, db6, dr6;

    da6 = (DOUBLE_Q1_6_t){0, 0, 3072}; /* 0.75 */
    db6 = (DOUBLE_Q1_6_t){0, 0, 1024}; /* 0.25 */
    dr6 = DOUBLE_Q1_6_sub(da6, db6);
    print_double_q1_6("  0.75 - 0.25 =>", dr6);
    if (!(dr6.sign == 0 && dr6.integer == 0 && dr6.fractional == 2048))
    {
        printf("FAIL DOUBLE_Q1_6_sub case1\n");
        return 1;
    }

    da6 = (DOUBLE_Q1_6_t){1, 0, 2048}; /* -0.50 */
    db6 = (DOUBLE_Q1_6_t){0, 0, 1024}; /* 0.25 */
    dr6 = DOUBLE_Q1_6_sub(da6, db6);
    print_double_q1_6("  -0.50 - 0.25 =>", dr6);
    if (!(dr6.sign == 1 && dr6.integer == 0 && dr6.fractional == 3072))
    {
        printf("FAIL DOUBLE_Q1_6_sub case2\n");
        return 1;
    }

    da6 = (DOUBLE_Q1_6_t){0, 0, 2048}; /* 0.50 */
    db6 = (DOUBLE_Q1_6_t){0, 0, 2048}; /* 0.50 */
    dr6 = DOUBLE_Q1_6_mul(da6, db6);
    print_double_q1_6("  0.50 * 0.50 =>", dr6);
    if (!(dr6.sign == 0 && dr6.integer == 0 && dr6.fractional == 1024))
    {
        printf("FAIL DOUBLE_Q1_6_mul case1\n");
        return 1;
    }

    da6 = (DOUBLE_Q1_6_t){1, 0, 3072}; /* -0.75 */
    db6 = (DOUBLE_Q1_6_t){0, 0, 2048}; /* 0.50 */
    dr6 = DOUBLE_Q1_6_mul(da6, db6);
    print_double_q1_6("  -0.75 * 0.50 =>", dr6);
    if (!(dr6.sign == 1 && dr6.integer == 0 && dr6.fractional == 1536))
    {
        printf("FAIL DOUBLE_Q1_6_mul case2\n");
        return 1;
    }

    da6 = (DOUBLE_Q1_6_t){0, 0, 3072}; /* 0.75 */
    db6 = (DOUBLE_Q1_6_t){0, 0, 2048}; /* 0.50 */
    dr6 = DOUBLE_Q1_6_div(da6, db6);
    print_double_q1_6("  0.75 / 0.50 =>", dr6);
    if (!(dr6.sign == 0 && dr6.integer == 1 && dr6.fractional == 2048))
    {
        printf("FAIL DOUBLE_Q1_6_div case1\n");
        return 1;
    }

    da6 = (DOUBLE_Q1_6_t){1, 0, 2048}; /* -0.50 */
    db6 = (DOUBLE_Q1_6_t){0, 0, 2048}; /* 0.50 */
    dr6 = DOUBLE_Q1_6_div(da6, db6);
    print_double_q1_6("  -0.50 / 0.50 =>", dr6);
    if (!(dr6.sign == 1 && dr6.integer == 1 && dr6.fractional == 0))
    {
        printf("FAIL DOUBLE_Q1_6_div case2\n");
        return 1;
    }

    printf("\nDOUBLE_Q1_6 arithmetic passed.\n\n");

    /* ---------------- Q1.14 ---------------- */
    printf("Q1_14 arithmetic tests\n");
    printf("======================\n\n");
    Q1_14_t a14, b14, r14;

    a14 = (Q1_14_t){0, 0, 12288}; /* 0.75 */
    b14 = (Q1_14_t){0, 0, 4096};  /* 0.25 */
    r14 = Q1_14_sub(a14, b14);
    print_q1_14("  0.75 - 0.25 =>", r14);
    if (!(r14.sign == 0 && r14.integer == 0 && r14.fractional == 8192))
    {
        printf("FAIL Q1_14_sub case1\n");
        return 1;
    }

    a14 = (Q1_14_t){1, 0, 8192}; /* -0.50 */
    b14 = (Q1_14_t){0, 0, 4096}; /* 0.25 */
    r14 = Q1_14_sub(a14, b14);
    print_q1_14("  -0.50 - 0.25 =>", r14);
    if (!(r14.sign == 1 && r14.integer == 0 && r14.fractional == 12288))
    {
        printf("FAIL Q1_14_sub case2\n");
        return 1;
    }

    a14 = (Q1_14_t){0, 0, 8192}; /* 0.50 */
    b14 = (Q1_14_t){0, 0, 8192}; /* 0.50 */
    r14 = Q1_14_mul(a14, b14);
    print_q1_14("  0.50 * 0.50 =>", r14);
    if (!(r14.sign == 0 && r14.integer == 0 && r14.fractional == 4096))
    {
        printf("FAIL Q1_14_mul case1\n");
        return 1;
    }

    a14 = (Q1_14_t){1, 0, 12288}; /* -0.75 */
    b14 = (Q1_14_t){0, 0, 8192};  /* 0.50 */
    r14 = Q1_14_mul(a14, b14);
    print_q1_14("  -0.75 * 0.50 =>", r14);
    if (!(r14.sign == 1 && r14.integer == 0 && r14.fractional == 6144))
    {
        printf("FAIL Q1_14_mul case2\n");
        return 1;
    }

    a14 = (Q1_14_t){0, 0, 12288}; /* 0.75 */
    b14 = (Q1_14_t){0, 0, 8192};  /* 0.50 */
    r14 = Q1_14_div(a14, b14);
    print_q1_14("  0.75 / 0.50 =>", r14);
    if (!(r14.sign == 0 && r14.integer == 1 && r14.fractional == 8192))
    {
        printf("FAIL Q1_14_div case1\n");
        return 1;
    }

    a14 = (Q1_14_t){1, 0, 8192}; /* -0.50 */
    b14 = (Q1_14_t){0, 0, 8192}; /* 0.50 */
    r14 = Q1_14_div(a14, b14);
    print_q1_14("  -0.50 / 0.50 =>", r14);
    if (!(r14.sign == 1 && r14.integer == 1 && r14.fractional == 0))
    {
        printf("FAIL Q1_14_div case2\n");
        return 1;
    }

    printf("\nQ1_14 arithmetic passed.\n\n");

    /* ---------------- DOUBLE Q1.14 ---------------- */
    printf("DOUBLE_Q1_14 arithmetic tests\n");
    printf("=============================\n\n");
    DOUBLE_Q1_14_t da14, db14, dr14;

    da14 = (DOUBLE_Q1_14_t){0, 0, 201326592}; /* 0.75 */
    db14 = (DOUBLE_Q1_14_t){0, 0, 67108864};  /* 0.25 */
    dr14 = DOUBLE_Q1_14_sub(da14, db14);
    print_double_q1_14("  0.75 - 0.25 =>", dr14);
    if (!(dr14.sign == 0 && dr14.integer == 0 && dr14.fractional == 134217728))
    {
        printf("FAIL DOUBLE_Q1_14_sub case1\n");
        return 1;
    }

    da14 = (DOUBLE_Q1_14_t){1, 0, 134217728}; /* -0.50 */
    db14 = (DOUBLE_Q1_14_t){0, 0, 67108864};  /* 0.25 */
    dr14 = DOUBLE_Q1_14_sub(da14, db14);
    print_double_q1_14("  -0.50 - 0.25 =>", dr14);
    if (!(dr14.sign == 1 && dr14.integer == 0 && dr14.fractional == 201326592))
    {
        printf("FAIL DOUBLE_Q1_14_sub case2\n");
        return 1;
    }

    da14 = (DOUBLE_Q1_14_t){0, 0, 134217728}; /* 0.50 */
    db14 = (DOUBLE_Q1_14_t){0, 0, 134217728}; /* 0.50 */
    dr14 = DOUBLE_Q1_14_mul(da14, db14);
    print_double_q1_14("  0.50 * 0.50 =>", dr14);
    if (!(dr14.sign == 0 && dr14.integer == 0 && dr14.fractional == 67108864))
    {
        printf("FAIL DOUBLE_Q1_14_mul case1\n");
        return 1;
    }

    da14 = (DOUBLE_Q1_14_t){1, 0, 201326592}; /* -0.75 */
    db14 = (DOUBLE_Q1_14_t){0, 0, 134217728}; /* 0.50 */
    dr14 = DOUBLE_Q1_14_mul(da14, db14);
    print_double_q1_14("  -0.75 * 0.50 =>", dr14);
    if (!(dr14.sign == 1 && dr14.integer == 0 && dr14.fractional == 100663296))
    {
        printf("FAIL DOUBLE_Q1_14_mul case2\n");
        return 1;
    }

    da14 = (DOUBLE_Q1_14_t){0, 0, 201326592}; /* 0.75 */
    db14 = (DOUBLE_Q1_14_t){0, 0, 134217728}; /* 0.50 */
    dr14 = DOUBLE_Q1_14_div(da14, db14);
    print_double_q1_14("  0.75 / 0.50 =>", dr14);
    if (!(dr14.sign == 0 && dr14.integer == 1 && dr14.fractional == 134217728))
    {
        printf("FAIL DOUBLE_Q1_14_div case1\n");
        return 1;
    }

    da14 = (DOUBLE_Q1_14_t){1, 0, 134217728}; /* -0.50 */
    db14 = (DOUBLE_Q1_14_t){0, 0, 134217728}; /* 0.50 */
    dr14 = DOUBLE_Q1_14_div(da14, db14);
    print_double_q1_14("  -0.50 / 0.50 =>", dr14);
    if (!(dr14.sign == 1 && dr14.integer == 1 && dr14.fractional == 0))
    {
        printf("FAIL DOUBLE_Q1_14_div case2\n");
        return 1;
    }

    printf("\nDOUBLE_Q1_14 arithmetic passed.\n\n");

    /* ---------------- Q1.30 ---------------- */
    printf("Q1_30 arithmetic tests\n");
    printf("======================\n\n");
    Q1_30_t a30, b30, r30;

    a30 = (Q1_30_t){0, 0, 805306368}; /* 0.75 */
    b30 = (Q1_30_t){0, 0, 268435456}; /* 0.25 */
    r30 = Q1_30_sub(a30, b30);
    print_q1_30("  0.75 - 0.25 =>", r30);
    if (!(r30.sign == 0 && r30.integer == 0 && r30.fractional == 536870912))
    {
        printf("FAIL Q1_30_sub case1\n");
        return 1;
    }

    a30 = (Q1_30_t){1, 0, 536870912}; /* -0.50 */
    b30 = (Q1_30_t){0, 0, 268435456}; /* 0.25 */
    r30 = Q1_30_sub(a30, b30);
    print_q1_30("  -0.50 - 0.25 =>", r30);
    if (!(r30.sign == 1 && r30.integer == 0 && r30.fractional == 805306368))
    {
        printf("FAIL Q1_30_sub case2\n");
        return 1;
    }

    a30 = (Q1_30_t){0, 0, 536870912}; /* 0.50 */
    b30 = (Q1_30_t){0, 0, 536870912}; /* 0.50 */
    r30 = Q1_30_mul(a30, b30);
    print_q1_30("  0.50 * 0.50 =>", r30);
    if (!(r30.sign == 0 && r30.integer == 0 && r30.fractional == 268435456))
    {
        printf("FAIL Q1_30_mul case1\n");
        return 1;
    }

    a30 = (Q1_30_t){1, 0, 805306368}; /* -0.75 */
    b30 = (Q1_30_t){0, 0, 536870912}; /* 0.50 */
    r30 = Q1_30_mul(a30, b30);
    print_q1_30("  -0.75 * 0.50 =>", r30);
    if (!(r30.sign == 1 && r30.integer == 0 && r30.fractional == 402653184))
    {
        printf("FAIL Q1_30_mul case2\n");
        return 1;
    }

    a30 = (Q1_30_t){0, 0, 805306368}; /* 0.75 */
    b30 = (Q1_30_t){0, 0, 536870912}; /* 0.50 */
    r30 = Q1_30_div(a30, b30);
    print_q1_30("  0.75 / 0.50 =>", r30);
    if (!(r30.sign == 0 && r30.integer == 1 && r30.fractional == 536870912))
    {
        printf("FAIL Q1_30_div case1\n");
        return 1;
    }

    a30 = (Q1_30_t){1, 0, 536870912}; /* -0.50 */
    b30 = (Q1_30_t){0, 0, 536870912}; /* 0.50 */
    r30 = Q1_30_div(a30, b30);
    print_q1_30("  -0.50 / 0.50 =>", r30);
    if (!(r30.sign == 1 && r30.integer == 1 && r30.fractional == 0))
    {
        printf("FAIL Q1_30_div case2\n");
        return 1;
    }

    printf("\nQ1_30 arithmetic passed.\n\n");

    /* ---------------- DOUBLE Q1.30 ---------------- */
    printf("DOUBLE_Q1_30 arithmetic tests\n");
    printf("=============================\n\n");
    DOUBLE_Q1_30_t da30, db30, dr30;

    da30 = (DOUBLE_Q1_30_t){0, 0, 864691128455135232ULL}; /* 0.75 */
    db30 = (DOUBLE_Q1_30_t){0, 0, 288230376151711744ULL}; /* 0.25 */
    dr30 = DOUBLE_Q1_30_sub(da30, db30);
    print_double_q1_30("  0.75 - 0.25 =>", dr30);
    if (!(dr30.sign == 0 && dr30.integer == 0 && dr30.fractional == 576460752303423488ULL))
    {
        printf("FAIL DOUBLE_Q1_30_sub case1\n");
        return 1;
    }

    da30 = (DOUBLE_Q1_30_t){1, 0, 576460752303423488ULL}; /* -0.50 */
    db30 = (DOUBLE_Q1_30_t){0, 0, 288230376151711744ULL}; /* 0.25 */
    dr30 = DOUBLE_Q1_30_sub(da30, db30);
    print_double_q1_30("  -0.50 - 0.25 =>", dr30);
    if (!(dr30.sign == 1 && dr30.integer == 0 && dr30.fractional == 864691128455135232ULL))
    {
        printf("FAIL DOUBLE_Q1_30_sub case2\n");
        return 1;
    }

    da30 = (DOUBLE_Q1_30_t){0, 0, 576460752303423488ULL}; /* 0.50 */
    db30 = (DOUBLE_Q1_30_t){0, 0, 576460752303423488ULL}; /* 0.50 */
    dr30 = DOUBLE_Q1_30_mul(da30, db30);
    print_double_q1_30("  0.50 * 0.50 =>", dr30);
    if (!(dr30.sign == 0 && dr30.integer == 0 && dr30.fractional == 288230376151711744ULL))
    {
        printf("FAIL DOUBLE_Q1_30_mul case1\n");
        return 1;
    }

    da30 = (DOUBLE_Q1_30_t){1, 0, 864691128455135232ULL}; /* -0.75 */
    db30 = (DOUBLE_Q1_30_t){0, 0, 576460752303423488ULL}; /* 0.50 */
    dr30 = DOUBLE_Q1_30_mul(da30, db30);
    print_double_q1_30("  -0.75 * 0.50 =>", dr30);
    if (!(dr30.sign == 1 && dr30.integer == 0 && dr30.fractional == 432345564227567616ULL))
    {
        printf("FAIL DOUBLE_Q1_30_mul case2\n");
        return 1;
    }

    da30 = (DOUBLE_Q1_30_t){0, 0, 864691128455135232ULL}; /* 0.75 */
    db30 = (DOUBLE_Q1_30_t){0, 0, 576460752303423488ULL}; /* 0.50 */
    dr30 = DOUBLE_Q1_30_div(da30, db30);
    print_double_q1_30("  0.75 / 0.50 =>", dr30);
    if (!(dr30.sign == 0 && dr30.integer == 1 && dr30.fractional == 576460752303423488ULL))
    {
        printf("FAIL DOUBLE_Q1_30_div case1\n");
        return 1;
    }

    da30 = (DOUBLE_Q1_30_t){1, 0, 576460752303423488ULL}; /* -0.50 */
    db30 = (DOUBLE_Q1_30_t){0, 0, 576460752303423488ULL}; /* 0.50 */
    dr30 = DOUBLE_Q1_30_div(da30, db30);
    print_double_q1_30("  -0.50 / 0.50 =>", dr30);
    if (!(dr30.sign == 1 && dr30.integer == 1 && dr30.fractional == 0ULL))
    {
        printf("FAIL DOUBLE_Q1_30_div case2\n");
        return 1;
    }

    printf("\nDOUBLE_Q1_30 arithmetic passed.\n");
    return 0;
}
