/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief the data adding to stack new node
/// @param address STACK or QUEUE structure
/// @param head head of structure
/// @param data
/// @return error code
int push(int address, node_t** head, node_t* data) {
  int error = OK;
  node_t* new_node_ptr = (node_t*)calloc(1, sizeof(node_t));
  if (new_node_ptr == NULL) {
    error = DATA_STRUCT_OVERFLOW;
  } else {
    if (address == STACK) new_node_ptr->next_node_ptr = *head;
    if (address == QUEUE && *head != NULL)
      (*head)->next_node_ptr = new_node_ptr;
    node_filling(data, new_node_ptr);
    *head = new_node_ptr;
  }
  return error;
}
