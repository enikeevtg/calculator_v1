/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief node removing from memory
/// @param phead structure head pointer
void remove_head_node(node_t** phead) {
  if (phead && *phead) {
    node_t* tmp = (*phead)->pnext;
    free(*phead);
    *phead = tmp;
  }
}
