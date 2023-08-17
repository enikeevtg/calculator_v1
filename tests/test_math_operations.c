#include "tests.h"

START_TEST(u_plus_test) {
  // Arrange
  double value = 123.4951547;
  // Act
  double result = u_plus(value);
  // Assert
  ck_assert_double_eq_tol(result, value, TOLERANCE);
}
END_TEST

START_TEST(u_minus_test) {
  // Arrange
  double value = 123.4786547;
  // Act
  double result = u_minus(value);
  // Assert
  ck_assert_double_eq_tol(result, -value, TOLERANCE);
}
END_TEST

START_TEST(add_test) {
  // Arrange
  double value_1 = 123.4224863;
  double value_2 = 983.7934988;
  // Act
  double result = add_calc(value_1, value_2);
  // Assert
  ck_assert_double_eq_tol(result, value_1 + value_2, TOLERANCE);
}
END_TEST

START_TEST(sub_test) {
  // Arrange
  double value_1 = 123.4224863;
  double value_2 = 983.7934988;
  // Act
  double result = sub_calc(value_1, value_2);
  // Assert
  ck_assert_double_eq_tol(result, value_1 - value_2, TOLERANCE);
}
END_TEST

START_TEST(mult_test) {
  // Arrange
  double value_1 = 123.4224863;
  double value_2 = 983.7934988;
  // Act
  double result = mult_calc(value_1, value_2);
  // Assert
  ck_assert_double_eq_tol(result, value_1 * value_2, TOLERANCE);
}
END_TEST

START_TEST(div_test) {
  // Arrange
  double value_1 = 123.4224863;
  double value_2 = 983.7934988;
  // Act
  double result = div_calc(value_1, value_2);
  // Assert
  ck_assert_double_eq_tol(result, value_1 / value_2, TOLERANCE);
}
END_TEST

Suite* test_math_operations(void) {
  Suite* s = suite_create("math operations test suite");
  TCase* math_operations_tc = tcase_create("math operations test case");
  tcase_add_test(math_operations_tc, u_plus_test);
  tcase_add_test(math_operations_tc, u_minus_test);
  tcase_add_test(math_operations_tc, add_test);
  tcase_add_test(math_operations_tc, sub_test);
  tcase_add_test(math_operations_tc, mult_test);
  tcase_add_test(math_operations_tc, div_test);
  suite_add_tcase(s, math_operations_tc);

  return s;
}
