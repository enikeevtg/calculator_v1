#include "tests.h"

START_TEST(evaluation_error_ACOS) {
  // Arrange
  char str[21] = "acos(2)";
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, ACOS_ERROR);
}
END_TEST

START_TEST(evaluation_error_ASIN) {
  // Arrange
  char str[21] = "asin(2)";
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, ASIN_ERROR);
}
END_TEST

START_TEST(evaluation_error_LN) {
  // Arrange
  char str[21] = "ln(0)";
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, LN_ERROR);
}
END_TEST

START_TEST(evaluation_error_SQRT) {
  // Arrange
  char str[21] = "sqrt(-2)";
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, SQRT_ERROR);
}
END_TEST

START_TEST(evaluation_error_UNBALANCED_BRACKETS_1) {
  // Arrange
  char str[21] = "(sqrt(4)";
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  if (!error) error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, UNBALANCED_BRACKETS);
}
END_TEST

START_TEST(evaluation_error_UNBALANCED_BRACKETS_2) {
  // Arrange
  char str[21] = "sqrt(4))";
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  if (!error) error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, UNBALANCED_BRACKETS);
}
END_TEST

START_TEST(evaluation_error_UNDEFINED_TOKEN) {
  // Arrange
  char str[21] = "sqr(4.)";
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  if (!error) error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, UNDEFINED_TOKEN);
}
END_TEST

START_TEST(evaluation_error_INCORRECT_INPUT) {
  // Arrange
  char str[21] = "sqrt(*4)";
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  if (!error) error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(evaluation_1) {
  // Arrange
  char str[21] = "1+2";
  double reference_result = 1 + 2;
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(result, reference_result, TOLERANCE);
}
END_TEST

START_TEST(evaluation_2) {
  // Arrange
  char str[21] = "(1*2)";
  double reference_result = 1. * 2.;
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(result, reference_result, TOLERANCE);
}
END_TEST

START_TEST(evaluation_3) {
  // Arrange
  char str[21] = "sin(1-2)";
  double reference_result = sin(1 - 2);
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(result, reference_result, TOLERANCE);
}
END_TEST

START_TEST(evaluation_4) {
  // Arrange
  char str[21] = "-cos(1-2.01)";
  double reference_result = -cos(1 - 2.01);
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(result, reference_result, TOLERANCE);
}
END_TEST

START_TEST(evaluation_5) {
  // Arrange
  char str[21] = "2^2^3";
  double reference_result = pow(2., pow(2., 3.));
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(result, reference_result, TOLERANCE);
}
END_TEST

START_TEST(evaluation_6) {
  // Arrange
  char str[21] = "-2^2^3";
  double reference_result = -pow(2., pow(2., 3.));
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(result, reference_result, TOLERANCE);
}
END_TEST

START_TEST(evaluation_7) {
  // Arrange
  char str[51] = "11(3sin(4) +  15)0.1";
  double reference_result = 11 * (3 * sin(4) + 15) * 0.1;
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(result, reference_result, TOLERANCE);
}
END_TEST

START_TEST(evaluation_8) {
  // Arrange
  char str[32] = "1 + 2*6^2 - log(100)";
  double reference_result = 1 + 2 * pow(6., 2.) - log10(100);
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(result, reference_result, TOLERANCE);
}
END_TEST

START_TEST(evaluation_9) {
  // Arrange
  char str[255] =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  double reference_result =
      15. / (7. - (1. + 1.)) * 3. -
      (2. + (1. + 1.)) * 15. / (7. - (200. + 1.)) * 3. -
      (2. + (1. + 1.)) * (15. / (7. - (1. + 1.)) * 3. - (2. + (1. + 1.)) +
                          15. / (7. - (1. + 1.)) * 3. - (2. + (1. + 1.)));
  node_t* q_root = NULL;
  double result = 0;

  // Act
  int error = convert_infix_to_RPN(str, &q_root);
  error = evaluate_expression(q_root, &result);

  // Assert
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(result, reference_result, TOLERANCE);
}
END_TEST

Suite* test_evaluate_expression(void) {
  Suite* s = suite_create("evaluations tests suite");

  TCase* evaluations_with_error_tc = tcase_create("evaluations with error");
  tcase_add_test(evaluations_with_error_tc, evaluation_error_ACOS);
  tcase_add_test(evaluations_with_error_tc, evaluation_error_ASIN);
  tcase_add_test(evaluations_with_error_tc, evaluation_error_LN);
  tcase_add_test(evaluations_with_error_tc, evaluation_error_SQRT);
  tcase_add_test(evaluations_with_error_tc,
                 evaluation_error_UNBALANCED_BRACKETS_1);
  tcase_add_test(evaluations_with_error_tc,
                 evaluation_error_UNBALANCED_BRACKETS_2);
  tcase_add_test(evaluations_with_error_tc, evaluation_error_UNDEFINED_TOKEN);
  tcase_add_test(evaluations_with_error_tc, evaluation_error_INCORRECT_INPUT);
  suite_add_tcase(s, evaluations_with_error_tc);

  TCase* evaluations_tc = tcase_create("evaluations");
  tcase_add_test(evaluations_tc, evaluation_1);
  tcase_add_test(evaluations_tc, evaluation_2);
  tcase_add_test(evaluations_tc, evaluation_3);
  tcase_add_test(evaluations_tc, evaluation_4);
  tcase_add_test(evaluations_tc, evaluation_5);
  tcase_add_test(evaluations_tc, evaluation_6);
  tcase_add_test(evaluations_tc, evaluation_7);
  tcase_add_test(evaluations_tc, evaluation_8);
  tcase_add_test(evaluations_tc, evaluation_9);
  suite_add_tcase(s, evaluations_tc);

  return s;
}
