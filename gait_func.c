/**
 * \file gait_func.c
 */
#include "gait_func.h"
#include <stdlib.h>


static void find_minima(int n, float* data_in, int* n_minima, int* minima);
static void find_maxima(int n, float* data_in, int* n_maxima, int* maxima);

/**
 * \brief Perform integration on a data set.
 * \details Perform integration using the trapezoidal method
 * \note The length of the data_out array MUST be 1 less
 * than the data_in array.
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
 * \param[in] ts Sample time in seconds
 * \param[out] data_out Pointer to the output data array
 */
void lin_reg(int n, float* data_in, float ts, float* data_out)
{
	float Ex = 0;
	float Ey = 0;
	float Exy = 0;
	float Ex2 = 0;
	for (int i=0; i<n; i++) {
		Ex = Ex + ts*(float)i;
		Ey = Ey + data_in[i];
		Exy = Exy + (data_in[i]*ts*(float)i);
		Ex2 = Ex2 + pow(ts*(float)i, 2);
	}
	
	float a = (Ey*Ex2-Ex*Exy)/(n*Ex2-pow(Ex, 2));
	float b = (n*Exy-Ex*Ey)/(n*Ex2-pow(Ex, 2));
	for (int i=0; i<n; i++) {
		data_out[i] = b*ts*(float)i + a;
	}
}

/**
 * \brief Find mean vertical displacement
 * \details Finds the vertical displacement from a vertical acceleration dataset.
 * \param[in] n Length of data set
 * \param[in] ts Sample time in seconds
 * \param[in] acceleration_data Pointer to acceleration data array
 * \returns The mean displacement in m
 */
float calculate_h(int n, float ts, float* acceleration_data)
{
	float* velocity_data = malloc((n-1)*sizeof(float));
	float* disp_data = malloc((n-2)*sizeof(float));
	
	integrate_data(n, acceleration_data, ts, velocity_data);
	integrate_data(n-1, velocity_data, ts, disp_data);
	
	int n_minima = 0;
	int n_maxima = 0;
	int minima[10] = {0};
	int maxima[10] = {0};

	find_minima(n, velocity_data, &n_minima, minima);
	find_maxima(n, velocity_data, &n_maxima, maxima);
	
	int m = 0;
	if (n_minima <= n_maxima) {
		m = n_minima;
	}
	else {
		m = n_maxima;
	}

	float subTot = 0.0;
	for (int i=0; i<m; i++) {
		subTot = subTot + (disp_data[maxima[i]] - disp_data[minima[i]]);
	}
	free(velocity_data);
	free(disp_data);
	return subTot / m;
}

/**
 * \brief Find mean vertical displacement with linear regression
 * \details Finds the vertical displacement from vertical acceleratiion dataset.
 * After integrating to velocity, the data is straightened using linear
 * regression.
 * \param[in] n Length of data set
 * \param[in] ts Sample time in seconds
 * \param[in] acceleration_data Pointer to acceleration data array
 * \returns The mean displacement in m
 */
float calculate_h_lin_reg(int n, float ts, float* acceleration_data)
{
	float* velocity_data = malloc((n-1)*sizeof(float));
	float* disp_data = malloc((n-2)*sizeof(float));
	float* reg_line = malloc((n-1)*sizeof(float));

	integrate_data(n, acceleration_data, ts, velocity_data);
	lin_reg(n-1, velocity_data, ts, reg_line);
	for (int i=0; i<n-1; i++) {
		velocity_data[i] = velocity_data[i] - reg_line[i];
	}
	integrate_data(n-1, velocity_data, ts, disp_data);
	
	int n_minima = 0;
	int n_maxima = 0;
	int minima[10] = {0};
	int maxima[10] = {0};

	find_minima(n, velocity_data, &n_minima, minima);
	find_maxima(n, velocity_data, &n_maxima, maxima);
	
	int m = 0;
	if (n_minima <= n_maxima) {
		m = n_minima;
	}
	else {
		m = n_maxima;
	}

	float subTot = 0.0;
	for (int i=0; i<m; i++) {
		subTot = subTot + (disp_data[maxima[i]] - disp_data[minima[i]]);
	}
	free(velocity_data);
	free(disp_data);
	return subTot / m;
}

/**
 * \brief Calculate step length
 * \param[in] h Vertical displacement in meters
 * \param[in] l Height of the sensor from the ground in meters
 * \returns The estimated step length in meters
 */
float calculate_step_length(float h, float l)
{
	return 2*sqrt(2*l*h - pow(h,2));
}

/**
 * \brief Find minima points
 * \details Locates the point where the data crosses the x axis. Passing from
 * negative to positive gives the location of a minima in the corrosponing 
 * integrated data set.
 * # Example
 * x is a dataset and x1 is the integrated dataset. Find the minima in x1 by
 * calling find_minima on x. 
 * \param[in] n Length of data_in array
 * \param[in] data_in Dataset from which to find minima
 * \param[out] n_minima Number of minima found
 * \param[out] minima Pointer to array of minima locations
 */
static void find_minima(int n, float* data_in, int* n_minima, int* minima)
{
	*n_minima = 0;
	for (int i=0; i<n-1; i++) {
		if (data_in[i] < 0 && data_in[i+1] > 0) {
			if (i > 0) {
				minima[*n_minima] = i;
			}
			else {
				minima[*n_minima] = 0;
			}
			*n_minima = *n_minima + 1;
		}
	}
}

/**
 * \brief Find maxima points
 * \details Locates the point where the data crosses the x axis. Passing from
 * positive to negative gives the location of a maxima in the corrosponding 
 * integrated data set.
 * # Example
 * x is a dataset and x1 is the integrated dataset. Find the maxima in x1 by
 * calling find_maxima on x. 
 * \param[in] n Length of data_in array
 * \param[in] data_in Dataset from which to find maxima
 * \param[out] n_maxima Number of maxima found
 * \param[out] maxima Pointer to array of maxima locations
 */
static void find_maxima(int n, float* data_in, int* n_maxima, int* maxima)
{
	*n_maxima = 0;
	for (int i=0; i<n-1; i++) {
		if (data_in[i] > 0 && data_in[i+1] < 0) {
			if (i > 0) {
				maxima[*n_maxima] = i;
			}
			else {
				maxima[*n_maxima] = 0;
			}
			*n_maxima = *n_maxima + 1;
		}
	}
}

