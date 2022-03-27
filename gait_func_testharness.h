#ifndef GAIT_FUNC_TESTHARNESS_H
#define GAIT_FUNC_TESTHARNESS_H

void test_find_minima(int n, float* data_in, int* n_minima, int* minima);
void test_find_maxima(int n, float* data_in, int* n_maxima, int* maxima);
float test_calculate_step_length(float h, float l);
void test_lin_reg(int n, float* data_in, float ts, float* data_out);

#endif // GAIT_FUNC_TESTHARNESS_H
