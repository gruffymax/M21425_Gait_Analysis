#include "unity.h"
#include "gait_func.h"
#include "gait_func_testharness.h"
#include <stdio.h>
#include <stdint.h>

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

int main (void)
{
	UNITY_BEGIN();
	RUN_TEST(test_1);
	RUN_TEST(test_2);
	RUN_TEST(test_3);
	RUN_TEST(test_4);
	RUN_TEST(test_5);
	return UNITY_END();
}
