#include "tests.h"

START_TEST(token_processing_error_INCORRECT_INPUT_NUMBER) {
  // Arrange
  int prev_address = QUEUE;
  char str[11] = "123.456";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t* q_root = NULL;
  node_t container = {0};

  // Act
  int error = token_processing(&prev_address, &current_str, &s_head, &q_root,
                               &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);
  ck_assert_ptr_eq(q_root, NULL);

  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(token_processing_error_INCORRECT_INPUT_OPERATOR) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "*";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t* q_root = NULL;
  node_t container = {0};

  // Act
  int error = token_processing(&prev_address, &current_str, &s_head, &q_root,
                               &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);
  ck_assert_ptr_eq(q_root, NULL);

  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(token_processing_INCORRECT_INPUT_FUNCTION) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "ln1";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t* q_root = NULL;
  node_t container = {0};

  // Act
  int error = token_processing(&prev_address, &current_str, &s_head, &q_root,
                               &container);

  // Assert
  ck_assert_ptr_eq(q_root, NULL);
  ck_assert_ptr_eq(s_head, NULL);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(token_processing_error_UNDEFINED_TOKEN) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "tangens";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t* q_root = NULL;
  node_t container = {0};

  // Act
  int error = token_processing(&prev_address, &current_str, &s_head, &q_root,
                               &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);
  ck_assert_ptr_eq(q_root, NULL);
  ck_assert_int_eq(error, UNDEFINED_TOKEN);
}
END_TEST

START_TEST(token_processing_NUMBER) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "123.456";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t* q_root = NULL;
  node_t container = {0};

  // Act
  token_processing(&prev_address, &current_str, &s_head, &q_root, &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);
  ck_assert_int_eq(q_root->token_type, NUMBER);

  remove_struct(&q_root);
}
END_TEST

START_TEST(token_processing_NUMBER_after_CLOSE_BRACKET) {
  // Arrange
  int prev_address = QUEUE;
  char str[11] = "123.456";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t* q_root = NULL;
  node_t container = {NULL, CLOSE_BRACKET, PRIOR_1, 0.0};

  // Act
  token_processing(&prev_address, &current_str, &s_head, &q_root, &container);
  token_processing(&prev_address, &current_str, &s_head, &q_root, &container);

  // Assert

  ck_assert_int_eq(s_head->token_type, MULT);
  ck_assert_int_eq(q_root->token_type, NUMBER);

  remove_struct(&q_root);
  remove_struct(&s_head);
}
END_TEST

START_TEST(token_processing_OPERATOR) {
  // Arrange
  int prev_address = QUEUE;
  char str[11] = "^";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t* q_root = NULL;
  node_t container = {0};

  // Act
  token_processing(&prev_address, &current_str, &s_head, &q_root, &container);

  // Assert
  ck_assert_ptr_eq(q_root, NULL);
  ck_assert_int_eq(s_head->token_type, POW);

  remove_struct(&s_head);
}
END_TEST

START_TEST(token_processing_U_MINUS_1) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "-";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t* q_root = NULL;
  node_t container = {0};

  // Act
  token_processing(&prev_address, &current_str, &s_head, &q_root, &container);

  // Assert
  ck_assert_ptr_eq(q_root, NULL);
  ck_assert_int_eq(s_head->token_type, U_MINUS);

  remove_struct(&s_head);
}
END_TEST

START_TEST(token_processing_U_MINUS_2) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "-";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t s_node = {NULL, OPEN_BRACKET, PRIOR_1, 0.0};
  push(STACK, &s_head, &s_node);
  node_t* q_root = NULL;
  node_t container = {0};

  // Act
  token_processing(&prev_address, &current_str, &s_head, &q_root, &container);

  // Assert
  ck_assert_ptr_eq(q_root, NULL);
  ck_assert_int_eq(s_head->token_type, U_MINUS);

  remove_struct(&s_head);
}
END_TEST

START_TEST(token_processing_U_MINUS_3) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "-";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t s_node = {NULL, POW, PRIOR_4, 0.0};
  push(STACK, &s_head, &s_node);
  node_t* q_root = NULL;
  node_t container = {0};

  // Act
  token_processing(&prev_address, &current_str, &s_head, &q_root, &container);

  // Assert
  ck_assert_ptr_eq(q_root, NULL);
  ck_assert_int_eq(s_head->token_type, U_MINUS);
  remove_head_node(&s_head);
  ck_assert_int_eq(s_head->token_type, POW);

  remove_struct(&q_root);
  remove_struct(&s_head);
}
END_TEST

START_TEST(token_processing_FUNCTION) {
  // Arrange
  int prev_address = STACK;
  char str[11] = "log(1)";
  char* current_str = str;
  node_t* s_head = NULL;
  node_t* q_root = NULL;
  node_t container = {0};

  // Act
  token_processing(&prev_address, &current_str, &s_head, &q_root, &container);

  // Assert
  ck_assert_ptr_eq(q_root, NULL);
  ck_assert_int_eq(s_head->token_type, LOG);

  remove_struct(&s_head);
}
END_TEST

Suite* test_token_processing(void) {
  Suite* s = suite_create("token_processing function tests suite");

  TCase* token_processing_errors_tc =
      tcase_create("token_processing with errors");
  tcase_add_test(token_processing_errors_tc,
                 token_processing_error_INCORRECT_INPUT_NUMBER);
  tcase_add_test(token_processing_errors_tc,
                 token_processing_error_INCORRECT_INPUT_OPERATOR);
  tcase_add_test(token_processing_errors_tc,
                 token_processing_INCORRECT_INPUT_FUNCTION);
  tcase_add_test(token_processing_errors_tc,
                 token_processing_error_UNDEFINED_TOKEN);
  suite_add_tcase(s, token_processing_errors_tc);

  TCase* token_processing_tc = tcase_create("token_processing OK");
  tcase_add_test(token_processing_tc, token_processing_NUMBER);
  tcase_add_test(token_processing_tc,
                 token_processing_NUMBER_after_CLOSE_BRACKET);
  tcase_add_test(token_processing_tc, token_processing_OPERATOR);
  tcase_add_test(token_processing_tc, token_processing_U_MINUS_1);
  tcase_add_test(token_processing_tc, token_processing_U_MINUS_2);
  tcase_add_test(token_processing_tc, token_processing_U_MINUS_3);
  tcase_add_test(token_processing_tc, token_processing_FUNCTION);
  suite_add_tcase(s, token_processing_tc);

  return s;
}
