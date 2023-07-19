/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

/// @brief reverse polish notation expression solving
/// @param q_root queue root pointer
/// @param variable variable value
/// @param result result of expression solving
/// @return error code (token_type with invalid argument + 100)
int expression_solver(node_t* q_root, double variable, double* result) {
  if (q_root == NULL) return EMPTY_QUEUE;
  int error = OK;
  node_t* s_head = NULL;
  token_t token_type = 0;

  while (!error && q_root) {
    token_type = q_root->token_type;
    if (token_type == NUMBER) {
      error = node_from_queue_to_stack(&q_root, &s_head);
    } else if (token_type == VAR) {
      q_root->token_value = variable;
      error = node_from_queue_to_stack(&q_root, &s_head);
    } else if (token_type < OPEN_BRACKET) {
      error = unary_solver(&s_head, q_root->token_type);
      node_removing(q_root);
    } else {  // binary operators
      error = binary_solver(&s_head, q_root->token_type);
      node_removing(q_root);
    }
  }
}

int unary_solver(node_t** s_head, token_t function_id) {
  double value = (*s_head)->token_value;
  if (function_id == ACOS && fabs(value) > 1) return ACOS + 100;
  if (function_id == ASIN && fabs(value) > 1) return ASIN + 100;
  if (function_id == LN && value <= 0) return LN + 100;
  if (function_id == LOG && value <= 0) return LOG + 100;
  if (function_id == SQRT && value < 0) return SQRT + 100;

  UNARY_FUNCTIONS_CALLING;
  (*s_head)->token_value = unary_functions[function_id](value);

  // if (function_id == COS) {
  //   error = cos_solver(s_head);
  // } else if (function_id == SIN) {
  //   error = sin_solver(s_head);
  // } else if (function_id == TAN) {
  //   error = tan_solver(s_head);
  // } else if (function_id == ACOS) {
  //   error = acos_solver(s_head);

  // }

  return OK;
}
