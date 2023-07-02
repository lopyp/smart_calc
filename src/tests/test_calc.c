#include <check.h>

#include "s21_tests.h"

START_TEST(test1) {
  char input[255] = "123.45";
  char output[255] = "\0";
  double expect = 123.45;
  main_calc(input, output, 1);
  double res = strtod(output, NULL);
  ck_assert_double_eq_tol(expect, res, PREC);
}
END_TEST

START_TEST(test2) {
  char input[255] = "123.45 + 342.2356345";
  char output[255] = "\0";
  double expect = 123.45 + 342.2356345;
  main_calc(input, output, 1);
  double res = strtod(output, NULL);
  ck_assert_double_eq_tol(expect, res, PREC);
}
END_TEST

START_TEST(test3) {
  char input[255] =
      "-123.45 + 342.2356345 * 341. / .1235 * (0 + 0.23 - 3 ^ (-(-(+(-342 mod "
      "21)))))";
  char output[255] = "\0";
  double expect =
      -123.45 + 342.2356345 * 341. / .1235 *
                    (0. + 0.23 - pow(3., -(-(+(fmod(-342., 21.))))));
  main_calc(input, output, 1);
  double res = strtod(output, NULL);
  ck_assert_double_eq_tol(expect, res, PREC);
}
END_TEST

START_TEST(test4) {
  char input[255] = "-(-2+3) * 4.3422342 - tan(230+70) ^ sqrt(cos(0.45))";
  char output[255] = "\0";
  double expect = -(-2 + 3) * 4.3422342 - pow(tan(230 + 70), sqrt(cos(0.45)));
  main_calc(input, output, 1);
  double res = strtod(output, NULL);
  ck_assert_double_eq_tol(expect, res, PREC);
}
END_TEST

START_TEST(test5) {
  char input[255] =
      "-(-2+3) * 4.3422342 - log(234+23) ^ ln(1.34) / acos(.321) * asin(.9234) "
      "+ atan(1)";
  char output[255] = "\0";
  double expect = -(-2 + 3) * 4.3422342 -
                  pow(log10(234 + 23), log(1.34)) / acos(.321) * asin(.9234) +
                  atan(1);
  main_calc(input, output, 1);
  double res = strtod(output, NULL);
  ck_assert_double_eq_tol(expect, res, PREC);
}
END_TEST

START_TEST(test14) {
  char input[255] =
      "-(-2+3) * 4.3422342 - log(234+23 +4*x) ^ ln(1.34) / acos(.321) * "
      "asin(.9234) "
      "+ atan(1)";
  char output[255] = "\0";
  double expect =
      -(-2 + 3) * 4.3422342 -
      pow(log10(234 + 23 + 4 * 7), log(1.34)) / acos(.321) * asin(.9234) +
      atan(1);
  main_calc(input, output, 7);
  double res = strtod(output, NULL);
  ck_assert_double_eq_tol(expect, res, PREC);
}
END_TEST

START_TEST(test6) {
  char input[255] = "log(";
  char output[255] = "\0";
  int error = main_calc(input, output, 1);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(test7) {
  char input[255] = "134+dfe";
  char output[255] = "\0";
  int error = main_calc(input, output, 1);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(test8) {
  char input[255] = "134+";
  char output[255] = "\0";
  int error = main_calc(input, output, 1);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(test9) {
  char input[255] = "134+.";
  char output[255] = "\0";
  int error = main_calc(input, output, 1);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(test10) {
  char input[255] = "34+134x";
  char output[255] = "\0";
  int error = main_calc(input, output, 1);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(test11) {
  char input[255] = "63+134)";
  char output[255] = "\0";
  int error = main_calc(input, output, 1);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(test12) {
  char input[255] = "1./0";
  char output[255] = "\0";
  int error = main_calc(input, output, 1);
  ck_assert_int_eq(405, error);
}
END_TEST

START_TEST(test13) {
  char input[255] = "0./0";
  char output[255] = "\0";
  int error = main_calc(input, output, 1);
  ck_assert_int_eq(404, error);
}
END_TEST

START_TEST(test15) {
  char input[255] = "63+*m134";
  char output[255] = "\0";
  int error = main_calc(input, output, 1);
  ck_assert_int_eq(1, error);
}
END_TEST

Suite *suite_calc(void) {
  Suite *s = suite_create("calc");
  TCase *tc = tcase_create("calc_tc");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);
  tcase_add_test(tc, test6);
  tcase_add_test(tc, test7);
  tcase_add_test(tc, test8);
  tcase_add_test(tc, test9);
  tcase_add_test(tc, test10);
  tcase_add_test(tc, test11);
  tcase_add_test(tc, test12);
  tcase_add_test(tc, test13);
  tcase_add_test(tc, test14);
  tcase_add_test(tc, test15);
  suite_add_tcase(s, tc);

  return s;
}
