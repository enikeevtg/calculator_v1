/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

/// @brief the data at the top of the stack removing and returning it to queue
/// function
/// @param stack_head pointer to head node pointer of stack
/// @param queue_head pointer to head node pointer of queue
/// @return error code
int stack_to_queue(stack_node_t** stack_head, queue_node_t** queue_head) {
  int error_code = OK;
  queue_node_t* new_q_node_ptr = (queue_node_t*)calloc(1, sizeof(queue_node_t));
  if (new_q_node_ptr == NULL) {
    error_code = QUEUE_OVERFLOW;
  } else {
    stack_pop(stack_head, new_q_node_ptr);
    (*queue_head)->next_node = new_q_node_ptr;
    *queue_head = new_q_node_ptr;
  }
  return error_code;
}
