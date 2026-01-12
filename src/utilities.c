#include "utilities.h"
/* ========================================================================
 * Generic Fixed-Point Utility Functions Implementation
 * ======================================================================== */

static inline int64_t q1_6_to_raw(Q1_6_t v)
{
    int16_t mag = (int16_t)(((uint16_t)v.integer << Q1_6_FRACTIONAL_BITS) | v.fractional);
    return v.sign ? -(int64_t)mag : (int64_t)mag;
}

static inline Q1_6_t q1_6_from_raw(int64_t raw)
{
    uint16_t max_mag = (uint16_t)((1u << (1 + Q1_6_FRACTIONAL_BITS)) - 1u);
    int64_t mag = raw < 0 ? -raw : raw;
    if (mag > max_mag)
        mag = max_mag;
    Q1_6_t r;
    r.sign = raw < 0;
    r.integer = (uint16_t)((mag >> Q1_6_FRACTIONAL_BITS) & 0x01u);
    r.fractional = (uint16_t)(mag & ((1u << Q1_6_FRACTIONAL_BITS) - 1u));
    return r;
}

static inline int64_t q1_14_to_raw(Q1_14_t v)
{
    int32_t mag = (int32_t)(((uint32_t)v.integer << Q1_14_FRACTIONAL_BITS) | v.fractional);
    return v.sign ? -(int64_t)mag : (int64_t)mag;
}

static inline Q1_14_t q1_14_from_raw(int64_t raw)
{
    uint32_t max_mag = (uint32_t)((1u << (1 + Q1_14_FRACTIONAL_BITS)) - 1u);
    int64_t mag = raw < 0 ? -raw : raw;
    if (mag > max_mag)
        mag = max_mag;
    Q1_14_t r;
    r.sign = raw < 0;
    r.integer = (uint16_t)((mag >> Q1_14_FRACTIONAL_BITS) & 0x01u);
    r.fractional = (uint16_t)(mag & ((1u << Q1_14_FRACTIONAL_BITS) - 1u));
    return r;
}

static inline int64_t q1_30_to_raw(Q1_30_t v)
{
    int64_t mag = ((int64_t)v.integer << Q1_30_FRACTIONAL_BITS) | (int64_t)v.fractional;
    return v.sign ? -mag : mag;
}

static inline Q1_30_t q1_30_from_raw(int64_t raw)
{
    uint64_t max_mag = (1ULL << (1 + Q1_30_FRACTIONAL_BITS)) - 1ULL;
    int64_t mag = raw < 0 ? -raw : raw;
    if ((uint64_t)mag > max_mag)
        mag = (int64_t)max_mag;
    Q1_30_t r;
    r.sign = raw < 0;
    r.integer = (uint32_t)((mag >> Q1_30_FRACTIONAL_BITS) & 0x01u);
    r.fractional = (uint32_t)(mag & ((1u << Q1_30_FRACTIONAL_BITS) - 1u));
    return r;
}

static inline int64_t dq1_6_to_raw(DOUBLE_Q1_6_t v)
{
    int32_t mag = (int32_t)(((uint32_t)v.integer << DOUBLE_Q1_6_FRACTIONAL_BITS) | v.fractional);
    return v.sign ? -(int64_t)mag : (int64_t)mag;
}

static inline DOUBLE_Q1_6_t dq1_6_from_raw(int64_t raw)
{
    uint32_t max_mag = (uint32_t)((1u << (1 + DOUBLE_Q1_6_FRACTIONAL_BITS)) - 1u);
    int64_t mag = raw < 0 ? -raw : raw;
    if ((uint64_t)mag > max_mag)
        mag = max_mag;
    DOUBLE_Q1_6_t r;
    r.sign = raw < 0;
    r.integer = (uint16_t)((mag >> DOUBLE_Q1_6_FRACTIONAL_BITS) & 0x01u);
    r.fractional = (uint16_t)(mag & ((1u << DOUBLE_Q1_6_FRACTIONAL_BITS) - 1u));
    return r;
}

static inline int64_t dq1_14_to_raw(DOUBLE_Q1_14_t v)
{
    int64_t mag = ((int64_t)v.integer << DOUBLE_Q1_14_FRACTIONAL_BITS) | (int64_t)v.fractional;
    return v.sign ? -mag : mag;
}

static inline DOUBLE_Q1_14_t dq1_14_from_raw(int64_t raw)
{
    uint64_t max_mag = (1ULL << (1 + DOUBLE_Q1_14_FRACTIONAL_BITS)) - 1ULL;
    int64_t mag = raw < 0 ? -raw : raw;
    if ((uint64_t)mag > max_mag)
        mag = (int64_t)max_mag;
    DOUBLE_Q1_14_t r;
    r.sign = raw < 0;
    r.integer = (uint32_t)((mag >> DOUBLE_Q1_14_FRACTIONAL_BITS) & 0x01u);
    r.fractional = (uint32_t)(mag & ((1u << DOUBLE_Q1_14_FRACTIONAL_BITS) - 1u));
    return r;
}

static inline int64_t dq1_30_to_raw(DOUBLE_Q1_30_t v)
{
    int64_t mag = ((int64_t)v.integer << DOUBLE_Q1_30_FRACTIONAL_BITS) | (int64_t)v.fractional;
    return v.sign ? -mag : mag;
}

static inline DOUBLE_Q1_30_t dq1_30_from_raw(int64_t raw)
{
    uint64_t max_mag = (1ULL << (1 + DOUBLE_Q1_30_FRACTIONAL_BITS)) - 1ULL;
    uint64_t mag = raw < 0 ? (uint64_t)(-raw) : (uint64_t)raw;
    if (mag > max_mag)
        mag = max_mag;
    DOUBLE_Q1_30_t r;
    r.sign = raw < 0;
    r.integer = (uint64_t)((mag >> DOUBLE_Q1_30_FRACTIONAL_BITS) & 0x01u);
    r.fractional = (uint64_t)(mag & ((1ULL << DOUBLE_Q1_30_FRACTIONAL_BITS) - 1ULL));
    return r;
}
/* Get sign bit: returns 1 if negative, 0 if positive or zero */
bool Q1_6_get_sign_bit(Q1_6_t value)
{
    return value.sign;
}
bool DOUBLE_Q1_6_get_sign_bit(DOUBLE_Q1_6_t value)
{
    return value.sign;
}
bool Q1_14_get_sign_bit(Q1_14_t value)
{
    return value.sign;
}
bool DOUBLE_Q1_14_get_sign_bit(DOUBLE_Q1_14_t value)
{
    return value.sign;
}
bool Q1_30_get_sign_bit(Q1_30_t value)
{
    return value.sign;
}
bool DOUBLE_Q1_30_get_sign_bit(DOUBLE_Q1_30_t value)
{
    return value.sign;
}
/* Set sign bit: returns absolute value if sign=0, negated value if sign=1 */
Q1_6_t Q1_6_set_sign_bit(Q1_6_t value, bool sign)
{
    Q1_6_t result = value;
    result.sign = sign ? 1 : 0;
    return result;
}
DOUBLE_Q1_6_t DOUBLE_Q1_6_set_sign_bit(DOUBLE_Q1_6_t value, bool sign)
{
    DOUBLE_Q1_6_t result = value;
    result.sign = sign ? 1 : 0;
    return result;
}
Q1_14_t Q1_14_set_sign_bit(Q1_14_t value, bool sign)
{
    Q1_14_t result = value;
    result.sign = sign ? 1 : 0;
    return result;
}
DOUBLE_Q1_14_t DOUBLE_Q1_14_set_sign_bit(DOUBLE_Q1_14_t value, bool sign)
{
    DOUBLE_Q1_14_t result = value;
    result.sign = sign ? 1 : 0;
    return result;
}
Q1_30_t Q1_30_set_sign_bit(Q1_30_t value, bool sign)
{
    Q1_30_t result = value;
    result.sign = sign ? 1 : 0;
    return result;
}
DOUBLE_Q1_30_t DOUBLE_Q1_30_set_sign_bit(DOUBLE_Q1_30_t value, bool sign)
{
    DOUBLE_Q1_30_t result = value;
    result.sign = sign ? 1 : 0;
    return result;
}
/* Get fractional part */
Q1_6_t Q1_6_get_fractional_part(Q1_6_t value)
{
    Q1_6_t frac = value;
    frac.integer = 0;
    // frac.sign = 0;
    return frac;
}
Q1_14_t Q1_14_get_fractional_part(Q1_14_t value)
{
    Q1_14_t frac = value;
    frac.integer = 0;
    // frac.sign = 0;
    return frac;
}
DOUBLE_Q1_6_t DOUBLE_Q1_6_get_fractional_part(DOUBLE_Q1_6_t value)
{
    DOUBLE_Q1_6_t frac = value;
    frac.integer = 0;
    // frac.sign = 0;
    return frac;
}
Q1_30_t Q1_30_get_fractional_part(Q1_30_t value)
{
    Q1_30_t frac = value;
    frac.integer = 0;
    // frac.sign = 0;
    return frac;
}
DOUBLE_Q1_14_t DOUBLE_Q1_14_get_fractional_part(DOUBLE_Q1_14_t value)
{
    DOUBLE_Q1_14_t frac = value;
    frac.integer = 0;
    // frac.sign = 0;
    return frac;
}
DOUBLE_Q1_30_t DOUBLE_Q1_30_get_fractional_part(DOUBLE_Q1_30_t value)
{
    DOUBLE_Q1_30_t frac = value;
    frac.integer = 0;
    // frac.sign = 0;
    return frac;
}
/* Arithmetic functions */
Q1_6_t Q1_6_add(Q1_6_t x, Q1_6_t y)
{
    if (Q1_6_get_sign_bit(x) == Q1_6_get_sign_bit(y))
    {
        // Same sign, add magnitudes
        uint8_t sum_fractional = x.fractional + y.fractional;
        uint8_t carry = sum_fractional >> Q1_6_FRACTIONAL_BITS;
        uint8_t sum_integer = x.integer + y.integer + carry;
        if (sum_integer > 1)
        {
            // Overflow, clamp to max value
            sum_integer = 1;
        }
        Q1_6_t result;
        result.sign = x.sign;
        result.integer = sum_integer & 0x01;                                    // Keep only 1 bit
        result.fractional = sum_fractional & ((1 << Q1_6_FRACTIONAL_BITS) - 1); // Keep only fractional bits
        return result;
    }
    else
    {
        // Different signs, perform subtraction
        // Determine which has larger magnitude
        bool x_greater = false;
        if (x.integer > y.integer)
        {
            x_greater = true;
        }
        else if (x.integer == y.integer)
        {
            if (x.fractional > y.fractional)
            {
                x_greater = true;
            }
        }

        Q1_6_t larger = x_greater ? x : y;
        Q1_6_t smaller = x_greater ? y : x;

        // Subtract magnitudes
        uint8_t borrow = 0;
        uint8_t sub_fractional;
        if (larger.fractional < smaller.fractional)
        {
            sub_fractional = (larger.fractional + (1 << Q1_6_FRACTIONAL_BITS)) - smaller.fractional;
            borrow = 1;
        }
        else
        {
            sub_fractional = larger.fractional - smaller.fractional;
        }
        uint8_t sub_integer = larger.integer - smaller.integer - borrow;

        Q1_6_t result;
        result.sign = larger.sign;
        result.integer = sub_integer & 0x01;                                    // Keep only 1 bit
        result.fractional = sub_fractional & ((1 << Q1_6_FRACTIONAL_BITS) - 1); // Keep only fractional bits
        return result;
    }
}

Q1_14_t Q1_14_add(Q1_14_t x, Q1_14_t y)
{
    if (x.sign == y.sign)
    {
        uint32_t sum_fractional = (uint32_t)x.fractional + (uint32_t)y.fractional;
        uint32_t carry = sum_fractional >> Q1_14_FRACTIONAL_BITS;
        uint32_t sum_integer = (uint32_t)x.integer + (uint32_t)y.integer + carry;
        if (sum_integer > 1)
            sum_integer = 1;
        Q1_14_t result;
        result.sign = x.sign;
        result.integer = (uint16_t)(sum_integer & 0x01);
        result.fractional = (uint16_t)(sum_fractional & ((1u << Q1_14_FRACTIONAL_BITS) - 1));
        return result;
    }
    else
    {
        bool x_greater = false;
        if (x.integer > y.integer)
            x_greater = true;
        else if (x.integer == y.integer && x.fractional > y.fractional)
            x_greater = true;

        Q1_14_t larger = x_greater ? x : y;
        Q1_14_t smaller = x_greater ? y : x;

        uint32_t borrow = 0;
        uint32_t sub_fractional;
        if (larger.fractional < smaller.fractional)
        {
            sub_fractional = (uint32_t)larger.fractional + (1u << Q1_14_FRACTIONAL_BITS) - (uint32_t)smaller.fractional;
            borrow = 1;
        }
        else
        {
            sub_fractional = (uint32_t)larger.fractional - (uint32_t)smaller.fractional;
        }
        uint32_t sub_integer = (uint32_t)larger.integer - (uint32_t)smaller.integer - borrow;

        Q1_14_t result;
        result.sign = larger.sign;
        result.integer = (uint16_t)(sub_integer & 0x01);
        result.fractional = (uint16_t)(sub_fractional & ((1u << Q1_14_FRACTIONAL_BITS) - 1));
        return result;
    }
}

DOUBLE_Q1_14_t DOUBLE_Q1_14_add(DOUBLE_Q1_14_t x, DOUBLE_Q1_14_t y)
{
    if (x.sign == y.sign)
    {
        uint32_t sum_fractional = (uint32_t)x.fractional + (uint32_t)y.fractional;
        uint32_t carry = sum_fractional >> DOUBLE_Q1_14_FRACTIONAL_BITS;
        uint32_t sum_integer = (uint32_t)x.integer + (uint32_t)y.integer + carry;
        if (sum_integer > 1)
            sum_integer = 1;
        DOUBLE_Q1_14_t result;
        result.sign = x.sign;
        result.integer = (uint32_t)(sum_integer & 0x01);
        result.fractional = (uint32_t)(sum_fractional & ((1u << DOUBLE_Q1_14_FRACTIONAL_BITS) - 1));
        return result;
    }
    else
    {
        bool x_greater = false;
        if (x.integer > y.integer)
            x_greater = true;
        else if (x.integer == y.integer && x.fractional > y.fractional)
            x_greater = true;

        DOUBLE_Q1_14_t larger = x_greater ? x : y;
        DOUBLE_Q1_14_t smaller = x_greater ? y : x;

        uint32_t borrow = 0;
        uint32_t sub_fractional;
        if (larger.fractional < smaller.fractional)
        {
            sub_fractional = (uint32_t)larger.fractional + (1u << DOUBLE_Q1_14_FRACTIONAL_BITS) - (uint32_t)smaller.fractional;
            borrow = 1;
        }
        else
        {
            sub_fractional = (uint32_t)larger.fractional - (uint32_t)smaller.fractional;
        }
        uint32_t sub_integer = (uint32_t)larger.integer - (uint32_t)smaller.integer - borrow;

        DOUBLE_Q1_14_t result;
        result.sign = larger.sign;
        result.integer = (uint32_t)(sub_integer & 0x01);
        result.fractional = (uint32_t)(sub_fractional & ((1u << DOUBLE_Q1_14_FRACTIONAL_BITS) - 1));
        return result;
    }
}

Q1_30_t Q1_30_add(Q1_30_t x, Q1_30_t y)
{
    if (x.sign == y.sign)
    {
        uint32_t sum_fractional = (uint32_t)x.fractional + (uint32_t)y.fractional;
        uint32_t carry = sum_fractional >> Q1_30_FRACTIONAL_BITS;
        uint32_t sum_integer = (uint32_t)x.integer + (uint32_t)y.integer + carry;
        if (sum_integer > 1)
            sum_integer = 1;
        Q1_30_t result;
        result.sign = x.sign;
        result.integer = (uint32_t)(sum_integer & 0x01);
        result.fractional = (uint32_t)(sum_fractional & ((1u << Q1_30_FRACTIONAL_BITS) - 1));
        return result;
    }
    else
    {
        bool x_greater = false;
        if (x.integer > y.integer)
            x_greater = true;
        else if (x.integer == y.integer && x.fractional > y.fractional)
            x_greater = true;

        Q1_30_t larger = x_greater ? x : y;
        Q1_30_t smaller = x_greater ? y : x;

        uint32_t borrow = 0;
        uint32_t sub_fractional;
        if (larger.fractional < smaller.fractional)
        {
            sub_fractional = (uint32_t)larger.fractional + (1u << Q1_30_FRACTIONAL_BITS) - (uint32_t)smaller.fractional;
            borrow = 1;
        }
        else
        {
            sub_fractional = (uint32_t)larger.fractional - (uint32_t)smaller.fractional;
        }
        uint32_t sub_integer = (uint32_t)larger.integer - (uint32_t)smaller.integer - borrow;

        Q1_30_t result;
        result.sign = larger.sign;
        result.integer = (uint32_t)(sub_integer & 0x01);
        result.fractional = (uint32_t)(sub_fractional & ((1u << Q1_30_FRACTIONAL_BITS) - 1));
        return result;
    }
}

DOUBLE_Q1_30_t DOUBLE_Q1_30_add(DOUBLE_Q1_30_t x, DOUBLE_Q1_30_t y)
{
    if (x.sign == y.sign)
    {
        uint64_t sum_fractional = (uint64_t)x.fractional + (uint64_t)y.fractional;
        uint64_t carry = sum_fractional >> DOUBLE_Q1_30_FRACTIONAL_BITS;
        uint64_t sum_integer = (uint64_t)x.integer + (uint64_t)y.integer + carry;
        if (sum_integer > 1)
            sum_integer = 1;
        DOUBLE_Q1_30_t result;
        result.sign = x.sign;
        result.integer = (uint64_t)(sum_integer & 0x01);
        result.fractional = (uint64_t)(sum_fractional & ((1ULL << DOUBLE_Q1_30_FRACTIONAL_BITS) - 1ULL));
        return result;
    }
    else
    {
        bool x_greater = false;
        if (x.integer > y.integer)
            x_greater = true;
        else if (x.integer == y.integer && x.fractional > y.fractional)
            x_greater = true;

        DOUBLE_Q1_30_t larger = x_greater ? x : y;
        DOUBLE_Q1_30_t smaller = x_greater ? y : x;

        uint64_t borrow = 0;
        uint64_t sub_fractional;
        if (larger.fractional < smaller.fractional)
        {
            sub_fractional = (uint64_t)larger.fractional + (1ULL << DOUBLE_Q1_30_FRACTIONAL_BITS) - (uint64_t)smaller.fractional;
            borrow = 1;
        }
        else
        {
            sub_fractional = (uint64_t)larger.fractional - (uint64_t)smaller.fractional;
        }
        uint64_t sub_integer = (uint64_t)larger.integer - (uint64_t)smaller.integer - borrow;

        DOUBLE_Q1_30_t result;
        result.sign = larger.sign;
        result.integer = (uint64_t)(sub_integer & 0x01);
        result.fractional = (uint64_t)(sub_fractional & ((1ULL << DOUBLE_Q1_30_FRACTIONAL_BITS) - 1ULL));
        return result;
    }
}

DOUBLE_Q1_6_t DOUBLE_Q1_6_add(DOUBLE_Q1_6_t x, DOUBLE_Q1_6_t y)
{
    if (x.sign == y.sign)
    {
        /* Same sign, add magnitudes */
        uint16_t sum_fractional = x.fractional + y.fractional;
        uint16_t carry = sum_fractional >> DOUBLE_Q1_6_FRACTIONAL_BITS; /* carry if fractional overflows 12 bits */
        uint16_t sum_integer = x.integer + y.integer + carry;
        if (sum_integer > 1)
        {
            /* Overflow, clamp integer to 1 */
            sum_integer = 1;
        }
        DOUBLE_Q1_6_t result;
        result.sign = x.sign;
        result.integer = sum_integer & 0x01; /* keep 1 bit */
        result.fractional = sum_fractional & ((1u << DOUBLE_Q1_6_FRACTIONAL_BITS) - 1);
        return result;
    }
    else
    {
        /* Different signs, perform subtraction of magnitudes */
        bool x_greater = false;
        if (x.integer > y.integer)
        {
            x_greater = true;
        }
        else if (x.integer == y.integer)
        {
            if (x.fractional > y.fractional)
            {
                x_greater = true;
            }
        }

        DOUBLE_Q1_6_t larger = x_greater ? x : y;
        DOUBLE_Q1_6_t smaller = x_greater ? y : x;

        /* Subtract magnitudes with borrow from integer if needed */
        uint16_t borrow = 0;
        uint16_t sub_fractional;
        if (larger.fractional < smaller.fractional)
        {
            sub_fractional = (larger.fractional + (1u << DOUBLE_Q1_6_FRACTIONAL_BITS)) - smaller.fractional;
            borrow = 1;
        }
        else
        {
            sub_fractional = larger.fractional - smaller.fractional;
        }
        uint16_t sub_integer = (uint16_t)larger.integer - (uint16_t)smaller.integer - borrow;

        DOUBLE_Q1_6_t result;
        result.sign = larger.sign; /* sign of the operand with larger magnitude */
        result.integer = sub_integer & 0x01;
        result.fractional = sub_fractional & ((1u << DOUBLE_Q1_6_FRACTIONAL_BITS) - 1);
        return result;
    }
}

/* ========================================================================
 * Subtraction
 * ======================================================================== */
Q1_6_t Q1_6_sub(Q1_6_t x, Q1_6_t y)
{
    int64_t raw = q1_6_to_raw(x) - q1_6_to_raw(y);
    return q1_6_from_raw(raw);
}

DOUBLE_Q1_6_t DOUBLE_Q1_6_sub(DOUBLE_Q1_6_t x, DOUBLE_Q1_6_t y)
{
    int64_t raw = dq1_6_to_raw(x) - dq1_6_to_raw(y);
    return dq1_6_from_raw(raw);
}

Q1_14_t Q1_14_sub(Q1_14_t x, Q1_14_t y)
{
    int64_t raw = q1_14_to_raw(x) - q1_14_to_raw(y);
    return q1_14_from_raw(raw);
}

DOUBLE_Q1_14_t DOUBLE_Q1_14_sub(DOUBLE_Q1_14_t x, DOUBLE_Q1_14_t y)
{
    int64_t raw = dq1_14_to_raw(x) - dq1_14_to_raw(y);
    return dq1_14_from_raw(raw);
}

Q1_30_t Q1_30_sub(Q1_30_t x, Q1_30_t y)
{
    int64_t raw = q1_30_to_raw(x) - q1_30_to_raw(y);
    return q1_30_from_raw(raw);
}

DOUBLE_Q1_30_t DOUBLE_Q1_30_sub(DOUBLE_Q1_30_t x, DOUBLE_Q1_30_t y)
{
    int64_t raw = dq1_30_to_raw(x) - dq1_30_to_raw(y);
    return dq1_30_from_raw(raw);
}

/* ========================================================================
 * Multiplication
 * ======================================================================== */
Q1_6_t Q1_6_mul(Q1_6_t x, Q1_6_t y)
{
    int64_t ax = q1_6_to_raw(x);
    int64_t by = q1_6_to_raw(y);
    int64_t raw = (ax * by) >> Q1_6_FRACTIONAL_BITS;
    return q1_6_from_raw(raw);
}

DOUBLE_Q1_6_t DOUBLE_Q1_6_mul(DOUBLE_Q1_6_t x, DOUBLE_Q1_6_t y)
{
    int64_t ax = dq1_6_to_raw(x);
    int64_t by = dq1_6_to_raw(y);
    int64_t raw = (ax * by) >> DOUBLE_Q1_6_FRACTIONAL_BITS;
    return dq1_6_from_raw(raw);
}

Q1_14_t Q1_14_mul(Q1_14_t x, Q1_14_t y)
{
    int64_t ax = q1_14_to_raw(x);
    int64_t by = q1_14_to_raw(y);
    int64_t raw = (ax * by) >> Q1_14_FRACTIONAL_BITS;
    return q1_14_from_raw(raw);
}

DOUBLE_Q1_14_t DOUBLE_Q1_14_mul(DOUBLE_Q1_14_t x, DOUBLE_Q1_14_t y)
{
    int64_t ax = dq1_14_to_raw(x);
    int64_t by = dq1_14_to_raw(y);
    int64_t raw = (ax * by) >> DOUBLE_Q1_14_FRACTIONAL_BITS;
    return dq1_14_from_raw(raw);
}

Q1_30_t Q1_30_mul(Q1_30_t x, Q1_30_t y)
{
    int64_t ax = q1_30_to_raw(x);
    int64_t by = q1_30_to_raw(y);
    int64_t raw = (ax * by) >> Q1_30_FRACTIONAL_BITS;
    return q1_30_from_raw(raw);
}

DOUBLE_Q1_30_t DOUBLE_Q1_30_mul(DOUBLE_Q1_30_t x, DOUBLE_Q1_30_t y)
{
    int64_t ax = dq1_30_to_raw(x);
    int64_t by = dq1_30_to_raw(y);
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif
    __int128 prod = (__int128)ax * (__int128)by;
    int64_t raw = (int64_t)(prod >> DOUBLE_Q1_30_FRACTIONAL_BITS);
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
    return dq1_30_from_raw(raw);
}

/* ========================================================================
 * Division (with simple saturation on divide-by-zero)
 * ======================================================================== */
Q1_6_t Q1_6_div(Q1_6_t x, Q1_6_t y)
{
    int64_t ax = q1_6_to_raw(x);
    int64_t by = q1_6_to_raw(y);
    if (by == 0)
    {
        int64_t limit = (1 << (1 + Q1_6_FRACTIONAL_BITS)) - 1;
        return q1_6_from_raw(ax < 0 ? -limit : limit);
    }
    int64_t raw = (ax << Q1_6_FRACTIONAL_BITS) / by;
    return q1_6_from_raw(raw);
}

DOUBLE_Q1_6_t DOUBLE_Q1_6_div(DOUBLE_Q1_6_t x, DOUBLE_Q1_6_t y)
{
    int64_t ax = dq1_6_to_raw(x);
    int64_t by = dq1_6_to_raw(y);
    if (by == 0)
    {
        int64_t limit = (1 << (1 + DOUBLE_Q1_6_FRACTIONAL_BITS)) - 1;
        return dq1_6_from_raw(ax < 0 ? -limit : limit);
    }
    int64_t raw = (ax << DOUBLE_Q1_6_FRACTIONAL_BITS) / by;
    return dq1_6_from_raw(raw);
}

Q1_14_t Q1_14_div(Q1_14_t x, Q1_14_t y)
{
    int64_t ax = q1_14_to_raw(x);
    int64_t by = q1_14_to_raw(y);
    if (by == 0)
    {
        int64_t limit = (1 << (1 + Q1_14_FRACTIONAL_BITS)) - 1;
        return q1_14_from_raw(ax < 0 ? -limit : limit);
    }
    int64_t raw = (ax << Q1_14_FRACTIONAL_BITS) / by;
    return q1_14_from_raw(raw);
}

DOUBLE_Q1_14_t DOUBLE_Q1_14_div(DOUBLE_Q1_14_t x, DOUBLE_Q1_14_t y)
{
    int64_t ax = dq1_14_to_raw(x);
    int64_t by = dq1_14_to_raw(y);
    if (by == 0)
    {
        int64_t limit = (1LL << (1 + DOUBLE_Q1_14_FRACTIONAL_BITS)) - 1LL;
        return dq1_14_from_raw(ax < 0 ? -limit : limit);
    }
    int64_t raw = (ax << DOUBLE_Q1_14_FRACTIONAL_BITS) / by;
    return dq1_14_from_raw(raw);
}

Q1_30_t Q1_30_div(Q1_30_t x, Q1_30_t y)
{
    int64_t ax = q1_30_to_raw(x);
    int64_t by = q1_30_to_raw(y);
    if (by == 0)
    {
        int64_t limit = (1LL << (1 + Q1_30_FRACTIONAL_BITS)) - 1LL;
        return q1_30_from_raw(ax < 0 ? -limit : limit);
    }
    int64_t raw = (ax << Q1_30_FRACTIONAL_BITS) / by;
    return q1_30_from_raw(raw);
}

DOUBLE_Q1_30_t DOUBLE_Q1_30_div(DOUBLE_Q1_30_t x, DOUBLE_Q1_30_t y)
{
    int64_t ax = dq1_30_to_raw(x);
    int64_t by = dq1_30_to_raw(y);
    if (by == 0)
    {
        int64_t limit = (int64_t)((1ULL << (1 + DOUBLE_Q1_30_FRACTIONAL_BITS)) - 1ULL);
        return dq1_30_from_raw(ax < 0 ? -limit : limit);
    }
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif
    __int128 num = (__int128)ax << DOUBLE_Q1_30_FRACTIONAL_BITS;
    int64_t raw = (int64_t)(num / by);
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
    return dq1_30_from_raw(raw);
}