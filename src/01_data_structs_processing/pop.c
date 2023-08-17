/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief the data at the top of the stack removing and returning
/// @param phead pointer to s_head node pointer of data structure
/// @param pnode pointer to node_t
/// @return error code
int pop(node_t** phead, node_t* pnode) {
  if (*phead == NULL) return DATA_STRUCT_UNDERFLOW;

  fill_node(*phead, pnode);
  remove_head_node(phead);
  return OK;
}
