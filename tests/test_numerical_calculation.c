#include "tests.h"

START_TEST(calculation_ACOS_error) {
  // Arrange
  node_t s_node = {NULL, NUMBER, PRIOR_1, 1.1};
  node_t* s_head = &s_node;
  // Act
  int error = numerical_calculation(&s_head, ACOS);
  // Assert
  ck_assert_int_eq(error, ACOS_ERROR);
}
END_TEST

START_TEST(calculation_ASIN_error) {
  // Arrange
  node_t s_node = {NULL, NUMBER, PRIOR_1, 1.1};
  node_t* s_head = &s_node;
  // Act
  int error = numerical_calculation(&s_head, ASIN);
  // Assert
  ck_assert_int_eq(error, ASIN_ERROR);
}
END_TEST

START_TEST(calculation_LN_error) {
  // Arrange
  node_t s_node = {NULL, NUMBER, PRIOR_1, 0.0};
  node_t* s_head = &s_node;
  // Act
  int error = numerical_calculation(&s_head, LN);
  // Assert
  ck_assert_int_eq(error, LN_ERROR);
}
END_TEST

START_TEST(calculation_LOG_error) {
  // Arrange
  node_t s_node = {NULL, NUMBER, PRIOR_1, 0.0};
  node_t* s_head = &s_node;
  // Act
  int error = numerical_calculation(&s_head, LOG);
  // Assert
  ck_assert_int_eq(error, LOG_ERROR);
}
END_TEST

START_TEST(calculation_SQRT_error) {
  // Arrange
  node_t s_node = {NULL, NUMBER, PRIOR_1, -0.11};
  node_t* s_head = &s_node;
  // Act
  int error = numerical_calculation(&s_head, SQRT);
  // Assert
  ck_assert_int_eq(error, SQRT_ERROR);
}
END_TEST

START_TEST(calculation_SIN) {
  // Arrange
  double value = 1.1;
  node_t s_node = {NULL, NUMBER, PRIOR_1, value};
  node_t* s_head = NULL;
  push(STACK, &s_head, &s_node);
  // Act
  int error = numerical_calculation(&s_head, SIN);
  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(s_head->token_value, sin(value), TOLERANCE);

  remove_struct(&s_head);
}
END_TEST

START_TEST(calculation_LN) {
  // Arrange
  double value = 1.1;
  node_t s_node = {NULL, NUMBER, PRIOR_1, value};
  node_t* s_head = NULL;
  push(STACK, &s_head, &s_node);
  // Act
  int error = numerical_calculation(&s_head, LN);
  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(s_head->token_value, log(value), TOLERANCE);

  remove_struct(&s_head);
}
END_TEST

START_TEST(calculation_SQRT) {
  // Arrange
  double value = 16.0;
  node_t s_node = {NULL, NUMBER, PRIOR_1, value};
  node_t* s_head = NULL;
  push(STACK, &s_head, &s_node);
  // Act
  int error = numerical_calculation(&s_head, SQRT);
  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(s_head->token_value, sqrt(value), TOLERANCE);

  remove_struct(&s_head);
}
END_TEST

START_TEST(calculation_DIV) {
  // Arrange
  double value_1 = 3.1112348;
  double value_2 = 1.95;
  node_t s_node_1 = {NULL, NUMBER, PRIOR_1, value_1};
  node_t s_node_2 = {NULL, NUMBER, PRIOR_1, value_2};
  node_t* s_head = NULL;
  push(STACK, &s_head, &s_node_1);
  push(STACK, &s_head, &s_node_2);
  // Act
  int error = numerical_calculation(&s_head, DIV);
  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(s_head->token_value, value_1 / value_2, TOLERANCE);

  remove_struct(&s_head);
}
END_TEST

START_TEST(calculation_POW) {
  // Arrange
  double value_1 = 3.1112348;
  double value_2 = 1.95;
  node_t s_node_1 = {NULL, NUMBER, PRIOR_1, value_1};
  node_t s_node_2 = {NULL, NUMBER, PRIOR_1, value_2};
  node_t* s_head = NULL;
  push(STACK, &s_head, &s_node_1);
  push(STACK, &s_head, &s_node_2);
  // Act
  int error = numerical_calculation(&s_head, POW);
  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(s_head->token_value, pow(value_1, value_2),
                          TOLERANCE);

  remove_struct(&s_head);
}
END_TEST

Suite* test_numerical_calculation(void) {
  Suite* s = suite_create("numerical calculation test suite");

  TCase* errors_tc = tcase_create("numerical calculations with error");
  tcase_add_test(errors_tc, calculation_ACOS_error);
  tcase_add_test(errors_tc, calculation_ASIN_error);
  tcase_add_test(errors_tc, calculation_LN_error);
  tcase_add_test(errors_tc, calculation_LOG_error);
  tcase_add_test(errors_tc, calculation_SQRT_error);
  suite_add_tcase(s, errors_tc);

  TCase* unary_calculations_tc =
      tcase_create("unary functions numerical calculations");
  tcase_add_test(unary_calculations_tc, calculation_SIN);
  tcase_add_test(unary_calculations_tc, calculation_LN);
  tcase_add_test(unary_calculations_tc, calculation_SQRT);
  suite_add_tcase(s, unary_calculations_tc);

  TCase* binary_calculations_tc =
      tcase_create("binary functions numerical calculations");
  tcase_add_test(binary_calculations_tc, calculation_DIV);
  tcase_add_test(binary_calculations_tc, calculation_POW);
  suite_add_tcase(s, binary_calculations_tc);

  return s;
}
