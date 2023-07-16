/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

/// @brief the data at the top of the stack removing and returning function
/// @param stack_head pointer to head node pointer of stack
/// @param node pointer to stack_node_t
/// @return error code
int stack_pop(stack_node_t** stack_head, stack_node_t* node) {
  if (*stack_head == NULL) return STACK_UNDERFLOW;
  
  node->token_type = (*stack_head)->token_type;
  node->token_priority = (*stack_head)->token_priority;
  node->token_value = (*stack_head)->token_value;
  free(*stack_head);
  *stack_head = (*stack_head)->prev_node;
  return OK;
}
