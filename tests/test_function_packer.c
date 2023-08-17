#include "tests.h"

START_TEST(function_packer_error_UNDEFINED_TOKEN) {
  // Arrange
  char str[11] = "sqr4";
  char* current_str = str;
  node_t container = {0};

  // Act
  int error = function_packer(&current_str, &container);

  // Assert
  ck_assert_int_eq(error, UNDEFINED_TOKEN);
}
END_TEST

START_TEST(function_packer_error_INCORRECT_INPUT_FUNCTION) {
  // Arrange
  char str[11] = "sqrt4";
  char* current_str = str;
  node_t container = {0};

  // Act
  int error = function_packer(&current_str, &container);

  // Assert
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(container_packing_SQRT) {
  // Arrange
  char str[11] = "sqrt(1)";
  char* current_str = str;
  node_t container = {0};

  // Act
  int error = function_packer(&current_str, &container);

  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_int_eq(container.token_type, SQRT);
}
END_TEST

Suite* test_function_packer(void) {
  Suite* s = suite_create("function_packer function tests suite");

  TCase* function_packer_errors_tc =
      tcase_create("function_packer with errors");
  tcase_add_test(function_packer_errors_tc,
                 function_packer_error_UNDEFINED_TOKEN);
  tcase_add_test(function_packer_errors_tc,
                 function_packer_error_INCORRECT_INPUT_FUNCTION);
  suite_add_tcase(s, function_packer_errors_tc);

  TCase* function_packer_tc = tcase_create("function_packer OK");
  tcase_add_test(function_packer_tc, container_packing_SQRT);
  suite_add_tcase(s, function_packer_tc);

  return s;
}
