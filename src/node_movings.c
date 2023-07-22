/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

int drag_and_drop(int address, node_t** src_head, node_t** dest_head);

int move_node_from_stack_to_queue(node_t** s_head, node_t** q_head) {
  return drag_and_drop(QUEUE, s_head, q_head);
}

int move_node_from_queue_to_stack(node_t** q_head, node_t** s_head) {
  return drag_and_drop(STACK, q_head, s_head);
}

/// @brief the data at the top of the one data structure removing and returning
/// it to another data structure
/// @param dest_head pointer to head node pointer of
/// @param src_head pointer to head node pointer of
/// @return error code
int drag_and_drop(int address, node_t** src_head, node_t** dest_head) {
  if (*src_head == NULL) return DATA_STRUCT_UNDERFLOW;

  int error = push(address, dest_head, *src_head);
  remove_head_node(src_head);

  return error;
}
