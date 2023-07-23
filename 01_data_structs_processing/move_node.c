/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

int drag_and_drop(int address, node_t** src_phead, node_t** dest_phead);

int move_node_from_stack_to_queue(node_t** s_phead, node_t** q_phead) {
  return drag_and_drop(QUEUE, s_phead, q_phead);
}

int move_node_from_queue_to_stack(node_t** q_phead, node_t** s_phead) {
  return drag_and_drop(STACK, q_phead, s_phead);
}

/// @brief the data at the top of the one data structure removing and returning
/// it to another data structure
/// @param dest_phead pointer to head node pointer of
/// @param src_phead pointer to head node pointer of
/// @return error code
int drag_and_drop(int address, node_t** src_phead, node_t** dest_phead) {
  if (*src_phead == NULL) return DATA_STRUCT_UNDERFLOW;

  int error = push(address, dest_phead, *src_phead);
  remove_head_node(src_phead);

  return error;
}
