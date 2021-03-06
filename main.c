#include "unity.h"
#include "gait_func.h"
#include "gait_func_testharness.h"
#include <stdio.h>
#include <stdint.h>

#define UNITY_OUTPUT_COLOR

#include "data.c"

void setUp(void)
{

}

void tearDown(void)
{

}

void test_1(void)
{
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
	float h = 0.02;
	float l = 1.1;
	float x = test_calculate_step_length(h, l);
	TEST_ASSERT_EQUAL_FLOAT(0.41761, x);
}

void test_5(void)
{
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
	float x = 2.74;
	float y = 9.42;
	float y_angle = get_calibration_angle(x, y);
	TEST_ASSERT_EQUAL_FLOAT(0.28306, y_angle);
}

void test_7(void)
{
	float x_raw = 1.507;
	float y_raw = 9.661;
	float y_angle = get_calibration_angle(x_raw, y_raw);
	TEST_ASSERT_EQUAL_FLOAT(0.154741, y_angle);

	float y = get_corrected_y(y_angle, y_raw, 8.5);
	TEST_ASSERT_EQUAL_FLOAT(-1.17504, y);
}

void test_8(void)
{
	float x_angle = get_calibration_angle(1.507, 9.661);
	float x = get_corrected_x(x_angle, 1.507, 2.0);
	TEST_ASSERT_EQUAL_FLOAT(0.487109, x);
}

void test_9(void)
{
	step_t mystep = calculate_step_linreg(500, 0.01, 1.1, data);
	/* Test results are confirmed with MATLAB */
	TEST_ASSERT_EQUAL_FLOAT(0.47206, mystep.length);
	TEST_ASSERT_EQUAL_FLOAT(164.3836, mystep.cadence);
	TEST_ASSERT_EQUAL_FLOAT(1.293325, mystep.gait_speed);
	TEST_ASSERT_EQUAL_FLOAT(3.8660, mystep.time);
}

void test_10(void)
{
	float data[5] = {3, -2, -1, 2, 1};
	float res = test_get_minimum_value(5, data);
	TEST_ASSERT_EQUAL_FLOAT(-2.0, res);
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
	RUN_TEST(test_9);
	RUN_TEST(test_10);
	return UNITY_END();
}
