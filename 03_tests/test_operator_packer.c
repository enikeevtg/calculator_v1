#include "tests.h"

START_TEST(operator_packer_error_INCORRECT_INPUT_OPERATOR) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "/";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  int error = operator_packer(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);

  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(operator_packer_OPERATOR_MOD) {
  // Arrange
  int prev_address = QUEUE;
  char str[11] = "%";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  operator_packer(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);

  ck_assert_int_eq(container.token_type, MOD);

  remove_struct(&s_head);
}
END_TEST

START_TEST(operator_packer_OPERATOR_DIV) {
  // Arrange
  int prev_address = QUEUE;
  char str[11] = "/";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  operator_packer(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);

  ck_assert_int_eq(container.token_type, DIV);

  remove_struct(&s_head);
}
END_TEST

START_TEST(operator_packer_U_MINUS_1) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "-";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  operator_packer(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_int_eq(container.token_type, U_MINUS);
}
END_TEST

START_TEST(operator_packer_U_MINUS_2) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "-";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t s_node = {NULL, OPEN_BRACKET, PRIOR_1, 0.0};
  push(STACK, &s_head, &s_node);
  node_t container = {0};

  // Act
  operator_packer(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_int_eq(container.token_type, U_MINUS);

  remove_struct(&s_head);
}
END_TEST

START_TEST(operator_packer_U_MINUS_3) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "-";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t s_node = {NULL, POW, PRIOR_3, 0.0};
  push(STACK, &s_head, &s_node);
  node_t container = {0};

  // Act
  operator_packer(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_int_eq(container.token_type, U_MINUS);

  remove_struct(&s_head);
}
END_TEST

START_TEST(operator_packer_OPEN_BRACKET) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "(";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  operator_packer(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_int_eq(container.token_type, OPEN_BRACKET);
}
END_TEST

START_TEST(operator_packer_OPEN_BRACKET_after_NUMBER) {
  // Arrange
  int prev_address = QUEUE;
  char str[11] = "(";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  operator_packer(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_int_eq(container.token_type, MULT);

  prev_address = STACK;
  operator_packer(prev_address, &current_str, &s_head, &container);
  ck_assert_int_eq(container.token_type, OPEN_BRACKET);
}
END_TEST

Suite* test_operator_packer(void) {
  Suite* s = suite_create("operator_packer function tests suite");

  TCase* operator_packer_errors_tc =
      tcase_create("operator_packer with errors");
  tcase_add_test(operator_packer_errors_tc,
                 operator_packer_error_INCORRECT_INPUT_OPERATOR);
  suite_add_tcase(s, operator_packer_errors_tc);

  TCase* operator_packer_tc = tcase_create("operator_packer OK");
  tcase_add_test(operator_packer_tc, operator_packer_OPERATOR_MOD);
  tcase_add_test(operator_packer_tc, operator_packer_OPERATOR_DIV);
  tcase_add_test(operator_packer_tc, operator_packer_U_MINUS_1);
  tcase_add_test(operator_packer_tc, operator_packer_U_MINUS_2);
  tcase_add_test(operator_packer_tc, operator_packer_U_MINUS_3);
  tcase_add_test(operator_packer_tc, operator_packer_OPEN_BRACKET);
  tcase_add_test(operator_packer_tc, operator_packer_OPEN_BRACKET_after_NUMBER);
  suite_add_tcase(s, operator_packer_tc);

  return s;
}
