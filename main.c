#include "gait_func.h"
#include <stdio.h>
#include <stdint.h>

int main (void)
{
	int n = 11;
	float x[11] = {0.0, 1.0, 2.0, -1.0, -2.0, 2.0, 1.0, -1.0, 1.0, 2.0, -1.0};
	float X[11];
	lin_reg(n, x, 1, X);
	for (int i=0; i<10; i++) {
		printf("%.5f\n", X[i]);
	}
}
