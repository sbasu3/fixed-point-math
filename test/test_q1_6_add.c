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

int main(void)
{
    printf("Q1_6_add unit tests\n");
    printf("====================\n\n");

    Q1_6_t a, b, r;

    /* Case 1: 0.50 + 0.25 = 0.75 */
    a.sign = 0;
    a.integer = 0;
    a.fractional = 32; /* 0.50 */
    b.sign = 0;
    b.integer = 0;
    b.fractional = 16; /* 0.25 */
    r = Q1_6_add(a, b);
    print_q1_6("  0.50 + 0.25 =>", r);
    if (!(r.sign == 0 && r.integer == 0 && r.fractional == 48))
    {
        printf("FAIL: expected (0,0,48)\n");
        return 1;
    }

    /* Case 2: 1.00 + 0.50 => clamp integer to 1 */
    a.sign = 0;
    a.integer = 1;
    a.fractional = 0; /* 1.00 */
    b.sign = 0;
    b.integer = 0;
    b.fractional = 32; /* 0.50 */
    r = Q1_6_add(a, b);
    print_q1_6("  1.00 + 0.50 =>", r);
    if (!(r.sign == 0 && r.integer == 1))
    {
        printf("FAIL: expected integer clamped to 1\n");
        return 1;
    }

    /* Case 3: -0.75 + 0.50 = -0.25 */
    a.sign = 1;
    a.integer = 0;
    a.fractional = 48; /* -0.75 */
    b.sign = 0;
    b.integer = 0;
    b.fractional = 32; /* 0.50 */
    r = Q1_6_add(a, b);
    print_q1_6("  -0.75 + 0.50 =>", r);
    if (!(r.sign == 1 && r.integer == 0 && r.fractional == 16))
    {
        printf("FAIL: expected (1,0,16)\n");
        return 1;
    }

    /* Case 4: -0.25 + -0.50 = -0.75 */
    a.sign = 1;
    a.integer = 0;
    a.fractional = 16; /* -0.25 */
    b.sign = 1;
    b.integer = 0;
    b.fractional = 32; /* -0.50 */
    r = Q1_6_add(a, b);
    print_q1_6("  -0.25 + -0.50 =>", r);
    if (!(r.sign == 1 && r.integer == 0 && r.fractional == 48))
    {
        printf("FAIL: expected (1,0,48)\n");
        return 1;
    }

    printf("\nAll Q1_6_add tests passed.\n");

    /* ------------------------------------------------------ */
    /* DOUBLE_Q1_6_add tests */
    /* ------------------------------------------------------ */
    printf("\nDOUBLE_Q1_6_add unit tests\n");
    printf("==========================\n\n");

    DOUBLE_Q1_6_t da, db, dr;

    /* Case 1: 0.50 + 0.25 = 0.75 (fractional: 2048 + 1024 = 3072) */
    da.sign = 0;
    da.integer = 0;
    da.fractional = 2048;
    db.sign = 0;
    db.integer = 0;
    db.fractional = 1024;
    dr = DOUBLE_Q1_6_add(da, db);
    print_double_q1_6("  0.50 + 0.25 =>", dr);
    if (!(dr.sign == 0 && dr.integer == 0 && dr.fractional == 3072))
    {
        printf("FAIL: expected (0,0,3072)\n");
        return 1;
    }

    /* Case 2: 1.00 + 0.75 => clamp integer to 1, fractional 3072 */
    da.sign = 0;
    da.integer = 1;
    da.fractional = 0; /* 1.00 */
    db.sign = 0;
    db.integer = 0;
    db.fractional = 3072; /* 0.75 */
    dr = DOUBLE_Q1_6_add(da, db);
    print_double_q1_6("  1.00 + 0.75 =>", dr);
    if (!(dr.sign == 0 && dr.integer == 1))
    {
        printf("FAIL: expected integer clamped to 1\n");
        return 1;
    }

    /* Case 3: -0.75 + 0.50 = -0.25 */
    da.sign = 1;
    da.integer = 0;
    da.fractional = 3072; /* -0.75 */
    db.sign = 0;
    db.integer = 0;
    db.fractional = 2048; /* 0.50 */
    dr = DOUBLE_Q1_6_add(da, db);
    print_double_q1_6("  -0.75 + 0.50 =>", dr);
    if (!(dr.sign == 1 && dr.integer == 0 && dr.fractional == 1024))
    {
        printf("FAIL: expected (1,0,1024)\n");
        return 1;
    }

    /* Case 4: -0.25 + -0.50 = -0.75 */
    da.sign = 1;
    da.integer = 0;
    da.fractional = 1024; /* -0.25 */
    db.sign = 1;
    db.integer = 0;
    db.fractional = 2048; /* -0.50 */
    dr = DOUBLE_Q1_6_add(da, db);
    print_double_q1_6("  -0.25 + -0.50 =>", dr);
    if (!(dr.sign == 1 && dr.integer == 0 && dr.fractional == 3072))
    {
        printf("FAIL: expected (1,0,3072)\n");
        return 1;
    }

    printf("\nAll DOUBLE_Q1_6_add tests passed.\n");
    return 0;
}
