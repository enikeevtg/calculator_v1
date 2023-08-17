/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief filling dest node by src node data
/// @version v.1
/// @param dest
/// @param src
void fill_node(node_t* src, node_t* dest) {
  dest->token_type = src->token_type;
  dest->token_priority = src->token_priority;
  dest->token_value = src->token_value;
}
