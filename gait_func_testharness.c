#include "gait_func_testharness.h"
#include "gait_func.h"
#include "gait_func.c"

void test_find_minima(int n, float* data_in, int* n_minima, int* minima)
{
	find_minima(n, data_in, n_minima, minima);
}

void test_find_maxima(int n, float* data_in, int* n_maxima, int* maxima)
{
	find_maxima(n, data_in, n_maxima, maxima);
}

float test_calculate_step_length(float h, float l)
{
	return calculate_step_length(h, l);
}

void test_lin_reg(int n, float* data_in, float ts, float* data_out)
{
	lin_reg(n, data_in, ts, data_out);
}
