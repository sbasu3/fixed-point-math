#ifndef __CORDIC_H__
#define __CORDIC_H__

#include <stdint.h>
#include <stdbool.h>
#include "defines.h"

typedef enum
{
    CORDIC_SIN = 0,
    CORDIC_COS,
    CORDIC_ATAN2
} cordic_mode_t;

void cordic_core(fp16_t *x, fp16_t *y, fp16_t *z, uint8_t iterations, cordic_mode_t mode);
fp16_t cordic_sin(fp16_t angle);
fp16_t cordic_cos(fp16_t angle);
fp16_t cordic_atan2(fp16_t y, fp16_t x);
#endif // __CORDIC_H__