#ifndef UTIL_H
#define UTIL_H
#include "defines.h"

fp16_t float_to_fp16(float input);
float fp16_to_float(fp16_t input);
fp32_t float_to_fp32(float input);
float fp32_to_float(fp32_t input);
fp32_t fp16_to_fp32(fp16_t input);
fp16_t fp32_to_fp16(fp32_t input);
fp16_t double_to_fp16(double input);
double fp16_to_double(fp16_t input);
fp32_t double_to_fp32(double input);
double fp32_to_double(fp32_t input);
#endif /* UTIL_H */