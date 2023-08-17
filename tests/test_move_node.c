#include "tests.h"

START_TEST(from_stack_to_queue_1) {
  // Arrange
  node_t s_node = {NULL, COS, PRIOR_4, 0.0};
  node_t* s_head = NULL;
  push(STACK, &s_head, &s_node);

  node_t* q_head = NULL;

  // Act
  move_node_from_stack_to_queue(&s_head, &q_head);

  // Assert
  ck_assert_ptr_eq(q_head->pnext, NULL);
  ck_assert_int_eq(q_head->token_type, s_node.token_type);
  ck_assert_int_eq(q_head->token_priority, s_node.token_priority);
  ck_assert_int_eq(q_head->token_value, s_node.token_value);

  ck_assert_ptr_eq(s_head, NULL);

  remove_head_node(&q_head);
}
END_TEST

START_TEST(from_stack_to_queue_2) {
  // Arrange
  node_t s_node_1 = {NULL, COS, PRIOR_4, 0.0};
  node_t s_node_2 = {NULL, NUMBER, PRIOR_1, 100.500};

  node_t* s_head = NULL;
  push(STACK, &s_head, &s_node_1);
  push(STACK, &s_head, &s_node_2);

  node_t* q_root = NULL;

  // Act
  move_node_from_stack_to_queue(&s_head, &q_root);
  node_t* q_head = q_root;
  move_node_from_stack_to_queue(&s_head, &q_head);

  // Assert
  ck_assert_ptr_eq(q_root->pnext, q_head);
  ck_assert_int_eq(q_root->token_type, s_node_2.token_type);
  ck_assert_int_eq(q_root->token_priority, s_node_2.token_priority);
  ck_assert_int_eq(q_root->token_value, s_node_2.token_value);

  ck_assert_ptr_eq(q_head->pnext, NULL);
  ck_assert_int_eq(q_head->token_type, s_node_1.token_type);
  ck_assert_int_eq(q_head->token_priority, s_node_1.token_priority);
  ck_assert_int_eq(q_head->token_value, s_node_1.token_value);

  ck_assert_ptr_eq(s_head, NULL);

  remove_struct(&q_root);
}
END_TEST

START_TEST(from_queue_to_stack_1) {
  // Arrange
  node_t q_node = {NULL, COS, PRIOR_4, 0.0};
  node_t* q_root = NULL;
  push(QUEUE, &q_root, &q_node);

  node_t* s_head = NULL;

  // Act
  move_node_from_queue_to_stack(&q_root, &s_head);

  // Assert
  ck_assert_ptr_eq(s_head->pnext, NULL);
  ck_assert_int_eq(s_head->token_type, q_node.token_type);
  ck_assert_int_eq(s_head->token_priority, q_node.token_priority);
  ck_assert_int_eq(s_head->token_value, q_node.token_value);

  ck_assert_ptr_eq(q_root, NULL);

  remove_head_node(&s_head);
}
END_TEST

START_TEST(from_queue_to_stack_2) {
  // Arrange
  node_t q_node_1 = {NULL, COS, PRIOR_4, 0.0};
  node_t q_node_2 = {NULL, NUMBER, PRIOR_1, 100.500};
  node_t* q_root = NULL;
  push(QUEUE, &q_root, &q_node_1);
  node_t* q_head = q_root;
  push(QUEUE, &q_head, &q_node_2);

  node_t* s_head = NULL;

  // Act
  move_node_from_queue_to_stack(&q_root, &s_head);
  node_t* s_bottom = s_head;
  move_node_from_queue_to_stack(&q_root, &s_head);

  // Assert
  ck_assert_ptr_eq(s_head->pnext, s_bottom);
  ck_assert_int_eq(s_head->token_type, q_node_2.token_type);
  ck_assert_int_eq(s_head->token_priority, q_node_2.token_priority);
  ck_assert_int_eq(s_head->token_value, q_node_2.token_value);

  ck_assert_ptr_eq(s_bottom->pnext, NULL);
  ck_assert_int_eq(s_bottom->token_type, q_node_1.token_type);
  ck_assert_int_eq(s_bottom->token_priority, q_node_1.token_priority);
  ck_assert_int_eq(s_bottom->token_value, q_node_1.token_value);

  ck_assert_ptr_eq(q_root, NULL);

  remove_struct(&s_head);
}
END_TEST

Suite* test_move_node(void) {
  Suite* s = suite_create("moving node tests suite");

  TCase* from_st_to_q_tc = tcase_create("moving node from stack to queue");
  tcase_add_test(from_st_to_q_tc, from_stack_to_queue_1);
  tcase_add_test(from_st_to_q_tc, from_stack_to_queue_2);
  suite_add_tcase(s, from_st_to_q_tc);

  TCase* from_q_to_st_tc = tcase_create("moving node from stack to queue");
  tcase_add_test(from_q_to_st_tc, from_queue_to_stack_1);
  tcase_add_test(from_q_to_st_tc, from_queue_to_stack_2);
  suite_add_tcase(s, from_q_to_st_tc);

  return s;
}
