/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief
/// @param paddress
/// @param current_str
/// @param s_phead
/// @param q_phead
/// @param pcontainer
/// @return
int token_processing(int* paddress, char** current_str, node_t** s_phead,
                     node_t** q_phead, node_t* pcontainer) {
  int error = OK;

  error = container_packing(*paddress, current_str, s_phead, pcontainer);
  if (error == OK) {
    error = container_sending(paddress, s_phead, q_phead, pcontainer);
  }
  return error;
}
