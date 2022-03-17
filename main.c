#include "gait_func.h"
#include <stdio.h>
#include <stdint.h>

int main (void)
{
	int n = 11;
	float x[8] = {1, 2, -1, -2, 1, 2, -1, -2};
	float h = find_vertical_disp(8, 1, x);
	printf("%.5f\n", h);
}
