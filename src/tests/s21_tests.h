#ifndef SRC_TESTS_S21_MATH_H_
#define SRC_TESTS_S21_MATH_H_

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_calc.h"

#define PREC 1e-6

Suite *suite_calc(void);
Suite *suite_credit(void);

void run_tests(void);
void run_testcase(Suite *testcase);

#endif  // SRC_TESTS_S21_MATH_H_
