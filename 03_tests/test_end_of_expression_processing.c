#include "tests.h"

START_TEST(end_of_expression_error_UNBALANCED_BRACKETS) {
  // Arrange
  //         |     U_PLUS     |           |--------|-----
  // STACK:  |       \|/      |   QUEUE:  | NUMBER | ->
  //         |__OPEN_BRACKET__|           |--------|-----

  node_t* s_head = NULL;
  node_t s_node_1 = {NULL, OPEN_BRACKET, PRIOR_1, 0.0};
  node_t s_node_2 = {NULL, U_PLUS, PRIOR_4, 0.0};
  push(STACK, &s_head, &s_node_1);
  push(STACK, &s_head, &s_node_2);

  node_t q_root_node = {NULL, NUMBER, PRIOR_1, 3.1415};
  node_t* q_root = NULL;
  push(QUEUE, &q_root, &q_root_node);
  node_t* q_head = q_root;

  // Act
  int error_code = end_of_expression_processing(&s_head, &q_head);
  node_t q_node_1 = {0};
  node_t q_node_2 = {0};
  pop(&q_root, &q_node_1);
  pop(&q_root, &q_node_2);

  // Assert
  ck_assert_ptr_eq(q_root, NULL);

  ck_assert_int_eq(error_code, UNBALANCED_BRACKETS);
  ck_assert_int_eq(q_node_1.token_type, q_root_node.token_type);
  ck_assert_int_eq(q_node_2.token_type, s_node_2.token_type);

  remove_struct(&s_head);
}
END_TEST

START_TEST(end_of_expression_OK) {
  // Arrange
  //         |      PLUS      |           |--------|----|--------|----
  // STACK:  |       \|/      |   QUEUE:  | NUMBER | -> | NUMBER | ->
  //         |____U_MINUS_____|           |--------|----|--------|----

  node_t* s_head = NULL;
  node_t s_node_1 = {NULL, U_MINUS, PRIOR_4, 0.0};
  node_t s_node_2 = {NULL, PLUS, PRIOR_2, 0.0};
  push(STACK, &s_head, &s_node_1);
  push(STACK, &s_head, &s_node_2);

  node_t q_node_1 = {NULL, NUMBER, PRIOR_1, 3.1415};
  node_t q_node_2 = {NULL, NUMBER, PRIOR_1, 11.8};
  node_t* q_root = NULL;
  push(QUEUE, &q_root, &q_node_1);
  node_t* q_head = q_root;
  push(QUEUE, &q_head, &q_node_2);

  // Act
  int error_code = end_of_expression_processing(&s_head, &q_head);
  node_t q_node_3 = {0};
  node_t q_node_4 = {0};
  pop(&q_root, &q_node_1);
  pop(&q_root, &q_node_2);
  pop(&q_root, &q_node_3);
  pop(&q_root, &q_node_4);

  // Assert
  ck_assert_ptr_eq(q_root, NULL);

  ck_assert_int_eq(error_code, OK);
  ck_assert_int_eq(q_node_3.token_type, s_node_2.token_type);
  ck_assert_int_eq(q_node_4.token_type, s_node_1.token_type);

  remove_struct(&s_head);
}
END_TEST

Suite* test_end_of_expression_processing(void) {
  Suite* s = suite_create("end_of_expression_processing function tests suite");

  TCase* end_of_expression_errors_tc =
      tcase_create("end_of_expression_processing errors");
  tcase_add_test(end_of_expression_errors_tc,
                 end_of_expression_error_UNBALANCED_BRACKETS);
  suite_add_tcase(s, end_of_expression_errors_tc);

  TCase* end_of_expression_tc = tcase_create("end_of_expression_processing OK");
  tcase_add_test(end_of_expression_tc, end_of_expression_OK);
  suite_add_tcase(s, end_of_expression_tc);

  return s;
}
