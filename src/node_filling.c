/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

/// @brief filling dest node by src node data
/// @version v.1
/// @param dest
/// @param src
void node_filling(node_t* src, node_t* dest) {
  dest->token_type = src->token_type;
  dest->token_priority = src->token_priority;
  dest->token_value = src->token_value;
}

/// @brief filling dest node by src node data depend on data structure
/// @version v.2
/// @param dest
/// @param src
void node_filling_v2(int struct_type, node_t** head, node_t* src,
                     node_t* dest) {
  if (struct_type == STACK) dest->next_node_ptr = *head;
  if (struct_type == QUEUE) (*head)->next_node_ptr = dest;

  dest->token_type = src->token_type;
  dest->token_priority = src->token_priority;
  dest->token_value = src->token_value;

  *head = dest;
}
