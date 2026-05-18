#include "fp16_cordic.h"

// CORDIC gain factor: approximately 0.6072529351
// In Q1.14 format: 0.6072529351 * 2^14 = 9949 = 0x26D7
#define CORDIC_GAIN_FP16 ((fp16_t)0x26D7)

// Number of iterations for CORDIC
#define CORDIC_ITERATIONS 14

// Precomputed arctangent values in Q1.14 radians format
// These are atan(2^-i) for i = 0 to 13
static const fp16_t atan_table_fp16[CORDIC_ITERATIONS] = {
    (fp16_t)0x3243, // atan(2^0)   = 0.7854 rad (45.0 deg)
    (fp16_t)0x1DAC, // atan(2^-1)  = 0.4636 rad (26.57 deg)
    (fp16_t)0x0FB6, // atan(2^-2)  = 0.2450 rad (14.04 deg)
    (fp16_t)0x07D5, // atan(2^-3)  = 0.1244 rad (7.125 deg)
    (fp16_t)0x03FE, // atan(2^-4)  = 0.0624 rad (3.576 deg)
    (fp16_t)0x01FF, // atan(2^-5)  = 0.0312 rad (1.789 deg)
    (fp16_t)0x00FF, // atan(2^-6)  = 0.0156 rad (0.895 deg)
    (fp16_t)0x007F, // atan(2^-7)  = 0.0078 rad (0.448 deg)
    (fp16_t)0x003F, // atan(2^-8)  = 0.0039 rad (0.224 deg)
    (fp16_t)0x001F, // atan(2^-9)  = 0.0020 rad (0.112 deg)
    (fp16_t)0x000F, // atan(2^-10) = 0.0010 rad (0.056 deg)
    (fp16_t)0x0007, // atan(2^-11) = 0.0005 rad (0.028 deg)
    (fp16_t)0x0003, // atan(2^-12) = 0.0002 rad (0.014 deg)
    (fp16_t)0x0001  // atan(2^-13) = 0.0001 rad (0.007 deg)
};

void cordic_core(fp16_t *x, fp16_t *y, fp16_t *z, uint8_t iterations, cordic_mode_t mode)
{
    fp16_t x_new, y_new, z_new;
    bool stop_flag = 0;

    for (uint8_t i = 0; (i < iterations) && !stop_flag; i++)
    {

        if (*z >= 0)
        {
            x_new = *x - (*y >> i);
            y_new = *y + (*x >> i);
            z_new = *z - atan_table_fp16[i];
        }
        else
        {
            x_new = *x + (*y >> i);
            y_new = *y - (*x >> i);
            z_new = *z + atan_table_fp16[i];
        }
        *x = x_new;
        *y = y_new;
        *z = z_new;

        switch (mode)
        {
        case CORDIC_SIN:
        case CORDIC_COS:
            // Rotation mode: no special handling needed
            if (z_new == 0)
                stop_flag = 1;
            break;
        case CORDIC_ATAN2:
            // Vectoring mode: adjust z based on quadrant
            if (y_new == 0)
                stop_flag = 1;
            break;
        default:
            // Invalid mode, could handle error here
            break;
        }
    }
    // For sin: return y, For cos: return x, For atan2: return z
}

fp16_t cordic_sin(fp16_t angle)
{
    fp16_t x = CORDIC_GAIN_FP16;
    fp16_t y = 0;
    cordic_core(&x, &y, &angle, CORDIC_ITERATIONS, CORDIC_SIN);
    return y;
}

fp16_t cordic_cos(fp16_t angle)
{
    // Cosine computation: we need to return the x component
    fp16_t x = CORDIC_GAIN_FP16;
    fp16_t y = 0;
    fp16_t z = angle;

    cordic_core(&x, &y, &z, CORDIC_ITERATIONS, CORDIC_COS);
    return x;
}

fp16_t cordic_atan2(fp16_t y, fp16_t x)
{
    // CORDIC atan2: Vectoring mode - rotate vector (x, y) to x-axis
    // The CORDIC gain factor doesn't apply here since we're just finding angle
    // Returns angle z after vector is rotated to x-axis
    fp16_t x_rot = x;
    fp16_t y_rot = y;
    fp16_t z = 0;

    // Handle special cases for better accuracy
    if (x == 0)
    {
        return (y >= 0) ? (fp16_t)0x6488 : (fp16_t)-0x6488; // Return ±π/2 based on sign of y
    }
    if (y == 0)
    {
        return (x >= 0) ? (fp16_t)0x0000 : (fp16_t)0x8000; // Return 0 or π based on sign of x
    }

    cordic_core(&x_rot, &y_rot, &z, CORDIC_ITERATIONS, CORDIC_ATAN2);
    return z;
}