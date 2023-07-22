/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

/// @brief data struct removing from memory
/// @param head stack head (or queue root) pointer
void remove_struct(node_t** head) {
  if (head) {
    while (*head) {
      remove_head_node(head);
    }
  }
}
