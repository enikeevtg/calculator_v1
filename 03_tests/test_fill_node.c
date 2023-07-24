#include "tests.h"

START_TEST(fill_node_COS) {
  // Arrange
  node_t node_src = {NULL, COS, PRIOR_4, 0.0};
  node_t node_dest = {0};
  // Act
  fill_node(&node_src, &node_dest);
  // Assert
  ck_assert_int_eq(node_src.token_type, node_dest.token_type);
  ck_assert_int_eq(node_src.token_priority, node_dest.token_priority);
  ck_assert_int_eq(node_src.token_value, node_dest.token_value);
}
END_TEST

START_TEST(fill_node_NUMBER) {
  // Arrange
  node_t node_src = {NULL, NUMBER, PRIOR_1, 987.0};
  node_t node_dest = {0};
  // Act
  fill_node(&node_src, &node_dest);
  // Assert
  ck_assert_int_eq(node_src.token_type, node_dest.token_type);
  ck_assert_int_eq(node_src.token_priority, node_dest.token_priority);
  ck_assert_int_eq(node_src.token_value, node_dest.token_value);
}
END_TEST

Suite* test_fill_node(void) {
  Suite* s = suite_create("fill node tests suite");

  TCase* fill_node_tc = tcase_create("fill node");
  tcase_add_test(fill_node_tc, fill_node_COS);
  tcase_add_test(fill_node_tc, fill_node_NUMBER);
  suite_add_tcase(s, fill_node_tc);

  return s;
}
