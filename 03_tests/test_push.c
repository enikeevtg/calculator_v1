#include "tests.h"

START_TEST(push_COS_to_stack) {
  // Arrange
  node_t* s_head = NULL;
  node_t s_node = {NULL, COS, PRIOR_4, 0.0};
  int address = STACK;
  // Act
  int error_code = push(address, &s_head, &s_node);
  // Assert
  ck_assert_int_eq(error_code, OK);

  ck_assert_ptr_eq(s_head->pnext, s_node.pnext);
  ck_assert_int_eq(s_head->token_type, s_node.token_type);
  ck_assert_int_eq(s_head->token_priority, s_node.token_priority);
  ck_assert_int_eq(s_head->token_value, s_node.token_value);

  remove_head_node(&s_head);
}
END_TEST

START_TEST(push_POW_to_stack) {
  // Arrange
  node_t* s_head = NULL;
  node_t s_node = {NULL, POW, PRIOR_4, 0.0};
  int address = STACK;
  // Act
  int error_code = push(address, &s_head, &s_node);
  // Assert
  ck_assert_int_eq(error_code, OK);

  ck_assert_ptr_eq(s_head->pnext, s_node.pnext);
  ck_assert_int_eq(s_head->token_type, s_node.token_type);
  ck_assert_int_eq(s_head->token_priority, s_node.token_priority);
  ck_assert_int_eq(s_head->token_value, s_node.token_value);

  remove_head_node(&s_head);
}
END_TEST

START_TEST(push_NUMBER_to_queue) {
  // Arrange
  node_t* q_head = NULL;
  node_t q_node = {NULL, NUMBER, PRIOR_1, 123.456789};
  int address = QUEUE;
  // Act
  int error_code = push(address, &q_head, &q_node);
  // Assert
  ck_assert_int_eq(error_code, OK);

  ck_assert_ptr_eq(q_head->pnext, q_node.pnext);
  ck_assert_int_eq(q_head->token_type, q_node.token_type);
  ck_assert_int_eq(q_head->token_priority, q_node.token_priority);
  ck_assert_int_eq(q_head->token_value, q_node.token_value);

  remove_head_node(&q_head);
}
END_TEST


Suite* test_push(void) {
  Suite* s = suite_create("push node to stack/queue tests suite");

  TCase* push_to_stack_tc = tcase_create("push node to stack");
  tcase_add_test(push_to_stack_tc, push_COS_to_stack);
  tcase_add_test(push_to_stack_tc, push_POW_to_stack);
  suite_add_tcase(s, push_to_stack_tc);

  TCase* push_to_queue_tc = tcase_create("push node to queue");
  tcase_add_test(push_to_stack_tc, push_NUMBER_to_queue);
  suite_add_tcase(s, push_to_queue_tc);

  return s;
}
