/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief node removing from memory
/// @param head structure head pointer
void remove_head_node(node_t** head) {
  if (head && *head) {
    // printf("stack node %p removing\n", *head);
    node_t* tmp = (*head)->next_node_ptr;
    free(*head);
    *head = tmp;
    // printf("next node is %p\n", *head);
  }
}
