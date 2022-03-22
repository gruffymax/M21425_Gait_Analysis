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
typedef struct Step step_t;

step_t calculate_step(int n, float ts, float l, float* acceleration_data);
step_t calculate_step_linreg(int n, float ts, float l, float* acceleration_data);

#ifdef __cplusplus
}
#endif
#endif //GAIT_FUNC_H
