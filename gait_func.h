#ifndef GAIT_FUNC_H
#define GAIT_FUNC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdint.h>

/**
 * \brief Perform integration on a data set.
 * \param[in] n Length of data_in array
 * \param[in] data_in Pointer to the input data array
 * \param[in] ts Sample time in seconds
 * \param[out] Pointer to the output data array
 */
void integrate_data(int n, float* data_in, float ts, float* data_out);

#ifdef __cplusplus
}
#endif
#endif //GAIT_FUNC_H
