/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief reverse polish notation expression solving
/// @param q_root queue root pointer
/// @param variable variable value_2
/// @param result result of expression solving
/// @return error code (token_type with invalid argument + 100)
int evaluate_expression(node_t* q_root, double* result) {
  if (q_root == NULL) return EMPTY_QUEUE;
  int error = OK;
  node_t* s_head = NULL;

  while (!error && q_root) {
    if (q_root->token_type == NUMBER) {
      move_node_from_queue_to_stack(&q_root, &s_head);
    } else {
      error = numerical_calculation(&s_head, q_root->token_type);
      remove_head_node(&q_root);
    }
  }
  if (error) {
    remove_struct(&s_head);
    remove_struct(&q_root);
  } else {
    *result = s_head->token_value;
    remove_struct(&s_head);
  }
  return error;
}
