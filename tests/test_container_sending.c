#include "tests.h"

START_TEST(container_sending_NUMBER) {
  // Arrange
  int prev_address = STACK;
  node_t* s_head = NULL;
  node_t* q_root = NULL;
  node_t container = {NULL, NUMBER, PRIOR_1, 123.456};

  // Act
  container_sending(&prev_address, &s_head, &q_root, &container);

  // Assert
  ck_assert_ptr_eq(s_head, NULL);
  ck_assert_int_eq(q_root->token_type, NUMBER);

  remove_struct(&q_root);
}
END_TEST

START_TEST(container_sending_PLUS_after_POW) {
  // Arrange
  int prev_address = QUEUE;
  node_t s_node = {NULL, POW, PRIOR_3, 0.0};
  node_t* s_head = NULL;
  push(STACK, &s_head, &s_node);
  node_t* q_root = NULL;
  node_t container = {NULL, PLUS, PRIOR_1, 0.0};

  // Act
  container_sending(&prev_address, &s_head, &q_root, &container);

  // Assert
  ck_assert_int_eq(q_root->token_type, POW);
  ck_assert_int_eq(s_head->token_type, PLUS);

  remove_struct(&q_root);
  remove_struct(&s_head);
}
END_TEST

START_TEST(container_sending_POW_after_POW) {
  // Arrange
  int prev_address = QUEUE;
  node_t s_node = {NULL, POW, PRIOR_3, 0.0};
  node_t* s_head = NULL;
  push(STACK, &s_head, &s_node);
  node_t* q_root = NULL;
  node_t container = {NULL, POW, PRIOR_3, 0.0};

  // Act
  container_sending(&prev_address, &s_head, &q_root, &container);

  // Assert
  ck_assert_ptr_eq(q_root, NULL);
  ck_assert_int_eq(s_head->token_type, POW);
  remove_head_node(&s_head);
  ck_assert_int_eq(s_head->token_type, POW);

  remove_struct(&s_head);
}
END_TEST

Suite* test_container_sending(void) {
  Suite* s = suite_create("container_sending function tests suite");

  TCase* container_sending_tc = tcase_create("container_sending OK");
  tcase_add_test(container_sending_tc, container_sending_NUMBER);
  tcase_add_test(container_sending_tc, container_sending_PLUS_after_POW);
  tcase_add_test(container_sending_tc, container_sending_POW_after_POW);
  suite_add_tcase(s, container_sending_tc);

  return s;
}
