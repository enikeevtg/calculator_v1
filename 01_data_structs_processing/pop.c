/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief the data at the top of the stack removing and returning
/// @param s_head pointer to s_head node pointer of data structure
/// @param node pointer to node_t
/// @return error code
int pop(node_t** s_head, node_t* node) {
  if (*s_head == NULL) return DATA_STRUCT_UNDERFLOW;

  // node->next_node_ptr = (*s_head)->next_node_ptr;
  node_filling(*s_head, node);
  remove_head_node(s_head);
  // free(*s_head);
  // *s_head = node->next_node_ptr;
  return OK;
}
