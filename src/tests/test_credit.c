#include <check.h>

#include "../credit_calc/s21_credit.h"
#include "s21_tests.h"

START_TEST(test1) {
  long double loan, term, interest_rate, payments, total_interest, total, max,
      min;
  int type = 1;
  loan = 3000000;
  term = 120;
  interest_rate = 9;
  double payments_exp = 38002.73;
  double total_interest_exp = 1560327.60;
  double tota_exp = 4560327.60;
  credit_calc(loan, term, interest_rate, type, &payments, &total_interest,
              &total, &max, &min);
  ck_assert_ldouble_eq_tol(payments, payments_exp, 2);
  ck_assert_ldouble_eq_tol(total_interest, total_interest_exp, 2);
  ck_assert_ldouble_eq_tol(total, tota_exp, 2);
}
END_TEST

START_TEST(test2) {
  long double loan, term, interest_rate, payments, total_interest, total, max,
      min;
  int type = 2;
  loan = 300000;
  term = 12;
  interest_rate = 9;
  double payments_exp = 26218.0743;
  double total_interest_exp = 14616.8915;
  double tota_exp = 314616.892;
  credit_calc(loan, term, interest_rate, type, &payments, &total_interest,
              &total, &max, &min);
  ck_assert_ldouble_eq_tol(payments, payments_exp, 2);
  ck_assert_ldouble_eq_tol(total_interest, total_interest_exp, 2);
  ck_assert_ldouble_eq_tol(total, tota_exp, 2);
}
END_TEST

Suite *suite_credit(void) {
  Suite *s = suite_create("credit");
  TCase *tc = tcase_create("credit_tc");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  suite_add_tcase(s, tc);

  return s;
}
