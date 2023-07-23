/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief 
/// @version v.2
/// @param struct_type 
/// @param phead 
/// @param src 
/// @param dest 
void fill_node_v2(int struct_type, node_t** phead, node_t* src,
                     node_t* dest) {
  if (struct_type == STACK) dest->next_node_ptr = *phead;
  if (struct_type == QUEUE) (*phead)->next_node_ptr = dest;

  dest->token_type = src->token_type;
  dest->token_priority = src->token_priority;
  dest->token_value = src->token_value;

  *phead = dest;
}
