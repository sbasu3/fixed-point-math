#ifndef __UTILITIES_H
#define __UTILITIES_H
#include <stdint.h>
#include <stdbool.h>
#include "defines.h"
/* ========================================================================
 * Generic Fixed-Point Utility Functions
 * ======================================================================== */
/* Get sign bit: returns 1 if negative, 0 if positive or zero */
bool Q1_6_get_sign_bit(Q1_6_t value);
bool DOUBLE_Q1_6_get_sign_bit(DOUBLE_Q1_6_t value);
bool Q1_14_get_sign_bit(Q1_14_t value);
bool DOUBLE_Q1_14_get_sign_bit(DOUBLE_Q1_14_t value);
bool Q1_30_get_sign_bit(Q1_30_t value);
bool DOUBLE_Q1_30_get_sign_bit(DOUBLE_Q1_30_t value);
/* ============================================================= */

/* Set sign bit: returns absolute value if sign=0, negated value if sign=1 */

Q1_6_t Q1_6_set_sign_bit(Q1_6_t value, bool sign);
DOUBLE_Q1_6_t DOUBLE_Q1_6_set_sign_bit(DOUBLE_Q1_6_t value, bool sign);
Q1_14_t Q1_14_set_sign_bit(Q1_14_t value, bool sign);
DOUBLE_Q1_14_t DOUBLE_Q1_14_set_sign_bit(DOUBLE_Q1_14_t value, bool sign);
Q1_30_t Q1_30_set_sign_bit(Q1_30_t value, bool sign);
DOUBLE_Q1_30_t DOUBLE_Q1_30_set_sign_bit(DOUBLE_Q1_30_t value, bool sign);
/* ============================================================= */

/*Get fractional part */

Q1_6_t Q1_6_get_fractional_part(Q1_6_t value);
DOUBLE_Q1_6_t DOUBLE_Q1_6_get_fractional_part(DOUBLE_Q1_6_t value);
Q1_14_t Q1_14_get_fractional_part(Q1_14_t value);
DOUBLE_Q1_14_t DOUBLE_Q1_14_get_fractional_part(DOUBLE_Q1_14_t value);
Q1_30_t Q1_30_get_fractional_part(Q1_30_t value);
DOUBLE_Q1_30_t DOUBLE_Q1_30_get_fractional_part(DOUBLE_Q1_30_t value);
/* ============================================================= */

/* Arithmetic functions */
Q1_6_t Q1_6_add(Q1_6_t x, Q1_6_t y);
DOUBLE_Q1_6_t DOUBLE_Q1_6_add(DOUBLE_Q1_6_t x, DOUBLE_Q1_6_t y);
Q1_6_t Q1_6_sub(Q1_6_t x, Q1_6_t y);
DOUBLE_Q1_6_t DOUBLE_Q1_6_sub(DOUBLE_Q1_6_t x, DOUBLE_Q1_6_t y);
Q1_6_t Q1_6_mul(Q1_6_t x, Q1_6_t y);
DOUBLE_Q1_6_t DOUBLE_Q1_6_mul(DOUBLE_Q1_6_t x, DOUBLE_Q1_6_t y);
Q1_6_t Q1_6_div(Q1_6_t x, Q1_6_t y);
DOUBLE_Q1_6_t DOUBLE_Q1_6_div(DOUBLE_Q1_6_t x, DOUBLE_Q1_6_t y);

Q1_14_t Q1_14_add(Q1_14_t x, Q1_14_t y);
DOUBLE_Q1_14_t DOUBLE_Q1_14_add(DOUBLE_Q1_14_t x, DOUBLE_Q1_14_t y);
Q1_14_t Q1_14_sub(Q1_14_t x, Q1_14_t y);
DOUBLE_Q1_14_t DOUBLE_Q1_14_sub(DOUBLE_Q1_14_t x, DOUBLE_Q1_14_t y);
Q1_14_t Q1_14_mul(Q1_14_t x, Q1_14_t y);
DOUBLE_Q1_14_t DOUBLE_Q1_14_mul(DOUBLE_Q1_14_t x, DOUBLE_Q1_14_t y);
Q1_14_t Q1_14_div(Q1_14_t x, Q1_14_t y);
DOUBLE_Q1_14_t DOUBLE_Q1_14_div(DOUBLE_Q1_14_t x, DOUBLE_Q1_14_t y);

Q1_30_t Q1_30_add(Q1_30_t x, Q1_30_t y);
DOUBLE_Q1_30_t DOUBLE_Q1_30_add(DOUBLE_Q1_30_t x, DOUBLE_Q1_30_t y);
Q1_30_t Q1_30_sub(Q1_30_t x, Q1_30_t y);
DOUBLE_Q1_30_t DOUBLE_Q1_30_sub(DOUBLE_Q1_30_t x, DOUBLE_Q1_30_t y);
Q1_30_t Q1_30_mul(Q1_30_t x, Q1_30_t y);
DOUBLE_Q1_30_t DOUBLE_Q1_30_mul(DOUBLE_Q1_30_t x, DOUBLE_Q1_30_t y);
Q1_30_t Q1_30_div(Q1_30_t x, Q1_30_t y);
DOUBLE_Q1_30_t DOUBLE_Q1_30_div(DOUBLE_Q1_30_t x, DOUBLE_Q1_30_t y);
#endif /* __UTILITIES_H */