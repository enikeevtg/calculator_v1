/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

/// @brief the data adding to stack function
/// @param stack_head pointer to head node pointer of stack
/// @param data data for new node of stack
/// @return error code
int stack_push(stack_node_t** stack_head, stack_node_t* data) {
  int error_code = OK;
  stack_node_t* new_node_ptr = (stack_node_t*)calloc(1, sizeof(stack_node_t));
  if (new_node_ptr == NULL) {
    error_code = STACK_OVERFLOW;
  } else {
    new_node_ptr->prev_node = *stack_head;
    new_node_ptr->token_type = data->token_type;
    new_node_ptr->token_priority = data->token_priority;
    new_node_ptr->token_value = data->token_value;
    *stack_head = new_node_ptr;
  }
  return error_code;
}
