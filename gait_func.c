/**
 * \file gait_func.c
 */
#include "gait_func.h"
#include <stdlib.h>



static void find_minima(int n, float* data_in, int* n_minima, int* minima);
static void find_maxima(int n, float* data_in, int* n_maxima, int* maxima);
static step_t _calculate_step(int n, float ts, float l, float* acceleration_data, int with_linreg);
static float calculate_step_length(float h, float l);
static void lin_reg(int n, float* data_in, float ts, float* data_out);

/**
 * \brief Calculate calibration angle in radians
 * \details The calibration angle is used to scale the readings from the
 * accelerometer to the actual vertical and horizontal values.
 * \param[in] x The x axis value (m/s^2)
 * \param[in] y The y axis value (m/s^2)
 * \returns The calibration angle (radians)
 */
float get_calibration_angle(float x, float y)
{
	return (float)atan(x / y);
}

/**
 * \brief Correct the y-axis value based on the correction angle
 * \param[in] angle The correction angle (radians)
 * \param[in] y_cal The Y-axis value taken during session calibration
 * \param[in] y_raw The raw y value (m/s^2)
 * \returns The corrected y value (m/s^2)
 */
float get_corrected_y(float angle, float y_cal, float y_raw)
{
	return (y_raw-y_cal)/cos(angle);
}

/**
 * \brief Correct the x-axis value based on the correction angle
 * \param[in] angle The correction angle (radians)
 * \param[in] x_cal The X-axis value taken during session calibration
 * \param[in] x_raw The raw x value (m/s^2)
 * \returns The corrected x value (m/s^2)
 */
float get_corrected_x(float angle, float x_cal, float x_raw)
{
	return (x_raw-x_cal)*cos(angle);
}


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
static void lin_reg(int n, float* data_in, float ts, float* data_out)
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
 * \brief Calculate gait parameters
 * \details Finds the vertical displacement from a vertical acceleration dataset.
 * \param[in] n Length of data set
 * \param[in] ts Sample time in seconds
 * \param[in] l Height of sensor from the ground in meters
 * \param[in] acceleration_data Pointer to acceleration data array
 * \param[in] with_linreg Flag to enable or disable linear regression
 * \returns The mean displacement in m
 */
static step_t _calculate_step(int n, float ts, float l, float* acceleration_data, int with_linreg)
{
	step_t step;
	float* velocity_data = malloc((n-1)*sizeof(float));
	float* disp_data = malloc((n-2)*sizeof(float));

	/* Calculate displacement data */
	integrate_data(n, acceleration_data, ts, velocity_data);
	if (with_linreg) {
		float* reg_line = malloc((n-1)*sizeof(float));
		lin_reg(n-1, velocity_data, ts, reg_line);
		for (int i=0; i<n-1; i++) {
			velocity_data[i] = velocity_data[i] - reg_line[i];
		}
		free(reg_line);
	}
	integrate_data(n-1, velocity_data, ts, disp_data);
	
	/* Calculate minima and maxima */
	int n_minima = 0;
	int n_maxima = 0;
	int minima[20] = {0};
	int maxima[20] = {0};

	find_minima(n, velocity_data, &n_minima, minima);
	find_maxima(n, velocity_data, &n_maxima, maxima);
	
	/* Calculate step length */
	float h = 0;
	int m = 0;
	if (n_minima <= n_maxima) {
		m = n_minima;
	}
	else {
		m = n_maxima;
	}

	float subTot = 0.0;
	for (int i=0; i<m; i++) {
		subTot = subTot + (disp_data[maxima[i]]+10) - (disp_data[minima[i]]+10);
	}
	h = subTot / m;
	step.length = calculate_step_length(h, l);

	/* Calculate time between steps */
	subTot = 0;
	float step_delta = 0;
	for (int i=0; i<n_minima-1; i++) {
		subTot = subTot + minima[i+1] - minima[i];
	}
	step_delta = subTot * ts / (n_minima-1);

	step.cadence = 60/step_delta;
	step.gait_speed = step.length / step_delta;
	step.time = 5/step.gait_speed;

	free(velocity_data);
	free(disp_data);

	return step;
}

/**
 * \brief Wrapper function to call _calculate_step without linear regression
 * \param[in] n Length of data set
 * \param[in] ts Sample time in seconds
 * \param[in] l Height of sensor from the ground in meters
 * \param[in] acceleration_data Pointer to acceleration data array
 * \returns A step_t struct with the calculated gait parameters
 */
step_t calculate_step(int n, float ts, float l, float* acceleration_data)
{
	return _calculate_step(n, ts, l, acceleration_data, 0);
}

/**
 * \brief Wrapper function to call _calculate_step with linear regression
 * \param[in] n Length of data set
 * \param[in] ts Sample time in seconds
 * \param[in] l Height of sensor from the ground in meters
 * \param[in] acceleration_data Pointer to acceleration data array
 * \returns A step_t struct with the calculated gait parameters
 */
step_t calculate_step_linreg(int n, float ts, float l, float* acceleration_data)
{
	return _calculate_step(n, ts, l, acceleration_data, 1);
}

/**
 * \brief Calculate step length
 * \param[in] h Vertical displacement in meters
 * \param[in] l Height of the sensor from the ground in meters
 * \returns The estimated step length in meters
 */
static float calculate_step_length(float h, float l)
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

