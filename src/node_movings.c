/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

int node_drag_and_drop(int dest_type, node_t** dest_head, node_t** src_head);

int node_from_stack_to_queue(node_t** s_head, node_t** q_head) {
  return node_drag_and_drop(QUEUE, q_head, s_head);
}

int node_from_queue_to_stack(node_t** q_head, node_t** s_head) {
  return node_drag_and_drop(STACK, s_head, q_head);
}

/// @brief the data at the top of the one data structure removing and returning
/// it to another data structure
/// @param dest_head pointer to head node pointer of
/// @param src_head pointer to head node pointer of
/// @return error code
int node_drag_and_drop(int dest_type, node_t** dest_head, node_t** src_head) {
  if (*src_head == NULL) return DATA_STRUCT_UNDERFLOW;

  int error_code = push(dest_type, dest_head, *src_head);
  node_t* tmp_node = *src_head;
  free(*src_head);
  *src_head = tmp_node;

  return error_code;
}
