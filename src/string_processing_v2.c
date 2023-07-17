/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

int right_bracket(node_t** s_head, node_t** q_head);
int value_to_str(char* dest, char** number);
int function_to_str(char* dest, char** function);

int string_processing(const char* str, node_t** s_head, node_t** q_head) {
  int error_code = OK;

  const char operators[] = "+-*/()^%";
  const char functions_first_letters[] = "cstal";
  const char numbers[] = "1234567890.";

  node_t container = {0};
  char* current_str = (char*)str;
  int address = STACK;

  int token_index = 0;
  while (!(*current_str == '\0' && *s_head == NULL) && !error_code) {
    if (*current_str == ')') {
      error_code = right_bracket(s_head, q_head);
    } else if (*current_str == '\0') {
      while (*s_head) node_from_stack_to_queue(s_head, q_head);
    } else if (*current_str == ' ') {
      current_str++;
    } else if (strchr(functions_first_letters, *current_str)) {
    } else {
      error_code = UNDEFINED_TOKEN;
    }
  }
}

int right_bracket(node_t** s_head, node_t** q_head) {
  int error_code = OK;
  while (*s_head && (*s_head)->token_type != LEFT_BRACKET)
    node_from_stack_to_queue(s_head, q_head);
  if (*s_head) {
    node_removing(s_head);
  } else {
    error_code = UNBALANCED_BRACKETS;
  }
  return error_code;
}
