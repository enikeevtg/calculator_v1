/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief
/// @param s_head
/// @param function_id
/// @return
int numerical_calculation(node_t** s_head, token_t function_id) {
  double value_2 = (*s_head)->token_value;
  if (function_id == ACOS && fabs(value_2) > 1) return ACOS_ERROR;
  if (function_id == ASIN && fabs(value_2) > 1) return ASIN_ERROR;
  if (function_id == LN && value_2 <= 0) return LN_ERROR;
  if (function_id == LOG && value_2 <= 0) return LOG_ERROR;
  if (function_id == SQRT && value_2 < 0) return SQRT_ERROR;

  CALC_FUNCTIONS_POINTERS;
  if (function_id < OPEN_BRACKET) {
    // unary functions:
    (*s_head)->token_value = calc_functions[function_id](value_2);
  } else {
    // binary functions:
    function_id--;  // because calc_function == open_bracket does not exist
    remove_head_node(s_head);
    double value_1 = (*s_head)->token_value;
    (*s_head)->token_value = calc_functions[function_id](value_1, value_2);
  }
  return OK;
}

double u_plus(double value) { return value; }

double u_minus(double value) { return -value; }

double add_calc(double value_1, double value_2) { return value_1 + value_2; }

double sub_calc(double value_1, double value_2) { return value_1 - value_2; }

double mult_calc(double value_1, double value_2) { return value_1 * value_2; }

double div_calc(double value_1, double value_2) { return value_1 / value_2; }

double pow_calc(double value_1, double value_2) {
  return pow(value_1, value_2);
}
