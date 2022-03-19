#include "gait_func.h"
#include <stdio.h>
#include <stdint.h>

int main (void)
{
	int n = 8;
	float x[8] = {1, 2, -1, -2, 1, 2, -1, -2};
	float h = calculate_h_lin_reg(8, 1, x);
	printf("%.5f\n", h);
}
