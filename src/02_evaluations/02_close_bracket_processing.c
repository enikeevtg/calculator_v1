/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief
/// @param prev_address
/// @param s_phead
/// @param q_phead
/// @return
int close_bracket_processing(int prev_address, node_t** s_phead,
                             node_t** q_phead) {
  if (prev_address == STACK && (*s_phead)->token_type == OPEN_BRACKET)
    return EMPTY_BRACKETS;
  if (prev_address == STACK) return INCORRECT_INPUT;

  while (*s_phead && (*s_phead)->token_type != OPEN_BRACKET) {
    move_node_from_stack_to_queue(s_phead, q_phead);
  }

  int error = OK;
  if (*s_phead == NULL) {
    error = UNBALANCED_BRACKETS;
  } else {
    remove_head_node(s_phead);
    // if function before open bracket
    if (*s_phead && (*s_phead)->token_type < OPEN_BRACKET) {
      move_node_from_stack_to_queue(s_phead, q_phead);
    }
  }

  return error;
}
