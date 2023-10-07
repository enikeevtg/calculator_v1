/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief
/// @param s_phead
/// @param q_phead
void move_node_from_stack_to_queue(node_t** s_phead, node_t** q_phead) {
  if (*q_phead != NULL) {
    (*q_phead)->pnext = *s_phead;
    *q_phead = (*q_phead)->pnext;
  } else {
    *q_phead = *s_phead;
  }
  *s_phead = (*s_phead)->pnext;
  (*q_phead)->pnext = NULL;
}

/// @brief
/// @param q_phead
/// @param s_phead
void move_node_from_queue_to_stack(node_t** q_proot, node_t** s_phead) {
  node_t* tmp_node = (*q_proot)->pnext;
  (*q_proot)->pnext = *s_phead;
  *s_phead = *q_proot;
  *q_proot = tmp_node;
}
