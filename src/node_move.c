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
int node_move(int dest_struct_type, node_t** dest_head, node_t** src_head) {
  if (*src_head == NULL) return DATA_STRUCT_UNDERFLOW;
 
  int error_code = push(dest_struct_type, dest_head, *src_head);
  node_t* tmp_node = *src_head;
  free(*src_head);
  *src_head = tmp_node;

  return error_code;
}
