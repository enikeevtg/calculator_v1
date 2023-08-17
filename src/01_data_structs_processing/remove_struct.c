/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief data struct removing from memory
/// @param phead stack head (or queue root) pointer
void remove_struct(node_t** phead) {
  if (phead) {
    while (*phead) {
      remove_head_node(phead);
    }
  }
}
