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
void find_minima(int n, float* data_in, int* n_minima, int* minima);
void find_maxima(int n, float* data_in, int* n_maxima, int* maxima);

#ifdef __cplusplus
}
#endif
#endif //GAIT_FUNC_H
