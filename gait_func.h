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
};
typedef struct Step step_t;

step_t calculate_step(int n, float ts, float l, float* acceleration_data);
step_t calculate_step_linreg(int n, float ts, float l, float* acceleration_data);
void integrate_data(int n, float* data_in, float ts, float* data_out);
float get_calibration_angle(float x, float y);
float get_corrected_y(float angle, float y_cal, float y_raw);
float get_corrected_x(float angle, float x_cal, float x_raw);
void lin_reg(int n, float* data_in, float ts, float* data_out);

#ifdef __cplusplus
}
#endif
#endif //GAIT_FUNC_H
