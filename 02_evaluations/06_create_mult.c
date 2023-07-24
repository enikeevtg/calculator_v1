/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief
/// @param prev_address
/// @param s_phead
/// @param pcontainer
void create_mult(int prev_address, node_t** s_phead, node_t* pcontainer) {
  char* mult_char_str = "*";
  operator_packer(prev_address, &mult_char_str, s_phead, pcontainer);
}
