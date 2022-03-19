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

struct Step {
	float length;
	float cadence;
	float gait_speed;
	float time;
}


void integrate_data(int n, float* data_in, float ts, float* data_out);
void lin_reg(int n, float* data_in, float ts, float* data_out);
float calculate_h(int n, float ts, float* acceleration_data);
float calculate_h_lin_reg(int n, float ts, float* acceleration_data);
float calculate_step_length(float h, float l);

#ifdef __cplusplus
}
#endif
#endif //GAIT_FUNC_H
