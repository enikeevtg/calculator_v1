/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

/// @brief node removing from memory
/// @param head structure head pointer
void node_removing(node_t** head) {
  if (head && *head) {
    node_t* tmp = (*head)->next_node_ptr;
    free(*head);
    *head = tmp;
  }
}
