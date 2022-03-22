#include "gait_func.h"
#include <stdio.h>
#include <stdint.h>

int main (void)
{
	int n = 8;
	float x[8] = {1, 2, -1, -2, 1, 2, -1, -2};
	float step = calculate_step_length(0.03, 1.1);
	printf("%.5f\n", step);
}
