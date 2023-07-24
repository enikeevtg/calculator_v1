#include "tests.h"

START_TEST(container_packing_error_INCORRECT_INPUT_NUMBER) {
  // Arrange
  int prev_address = QUEUE;
  char str[11] = "123.456";
  char* current_str = str;
  node_t* s_head = NULL;

  node_t container = {0};

  // Act
  int error =
      container_packing(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(container_packing_error_INCORRECT_INPUT_OPERATOR) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "*";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  int error =
      container_packing(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(container_packing_INCORRECT_INPUT_FUNCTION) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "ln1";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  int error =
      container_packing(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(container_packing_error_UNDEFINED_TOKEN) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "tangens";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  int error =
      container_packing(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);
  ck_assert_int_eq(error, UNDEFINED_TOKEN);
}
END_TEST

START_TEST(container_packing_NUMBER) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "123.456";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  container_packing(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);
  ck_assert_int_eq(container.token_type, NUMBER);
}
END_TEST

START_TEST(container_packing_NUMBER_after_CLOSE_BRACKET) {
  // Arrange
  int prev_address = QUEUE;
  char str[11] = "123.456";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {NULL, CLOSE_BRACKET, PRIOR_1, 0.0};

  // Act
  container_packing(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_int_eq(container.token_type, MULT);
  push(STACK, &s_head, &container);
  prev_address = STACK;

  container_packing(prev_address, &current_str, &s_head, &container);
  ck_assert_int_eq(container.token_type, NUMBER);

  remove_struct(&s_head);
}
END_TEST

START_TEST(container_packing_OPERATOR) {
  // Arrange
  int prev_address = QUEUE;
  char str[11] = "^";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  container_packing(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_int_eq(container.token_type, POW);

  remove_struct(&s_head);
}
END_TEST

START_TEST(container_packing_U_PLUS_1) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "+";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  container_packing(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_int_eq(container.token_type, U_PLUS);
}
END_TEST

START_TEST(container_packing_U_PLUS_2) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "+";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t s_node = {NULL, OPEN_BRACKET, PRIOR_1, 0.0};
  push(STACK, &s_head, &s_node);

  node_t container = {0};

  // Act
  container_packing(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_int_eq(container.token_type, U_PLUS);
}
END_TEST

START_TEST(container_packing_U_PLUS_3) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "+";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t s_node = {NULL, POW, PRIOR_3, 0.0};
  push(STACK, &s_head, &s_node);
  node_t container = {0};

  // Act
  container_packing(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_int_eq(container.token_type, U_PLUS);
  ck_assert_int_eq(s_head->token_type, POW);

  remove_struct(&s_head);
}
END_TEST

START_TEST(container_packing_FUNCTION) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "log(1)";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t container = {0};

  // Act
  container_packing(prev_address, &current_str, &s_head, &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);
  ck_assert_int_eq(container.token_type, LOG);
}
END_TEST

Suite* test_container_packing(void) {
  Suite* s = suite_create("container_packing function tests suite");

  TCase* container_packing_errors_tc =
      tcase_create("container_packing with errors");
  tcase_add_test(container_packing_errors_tc,
                 container_packing_error_INCORRECT_INPUT_NUMBER);
  tcase_add_test(container_packing_errors_tc,
                 container_packing_error_INCORRECT_INPUT_OPERATOR);
  tcase_add_test(container_packing_errors_tc,
                 container_packing_INCORRECT_INPUT_FUNCTION);
  tcase_add_test(container_packing_errors_tc,
                 container_packing_error_UNDEFINED_TOKEN);
  suite_add_tcase(s, container_packing_errors_tc);

  TCase* container_packing_tc = tcase_create("container_packing OK");
  tcase_add_test(container_packing_tc, container_packing_NUMBER);
  tcase_add_test(container_packing_tc,
                 container_packing_NUMBER_after_CLOSE_BRACKET);
  tcase_add_test(container_packing_tc, container_packing_OPERATOR);
  tcase_add_test(container_packing_tc, container_packing_U_PLUS_1);
  tcase_add_test(container_packing_tc, container_packing_U_PLUS_2);
  tcase_add_test(container_packing_tc, container_packing_U_PLUS_3);
  tcase_add_test(container_packing_tc, container_packing_FUNCTION);
  suite_add_tcase(s, container_packing_tc);

  return s;
}
