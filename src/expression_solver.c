/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

double u_plus(double value_2);
double u_minus(double value_2);
double add_calc(double value_1, double value_2);
double sub_calc(double value_1, double value_2);
double mult_calc(double value_1, double value_2);
double div_calc(double value_1, double value_2);
double mod_calc(double value_1, double value_2);
double pow_calc(double value_1, double value_2);

/// @brief reverse polish notation expression solving
/// @param q_root queue root pointer
/// @param variable variable value_2
/// @param result result of expression solving
/// @return error code (token_type with invalid argument + 100)
int expression_solver(node_t* q_root, double variable, double* result) {
  if (q_root == NULL) return EMPTY_QUEUE;
  int error = OK;
  node_t* s_head = NULL;
  token_t token_type = 0;

  int i = 0;
  while (!error && q_root) {
    token_type = q_root->token_type;
    if (token_type == NUMBER) {
      error = node_from_queue_to_stack(&q_root, &s_head);
    } else if (token_type == VAR) {
      q_root->token_value = variable;
      error = node_from_queue_to_stack(&q_root, &s_head);
    } else {
      error = numerical_calculation(&s_head, q_root->token_type);
      node_removing(&q_root);
    }
    log_info("#%d: %lf", i++, s_head->token_value);
  }
  if (error) {
    log_info("ERROR %d", error);
    struct_removing(&s_head);
    struct_removing(&q_root);
  } else {
    *result = s_head->token_value; 
  }
  return error;
}

int numerical_calculation(node_t** s_head, token_t function_id) {
  double value_2 = (*s_head)->token_value;
  if (function_id == ACOS && fabs(value_2) > 1) return ACOS + 100;
  if (function_id == ASIN && fabs(value_2) > 1) return ASIN + 100;
  if (function_id == LN && value_2 <= 0) return LN + 100;
  if (function_id == LOG && value_2 <= 0) return LOG + 100;
  if (function_id == SQRT && value_2 < 0) return SQRT + 100;

  C_FUNCTIONS_POINTERS;
  if (function_id < OPEN_BRACKET) {
    // unary functions:
    (*s_head)->token_value = c_functions[function_id](value_2);
  } else {
    // binary functions:
    function_id--;  // because OPEN_BRACKET c_function not exist
    node_removing(s_head);
    double value_1 = (*s_head)->token_value;
    (*s_head)->token_value = c_functions[function_id](value_1, value_2);
  }

  // if (function_id == COS) {
  //   error = cos_solver(s_head);
  // } else if (function_id == SIN) {
  //   error = sin_solver(s_head);
  // } else if (function_id == TAN) {
  //   error = tan_solver(s_head);
  // } else if (function_id == ACOS) {
  //   error = acos_solver(s_head);

  // }

  return OK;
}

double u_plus(double value_2) { return value_2; }

double u_minus(double value_2) { return -value_2; }

double add_calc(double value_1, double value_2) { return value_1 + value_2; }

double sub_calc(double value_1, double value_2) { return value_1 - value_2; }

double mult_calc(double value_1, double value_2) { return value_1 * value_2; }

double div_calc(double value_1, double value_2) { return value_1 / value_2; }

double mod_calc(double value_1, double value_2) {
  return (double)((int)value_1 * (int)value_2);
}

double pow_calc(double value_1, double value_2) { return pow_calc(value_1, value_2); }
