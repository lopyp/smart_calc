#include "s21_tests.h"

int main(void) {
  int failed = 0;
  Suite *s;
  SRunner *runner;
  s = suite_calc();
  runner = srunner_create(s);

  srunner_add_suite(runner, suite_credit());

  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);

  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
