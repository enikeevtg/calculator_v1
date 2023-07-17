/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

/// @brief data struct removing from memory
/// @param head stack head (or queue root) pointer
void struct_removing(node_t** head) {
  if (head) {
    while (*head) {
      node_removing(head);
    }
  }
}
