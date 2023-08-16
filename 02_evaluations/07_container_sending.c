/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief
/// @param paddress
/// @param s_phead
/// @param q_phead
/// @param pcontainer
/// @return
int container_sending(int* paddress, node_t** s_phead, node_t** q_phead,
                      node_t* pcontainer) {
  int error = OK;
  *paddress = STACK;
  if (pcontainer->token_type <= OPEN_BRACKET) {  // functions and '('
    error = push(STACK, s_phead, pcontainer);

  } else if (pcontainer->token_type < POW) {  // left-associative operators
    while (*s_phead != NULL &&
           pcontainer->token_priority <= (*s_phead)->token_priority) {
      move_node_from_stack_to_queue(s_phead, q_phead);
    }
    if (!error) error = push(*paddress, s_phead, pcontainer);

  } else if (pcontainer->token_type == POW) {  // right-associative POW
    error = push(STACK, s_phead, pcontainer);

  } else {  // NUMBER or VAR
    error = push(QUEUE, q_phead, pcontainer);
    *paddress = QUEUE;
  }
  return error;
}
