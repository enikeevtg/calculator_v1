#include "tests.h"

START_TEST(convert_1) {
  // Arrange
  char str[21] = "1+2";
  // 1 2 +
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, OK);
  node_t q_node = {0};
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 1., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 2., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, PLUS);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(evaluation_2) {
  // Arrange
  char str[21] = "(1*2)";
  // 1 2 *
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, OK);
  node_t q_node = {0};
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 1., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 2., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, MULT);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_3) {
  // Arrange
  char str[21] = "sin(1-2)";
  // 1 2 - sin
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, OK);
  node_t q_node = {0};
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 1., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 2., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, MINUS);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, SIN);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_4) {
  // Arrange
  char str[21] = "-cos(1-2.01)";
  // 1 2.01 - cos u-
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, OK);
  node_t q_node = {0};
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 1., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 2.01, TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, MINUS);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, COS);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, U_MINUS);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_5) {
  // Arrange
  char str[21] = "2^2^3";
  // 2 2 3 ^ ^
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, OK);
  node_t q_node = {0};
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 2., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 2., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 3., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, POW);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, POW);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_6) {
  // Arrange
  char str[21] = "-2^2^3";
  // 2 2 3 ^ ^ u-
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, OK);
  node_t q_node = {0};
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 2., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 2., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 3., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, POW);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, POW);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, U_MINUS);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_7) {
  // Arrange
  char str[51] = "11(3sin(4) +  15)0.1";
  // 11 3 4 sin * 15 + * 0.1 *
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, OK);
  node_t q_node = {0};
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 11., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 3., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 4., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, SIN);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, MULT);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 15., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, PLUS);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, MULT);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 0.1, TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, MULT);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_8) {
  // Arrange
  char str[32] = "1 + 2*6^2 - log(100)";
  // 1 2 6 2 ^ * + 100 u- log
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, OK);
  node_t q_node = {0};
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 1., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 2., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 6., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 2., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, POW);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, MULT);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, PLUS);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, NUMBER);
  ck_assert_double_eq_tol(q_node.token_value, 100., TOLERANCE);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, LOG);
  pop(&q_root, &q_node);
  ck_assert_int_eq(q_node.token_type, MINUS);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

Suite* test_convert_infix_to_RPN(void) {
  Suite* s = suite_create("converting from infix to RPN tests suite");

  TCase* converting_tc = tcase_create("converting");
  tcase_add_test(converting_tc, convert_1);
  tcase_add_test(converting_tc, evaluation_2);
  tcase_add_test(converting_tc, convert_3);
  tcase_add_test(converting_tc, convert_4);
  tcase_add_test(converting_tc, convert_5);
  tcase_add_test(converting_tc, convert_6);
  tcase_add_test(converting_tc, convert_7);
  tcase_add_test(converting_tc, convert_8);
  suite_add_tcase(s, converting_tc);

  return s;
}
