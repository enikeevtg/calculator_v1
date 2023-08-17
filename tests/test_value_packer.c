#include "tests.h"

START_TEST(value_packer_pos_NUMBER) {
  // Arrange
  char str[11] = "123.456";
  char* current_str = str;
  node_t container = {0};

  // Act
  value_packer(&current_str, &container);

  // Assert
  ck_assert_int_eq(container.token_type, NUMBER);
  ck_assert_int_eq(container.token_value, 123.456);
}
END_TEST

START_TEST(value_packer_neg_NUMBER) {
  // Arrange
  char str[11] = "-123.456";
  char* current_str = str;
  node_t container = {0};

  // Act
  value_packer(&current_str, &container);

  // Assert
  ck_assert_int_eq(container.token_type, NUMBER);
  ck_assert_int_eq(container.token_value, -123.456);
}
END_TEST

START_TEST(value_packer_incorrect_NUMBER) {
  // Arrange
  char str[21] = "123.456.789";
  char* current_str = str;
  node_t container = {0};

  // Act
  value_packer(&current_str, &container);

  // Assert
  ck_assert_int_eq(container.token_type, NUMBER);
  ck_assert_int_eq(container.token_value, 123.456);
}
END_TEST

Suite* test_value_packer(void) {
  Suite* s = suite_create("value_packer function tests suite");

  TCase* value_packer_tc = tcase_create("value_packer OK");
  tcase_add_test(value_packer_tc, value_packer_pos_NUMBER);
  tcase_add_test(value_packer_tc, value_packer_neg_NUMBER);
  tcase_add_test(value_packer_tc, value_packer_incorrect_NUMBER);
  suite_add_tcase(s, value_packer_tc);

  return s;
}
