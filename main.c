#include "unity.h"
#include "gait_func.h"
#include "gait_func_testharness.h"
#include <stdio.h>
#include <stdint.h>

int is_equal(float a, float b)
{
	float d = sqrt(pow(a-b,2));
	
	if (d > 0.001) {
		return 0;
		printf("d=%.5f",d);
	}
	return 1;
}

void setUp(void)
{

}

void tearDown(void)
{

}

void test_1(void)
{
	printf("Testing lin_reg\n");
	float x[7] = {2.0, 1.0, 4.0, 2.0, 5.0, 3.0, 7.0};
	float z[7] = {1.285714, 2.0, 2.714286, 3.428571, 4.142857, 
			4.857143, 5.571429};
	float y[7] = {0};
	test_lin_reg(7, x, 1, y);
	TEST_ASSERT_EQUAL_FLOAT(y[0], z[0]);
	TEST_ASSERT_EQUAL_FLOAT(y[1], z[1]);
	TEST_ASSERT_EQUAL_FLOAT(y[2], z[2]);
	TEST_ASSERT_EQUAL_FLOAT(y[3], z[3]);
	TEST_ASSERT_EQUAL_FLOAT(y[4], z[4]);
	TEST_ASSERT_EQUAL_FLOAT(y[5], z[5]);
	TEST_ASSERT_EQUAL_FLOAT(y[6], z[6]);
}

void test_2(void)
{
	printf("Testing find_minima\n");
	float x[10] = {2.0f, 1.0f, -1.0f, -2.0f, -1.0f, 1.0f, 2.0f,
		1.0f, -1.0f, -2.0f};
	int min;
	int minima[10];
	test_find_minima(10, x, &min, minima);
	TEST_ASSERT_EQUAL(1, min);
	TEST_ASSERT_EQUAL(4, minima[0]);
}

void test_3(void)
{
	printf("Testing find_maxima\n");
	float x[10] = {2.0f, 1.0f, -1.0f, -2.0f, -1.0f, 1.0f, 2.0f,
		1.0f, -1.0f, -2.0f};
	int max;
	int maxima[10];
	test_find_maxima(10, x, &max, maxima);
	TEST_ASSERT_EQUAL(2, max);
	TEST_ASSERT_EQUAL(1, maxima[0]);
	TEST_ASSERT_EQUAL(7, maxima[1]);
}

void test_4(void)
{
	printf("Testing calculate_step_length\n");
	float h = 0.02;
	float l = 1.1;
	float x = test_calculate_step_length(h, l);
	TEST_ASSERT_EQUAL_FLOAT(0.41761, x);
}

void test_5(void)
{
	printf("Testing integrate_data\n");
	float x[10] = {2.0f, 1.0f, -1.0f, -2.0f, -1.0f, 1.0f, 2.0f,
		1.0f, -1.0f, -2.0f};
	float X[9];
	integrate_data(10, x, 1.0, X);
	TEST_ASSERT_EQUAL_FLOAT(1.5, X[0]);
	TEST_ASSERT_EQUAL_FLOAT(1.5, X[1]);
	TEST_ASSERT_EQUAL_FLOAT(0.0, X[2]);
	TEST_ASSERT_EQUAL_FLOAT(-1.5, X[3]);
	TEST_ASSERT_EQUAL_FLOAT(-1.5, X[4]);
	TEST_ASSERT_EQUAL_FLOAT(0.0, X[5]);
	TEST_ASSERT_EQUAL_FLOAT(1.5, X[6]);
	TEST_ASSERT_EQUAL_FLOAT(1.5, X[7]);
	TEST_ASSERT_EQUAL_FLOAT(0.0, X[8]);
}

void test_6(void)
{
	printf("Testing calibration function\n");
	float y = 9.42;
	float y_angle = get_calibration_angle(y);
	TEST_ASSERT_EQUAL_FLOAT(0.282919, y_angle);
}

void test_7(void)
{
	printf("Testing get_corrected_y\n");
	float y_raw = 9.661;
	float y_angle = get_calibration_angle(y_raw);
	float y = get_corrected_y(y_angle, 8.5);
	TEST_ASSERT_EQUAL_FLOAT(-1.1789, y);
}

void test_8(void)
{
	printf("Testing get_corrected_x\n");
	float x_angle = get_calibration_angle(9.661);
	float x = get_corrected_x(x_angle, 2.0);
	TEST_ASSERT_EQUAL(1, is_equal(0.2925, x));
}

int main (void)
{
	UNITY_BEGIN();
	RUN_TEST(test_1);
	RUN_TEST(test_2);
	RUN_TEST(test_3);
	RUN_TEST(test_4);
	RUN_TEST(test_5);
	RUN_TEST(test_6);
	RUN_TEST(test_7);
	RUN_TEST(test_8);
	return UNITY_END();
}
