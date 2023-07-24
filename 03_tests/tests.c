#include "tests.h"

int main() {
  int tests_count = 0;
  int failed = 0;

  Suite* smart_calc_tests[] = {test_push(),
                               test_fill_node(),
                               test_move_node(),
                               test_close_bracket_processing(),
                               test_end_of_expression_processing(),
                               test_value_packer(),
                               test_operator_packer(),
                               test_function_packer(),
                               test_container_packing(),
                               test_container_sending(),
                               test_token_processing(),
                               test_errors_convert_infix_to_RPN(),
                               test_convert_infix_to_RPN(),
                               test_math_operations(),
                               test_numerical_calculation(),
                               test_evaluate_expression(),
                               NULL};

  for (int i = 0; smart_calc_tests[i] != NULL; i++) {
    SRunner* runner = srunner_create(smart_calc_tests[i]);

    srunner_set_fork_status(runner, CK_NOFORK);
    printf("\n");
    srunner_run_all(runner, CK_NORMAL);

    int this_test_count = srunner_ntests_run(runner);
    int this_test_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    printf("\033[0;32mSUCCESS: %d\n", this_test_count - this_test_failed);
    printf("\033[0;31mFAILED: %d\n\033[0m", this_test_failed);

    tests_count += this_test_count;
    failed += this_test_failed;
  }

  printf("\n\033[0;33mtests summary:\n");
  printf("\033[0;32mSUCCESS: %d\n", tests_count - failed);
  printf("\033[0;31mFAILED: %d\n\033[0m", failed);
  return failed ? 1 : 0;
}
