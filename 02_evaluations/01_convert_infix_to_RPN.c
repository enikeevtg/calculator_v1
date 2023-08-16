/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief converting from infix notation to reverse Polish notation
/// @param str
/// @param q_proot queue root pointer pointer.
/// When function is doing it is redefined to queue head,
/// but in the end of function it is redefined to queue node root pointer
/// @return error code
int convert_infix_to_RPN(const char* str, node_t** q_proot) {
  if (strlen(str) > MAX_INPUT_STR_LEN) return TOO_LONG_EXPRESSION;
  if (strlen(str) == 0) return EMPTY_EXPRESSION;

  int error = OK;
  char* current_str = (char*)str;
  node_t* s_head = NULL;
  node_t* q_root = NULL;
  int address = STACK;
  node_t container = {.pnext = NULL,
                      .token_type = (token_t)0,
                      .token_priority = (token_p)0,
                      .token_value = 0.0};
  const char token_chars[] = "1234567890.+-*/^%(cstal";

  while (!error && !(*current_str == '\0' && s_head == NULL)) {
    if (*current_str == ')') {
      container.token_type = CLOSE_BRACKET;
      error = close_bracket_processing(address, &s_head, q_proot);
      current_str++;
    } else if (*current_str == '\0' && address != STACK) {
      error = end_of_expression_processing(&s_head, q_proot);
    } else if (*current_str == '\0' && address == STACK) {
      error = INCORRECT_INPUT;
    } else if (*current_str == ' ') {
      current_str++;
    } else if (strchr(token_chars, *current_str)) {
      error = token_processing(&address, &current_str, &s_head, q_proot,
                               &container);
    } else {
      error = UNDEFINED_TOKEN;
    }
    if (q_root == NULL) q_root = *q_proot;
  }  // while

  if (error != OK) {
    remove_struct(&s_head);
    remove_struct(&q_root);
  }
  *q_proot = q_root;
  return error;
}
