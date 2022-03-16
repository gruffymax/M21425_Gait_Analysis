/**
 * \file gait_func.c
 */
#include "gait_func.h"

/**
 * \brief Perform integration on a data set.
 * \details Perform integration using the trapezoidal method
 * \param[in] n Length of data_in array
 * \param[in] data_in Pointer to the input data array
 * \param[in] ts Sample time in seconds
 * \param[out] data_out Pointer to the output data array
 */
void integrate_data(int n, float* data_in, float ts, float* data_out)
{
	float subTot = 0;
	for (int i=1; i<n; i++) {
		subTot = 0;
		for (int j=1; j<i+1; j++) {
			subTot = subTot + 0.5*ts*(data_in[j] + data_in[j-1]);
		}
		data_out[i-1] = subTot;
	}
}

/**
 * \brief Calculate the linear regression line of a data array
 * \param[in] n Length of data_in array
 * \param[in] data_in Pointer to the input data array
 * \param[out] data_out Pointer to the output data array
 */
void lin_reg(int n, float* data_in, float* data_out)
{
	float Ex = sum_data(
}

/**
 * \brief Sum the values in a data array
 * \param[in] n Length of data array
 * \param[in] data_in Pointer to input data array
 * \param[in] ts Sample time in seconds
 * \returns The sum of all data in the array
 */
static float sum_data(int n, float* data_in, float ts)
{
	float sum = 0;
	for (int i=0; i<n; i++) {
		sum = sum + data_in[i];
	}
	return sum;
}
