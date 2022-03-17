/**
 * \file gait_func.h
 */
#ifndef GAIT_FUNC_H
#define GAIT_FUNC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdint.h>

void integrate_data(int n, float* data_in, float ts, float* data_out);
void lin_reg(int n, float* data_in, float ts, float* data_out);
float find_vertical_disp(int n, float ts, float* velocity_data);

#ifdef __cplusplus
}
#endif
#endif //GAIT_FUNC_H
