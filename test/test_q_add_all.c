#include <stdio.h>
#include <stdbool.h>
#include "defines.h"
#include "utilities.h"

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
    /* ------------------------------------------------------ */
    /* Q1_14_add tests */
    /* ------------------------------------------------------ */
    printf("Q1_14_add unit tests\n");
    printf("====================\n\n");

    Q1_14_t a14, b14, r14;

    /* Case 1: 0.50 + 0.25 = 0.75 */
    a14.sign = 0;
    a14.integer = 0;
    a14.fractional = 8192; /* 0.50 */
    b14.sign = 0;
    b14.integer = 0;
    b14.fractional = 4096; /* 0.25 */
    r14 = Q1_14_add(a14, b14);
    print_q1_14("  0.50 + 0.25 =>", r14);
    if (!(r14.sign == 0 && r14.integer == 0 && r14.fractional == 12288))
    {
        printf("FAIL: expected (0,0,12288)\n");
        return 1;
    }

    /* Case 2: 1.00 + 0.75 => clamp integer to 1 */
    a14.sign = 0;
    a14.integer = 1;
    a14.fractional = 0; /* 1.00 */
    b14.sign = 0;
    b14.integer = 0;
    b14.fractional = 12288; /* 0.75 */
    r14 = Q1_14_add(a14, b14);
    print_q1_14("  1.00 + 0.75 =>", r14);
    if (!(r14.sign == 0 && r14.integer == 1))
    {
        printf("FAIL: expected integer clamped to 1\n");
        return 1;
    }

    /* Case 3: -0.75 + 0.50 = -0.25 */
    a14.sign = 1;
    a14.integer = 0;
    a14.fractional = 12288; /* -0.75 */
    b14.sign = 0;
    b14.integer = 0;
    b14.fractional = 8192; /* 0.50 */
    r14 = Q1_14_add(a14, b14);
    print_q1_14("  -0.75 + 0.50 =>", r14);
    if (!(r14.sign == 1 && r14.integer == 0 && r14.fractional == 4096))
    {
        printf("FAIL: expected (1,0,4096)\n");
        return 1;
    }

    /* Case 4: -0.25 + -0.50 = -0.75 */
    a14.sign = 1;
    a14.integer = 0;
    a14.fractional = 4096; /* -0.25 */
    b14.sign = 1;
    b14.integer = 0;
    b14.fractional = 8192; /* -0.50 */
    r14 = Q1_14_add(a14, b14);
    print_q1_14("  -0.25 + -0.50 =>", r14);
    if (!(r14.sign == 1 && r14.integer == 0 && r14.fractional == 12288))
    {
        printf("FAIL: expected (1,0,12288)\n");
        return 1;
    }

    printf("\nAll Q1_14_add tests passed.\n\n");

    /* ------------------------------------------------------ */
    /* DOUBLE_Q1_14_add tests */
    /* ------------------------------------------------------ */
    printf("DOUBLE_Q1_14_add unit tests\n");
    printf("==========================\n\n");

    DOUBLE_Q1_14_t da14, db14, dr14;

    /* Case 1: 0.50 + 0.25 = 0.75 */
    da14.sign = 0;
    da14.integer = 0;
    da14.fractional = 134217728; /* 0.50 */
    db14.sign = 0;
    db14.integer = 0;
    db14.fractional = 67108864; /* 0.25 */
    dr14 = DOUBLE_Q1_14_add(da14, db14);
    print_double_q1_14("  0.50 + 0.25 =>", dr14);
    if (!(dr14.sign == 0 && dr14.integer == 0 && dr14.fractional == 201326592))
    {
        printf("FAIL: expected (0,0,201326592)\n");
        return 1;
    }

    /* Case 2: 1.00 + 0.75 => clamp integer to 1 */
    da14.sign = 0;
    da14.integer = 1;
    da14.fractional = 0; /* 1.00 */
    db14.sign = 0;
    db14.integer = 0;
    db14.fractional = 201326592; /* 0.75 */
    dr14 = DOUBLE_Q1_14_add(da14, db14);
    print_double_q1_14("  1.00 + 0.75 =>", dr14);
    if (!(dr14.sign == 0 && dr14.integer == 1))
    {
        printf("FAIL: expected integer clamped to 1\n");
        return 1;
    }

    /* Case 3: -0.75 + 0.50 = -0.25 */
    da14.sign = 1;
    da14.integer = 0;
    da14.fractional = 201326592; /* -0.75 */
    db14.sign = 0;
    db14.integer = 0;
    db14.fractional = 134217728; /* 0.50 */
    dr14 = DOUBLE_Q1_14_add(da14, db14);
    print_double_q1_14("  -0.75 + 0.50 =>", dr14);
    if (!(dr14.sign == 1 && dr14.integer == 0 && dr14.fractional == 67108864))
    {
        printf("FAIL: expected (1,0,67108864)\n");
        return 1;
    }

    /* Case 4: -0.25 + -0.50 = -0.75 */
    da14.sign = 1;
    da14.integer = 0;
    da14.fractional = 67108864; /* -0.25 */
    db14.sign = 1;
    db14.integer = 0;
    db14.fractional = 134217728; /* -0.50 */
    dr14 = DOUBLE_Q1_14_add(da14, db14);
    print_double_q1_14("  -0.25 + -0.50 =>", dr14);
    if (!(dr14.sign == 1 && dr14.integer == 0 && dr14.fractional == 201326592))
    {
        printf("FAIL: expected (1,0,201326592)\n");
        return 1;
    }

    printf("\nAll DOUBLE_Q1_14_add tests passed.\n\n");

    /* ------------------------------------------------------ */
    /* Q1_30_add tests */
    /* ------------------------------------------------------ */
    printf("Q1_30_add unit tests\n");
    printf("====================\n\n");

    Q1_30_t a30, b30, r30;

    /* Case 1: 0.50 + 0.25 = 0.75 */
    a30.sign = 0;
    a30.integer = 0;
    a30.fractional = 536870912; /* 0.50 */
    b30.sign = 0;
    b30.integer = 0;
    b30.fractional = 268435456; /* 0.25 */
    r30 = Q1_30_add(a30, b30);
    print_q1_30("  0.50 + 0.25 =>", r30);
    if (!(r30.sign == 0 && r30.integer == 0 && r30.fractional == 805306368))
    {
        printf("FAIL: expected (0,0,805306368)\n");
        return 1;
    }

    /* Case 2: 1.00 + 0.75 => clamp integer to 1 */
    a30.sign = 0;
    a30.integer = 1;
    a30.fractional = 0; /* 1.00 */
    b30.sign = 0;
    b30.integer = 0;
    b30.fractional = 805306368; /* 0.75 */
    r30 = Q1_30_add(a30, b30);
    print_q1_30("  1.00 + 0.75 =>", r30);
    if (!(r30.sign == 0 && r30.integer == 1))
    {
        printf("FAIL: expected integer clamped to 1\n");
        return 1;
    }

    /* Case 3: -0.75 + 0.50 = -0.25 */
    a30.sign = 1;
    a30.integer = 0;
    a30.fractional = 805306368; /* -0.75 */
    b30.sign = 0;
    b30.integer = 0;
    b30.fractional = 536870912; /* 0.50 */
    r30 = Q1_30_add(a30, b30);
    print_q1_30("  -0.75 + 0.50 =>", r30);
    if (!(r30.sign == 1 && r30.integer == 0 && r30.fractional == 268435456))
    {
        printf("FAIL: expected (1,0,268435456)\n");
        return 1;
    }

    /* Case 4: -0.25 + -0.50 = -0.75 */
    a30.sign = 1;
    a30.integer = 0;
    a30.fractional = 268435456; /* -0.25 */
    b30.sign = 1;
    b30.integer = 0;
    b30.fractional = 536870912; /* -0.50 */
    r30 = Q1_30_add(a30, b30);
    print_q1_30("  -0.25 + -0.50 =>", r30);
    if (!(r30.sign == 1 && r30.integer == 0 && r30.fractional == 805306368))
    {
        printf("FAIL: expected (1,0,805306368)\n");
        return 1;
    }

    printf("\nAll Q1_30_add tests passed.\n\n");

    /* ------------------------------------------------------ */
    /* DOUBLE_Q1_30_add tests */
    /* ------------------------------------------------------ */
    printf("DOUBLE_Q1_30_add unit tests\n");
    printf("==========================\n\n");

    DOUBLE_Q1_30_t da30, db30, dr30;

    /* Case 1: 0.50 + 0.25 = 0.75 */
    da30.sign = 0;
    da30.integer = 0;
    da30.fractional = 576460752303423488ULL; /* 0.50 */
    db30.sign = 0;
    db30.integer = 0;
    db30.fractional = 288230376151711744ULL; /* 0.25 */
    dr30 = DOUBLE_Q1_30_add(da30, db30);
    print_double_q1_30("  0.50 + 0.25 =>", dr30);
    if (!(dr30.sign == 0 && dr30.integer == 0 && dr30.fractional == 864691128455135232ULL))
    {
        printf("FAIL: expected (0,0,864691128455135232)\n");
        return 1;
    }

    /* Case 2: 1.00 + 0.75 => clamp integer to 1 */
    da30.sign = 0;
    da30.integer = 1;
    da30.fractional = 0ULL; /* 1.00 */
    db30.sign = 0;
    db30.integer = 0;
    db30.fractional = 864691128455135232ULL; /* 0.75 */
    dr30 = DOUBLE_Q1_30_add(da30, db30);
    print_double_q1_30("  1.00 + 0.75 =>", dr30);
    if (!(dr30.sign == 0 && dr30.integer == 1))
    {
        printf("FAIL: expected integer clamped to 1\n");
        return 1;
    }

    /* Case 3: -0.75 + 0.50 = -0.25 */
    da30.sign = 1;
    da30.integer = 0;
    da30.fractional = 864691128455135232ULL; /* -0.75 */
    db30.sign = 0;
    db30.integer = 0;
    db30.fractional = 576460752303423488ULL; /* 0.50 */
    dr30 = DOUBLE_Q1_30_add(da30, db30);
    print_double_q1_30("  -0.75 + 0.50 =>", dr30);
    if (!(dr30.sign == 1 && dr30.integer == 0 && dr30.fractional == 288230376151711744ULL))
    {
        printf("FAIL: expected (1,0,288230376151711744)\n");
        return 1;
    }

    /* Case 4: -0.25 + -0.50 = -0.75 */
    da30.sign = 1;
    da30.integer = 0;
    da30.fractional = 288230376151711744ULL; /* -0.25 */
    db30.sign = 1;
    db30.integer = 0;
    db30.fractional = 576460752303423488ULL; /* -0.50 */
    dr30 = DOUBLE_Q1_30_add(da30, db30);
    print_double_q1_30("  -0.25 + -0.50 =>", dr30);
    if (!(dr30.sign == 1 && dr30.integer == 0 && dr30.fractional == 864691128455135232ULL))
    {
        printf("FAIL: expected (1,0,864691128455135232)\n");
        return 1;
    }

    printf("\nAll DOUBLE_Q1_30_add tests passed.\n");
    return 0;
}
