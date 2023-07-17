/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

/// @brief the data at the top of the stack removing and returning
/// @param head pointer to head node pointer of data structure
/// @param node pointer to node_t
/// @return error code
int pop(node_t** head, node_t* node) {
  if (*head == NULL) return DATA_STRUCT_UNDERFLOW;

  node->next_node_ptr = (*head)->next_node_ptr;
  node_filling(node, *head);
  free(*head);
  *head = node->next_node_ptr;
  return OK;
}
