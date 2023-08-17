#include "tests.h"

START_TEST(convert_error_TOO_LONG_EXPRESSION) {
  // Arrange
  char str[261] = "";
  for (int i = 0; i < 26; i++) strcat(str, "1234567890");
  str[256] = '\0';
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, TOO_LONG_EXPRESSION);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_EMPTY_EXPRESSION) {
  // Arrange
  char str[11] = "";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, EMPTY_EXPRESSION);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_UNDEFINED_TOKEN_1) {
  // Arrange
  char str[11] = "sinasin";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, UNDEFINED_TOKEN);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_UNDEFINED_TOKEN_2) {
  // Arrange
  char str[11] = "1+token";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, UNDEFINED_TOKEN);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_UNDEFINED_TOKEN_3) {
  // Arrange
  char str[11] = "1+tango";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, UNDEFINED_TOKEN);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_UNDEFINED_TOKEN_4) {
  // Arrange
  char str[11] = "1+undef";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, UNDEFINED_TOKEN);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_UNBALANCED_BRACKETS_1) {
  // Arrange
  char str[11] = "((1+2)";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, UNBALANCED_BRACKETS);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_UNBALANCED_BRACKETS_2) {
  // Arrange
  char str[11] = "(1+2))";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, UNBALANCED_BRACKETS);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_UNBALANCED_BRACKETS_3) {
  // Arrange
  char str[21] = "(1+2)sin(1))";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, UNBALANCED_BRACKETS);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_UNBALANCED_BRACKETS_4) {
  // Arrange
  char str[21] = "(1+2)cos((1)";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, UNBALANCED_BRACKETS);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_EMPTY_BRACKETS_1) {
  // Arrange
  char str[21] = "()cos((1)";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, EMPTY_BRACKETS);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_EMPTY_BRACKETS_2) {
  // Arrange
  char str[21] = "(1+2)cos()";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, EMPTY_BRACKETS);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_EMPTY_BRACKETS_3) {
  // Arrange
  char str[21] = "asin(cos())";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, EMPTY_BRACKETS);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_INCORRECT_INPUT_1) {
  // Arrange
  char str[21] = "1.23 2.3 + 3.6";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, INCORRECT_INPUT);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_INCORRECT_INPUT_2) {
  // Arrange
  char str[21] = "1.2.3 + 123.456";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, INCORRECT_INPUT);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_INCORRECT_INPUT_3) {
  // Arrange
  char str[21] = "1++2";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, INCORRECT_INPUT);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_INCORRECT_INPUT_4) {
  // Arrange
  char str[21] = "1+*2";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, INCORRECT_INPUT);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_INCORRECT_INPUT_5) {
  // Arrange
  char str[21] = "1+2-";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, INCORRECT_INPUT);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_INCORRECT_INPUT_6) {
  // Arrange
  char str[21] = "cos";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, INCORRECT_INPUT);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_INCORRECT_INPUT_7) {
  // Arrange
  char str[21] = "asin(cos)";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, INCORRECT_INPUT);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

START_TEST(convert_error_INCORRECT_INPUT_8) {
  // Arrange
  char str[21] = "asin(cos(+))";
  node_t* q_root = NULL;
  // Act
  int error_code = convert_infix_to_RPN(str, &q_root);

  // Assert
  ck_assert_int_eq(error_code, INCORRECT_INPUT);
  ck_assert_ptr_eq(q_root, NULL);
}
END_TEST

Suite* test_errors_convert_infix_to_RPN(void) {
  Suite* s =
      suite_create("converting from infix to RPN with errors tests suite");

  TCase* error_converting_tc = tcase_create("converting with errors");
  tcase_add_test(error_converting_tc, convert_error_TOO_LONG_EXPRESSION);
  tcase_add_test(error_converting_tc, convert_error_EMPTY_EXPRESSION);

  tcase_add_test(error_converting_tc, convert_error_UNDEFINED_TOKEN_1);
  tcase_add_test(error_converting_tc, convert_error_UNDEFINED_TOKEN_2);
  tcase_add_test(error_converting_tc, convert_error_UNDEFINED_TOKEN_3);
  tcase_add_test(error_converting_tc, convert_error_UNDEFINED_TOKEN_4);

  tcase_add_test(error_converting_tc, convert_error_UNBALANCED_BRACKETS_1);
  tcase_add_test(error_converting_tc, convert_error_UNBALANCED_BRACKETS_2);
  tcase_add_test(error_converting_tc, convert_error_UNBALANCED_BRACKETS_3);
  tcase_add_test(error_converting_tc, convert_error_UNBALANCED_BRACKETS_4);

  tcase_add_test(error_converting_tc, convert_error_EMPTY_BRACKETS_1);
  tcase_add_test(error_converting_tc, convert_error_EMPTY_BRACKETS_2);
  tcase_add_test(error_converting_tc, convert_error_EMPTY_BRACKETS_3);

  tcase_add_test(error_converting_tc, convert_error_INCORRECT_INPUT_1);
  tcase_add_test(error_converting_tc, convert_error_INCORRECT_INPUT_2);
  tcase_add_test(error_converting_tc, convert_error_INCORRECT_INPUT_3);
  tcase_add_test(error_converting_tc, convert_error_INCORRECT_INPUT_4);
  tcase_add_test(error_converting_tc, convert_error_INCORRECT_INPUT_5);
  tcase_add_test(error_converting_tc, convert_error_INCORRECT_INPUT_6);
  tcase_add_test(error_converting_tc, convert_error_INCORRECT_INPUT_7);
  tcase_add_test(error_converting_tc, convert_error_INCORRECT_INPUT_8);

  suite_add_tcase(s, error_converting_tc);

  return s;
}
