/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief
/// @param prev_address
/// @param str
/// @param s_phead
/// @param pcontainer
/// @return
int container_packing(int prev_address, char** str, node_t** s_phead,
                      node_t* pcontainer) {
  int error = OK;

  const char numbers_chars[] = "1234567890.";
  const char operators_chars[] = "+-*/^%()";
  char token_symbol = **str;

  if (strchr(numbers_chars, token_symbol)) {
    if (prev_address == QUEUE && pcontainer->token_type != CLOSE_BRACKET) {
      error = INCORRECT_INPUT;
    } else if (prev_address == QUEUE &&
               pcontainer->token_type == CLOSE_BRACKET) {  // )NUM -> )*NUM
      create_mult(prev_address, s_phead, pcontainer);
    } else {
      error = value_packer(str, pcontainer);
    }

  } else if (strchr(operators_chars, token_symbol)) {
    error = operator_packer(prev_address, str, s_phead, pcontainer);

  } else {  // functions case
    if (prev_address == QUEUE || pcontainer->token_type == CLOSE_BRACKET) {
      create_mult(prev_address, s_phead, pcontainer);
    } else {
      error = function_packer(str, pcontainer);
    }
  }
  return error;
}

/// @brief
/// @param str
/// @param pcontainer
/// @return
int value_packer(char** str, node_t* pcontainer) {
  pcontainer->token_type = NUMBER;
  sscanf(*str, "%lf", &(pcontainer->token_value));
  const char numbers_chars[] = "1234567890";
  *str += strspn(*str, numbers_chars);
  if (**str == '.') {
    *str += 1;
    *str += strspn(*str, numbers_chars);
  }
  return OK;
}

/// @brief
/// @param prev_address
/// @param s_phead
/// @param str
/// @param pcontainer
/// @return
int operator_packer(int prev_address, char** str, node_t** s_phead,
                    node_t* pcontainer) {
  int error = OK;
  char symb = **str;
  if (symb == '+' && prev_address == QUEUE) {
    node_t tmp_node = {NULL, PLUS, PRIOR_2, 0};
    fill_node(&tmp_node, pcontainer);
  } else if (symb == '-' && prev_address == QUEUE) {
    node_t tmp_node = {NULL, MINUS, PRIOR_2, 0};
    fill_node(&tmp_node, pcontainer);
  } else if (symb == '*' && prev_address == QUEUE) {
    node_t tmp_node = {NULL, MULT, PRIOR_3, 0};
    fill_node(&tmp_node, pcontainer);
  } else if (symb == '/' && prev_address == QUEUE) {
    node_t tmp_node = {NULL, DIV, PRIOR_3, 0};
    fill_node(&tmp_node, pcontainer);
  } else if (symb == '%' && prev_address == QUEUE) {
    node_t tmp_node = {NULL, MOD, PRIOR_3, 0};
    fill_node(&tmp_node, pcontainer);
  } else if (symb == '^' && prev_address == QUEUE) {
    node_t tmp_node = {NULL, POW, PRIOR_3, 0};
    fill_node(&tmp_node, pcontainer);
  } else if (symb == '+' && prev_address == STACK &&
             (*s_phead == NULL || (*s_phead)->token_type == OPEN_BRACKET ||
              (*s_phead)->token_type == POW)) {  // because 1^-2 is correct
    node_t tmp_node = {NULL, U_PLUS, PRIOR_4, 0};
    fill_node(&tmp_node, pcontainer);
  } else if (symb == '-' && prev_address == STACK &&
             (*s_phead == NULL || (*s_phead)->token_type == OPEN_BRACKET ||
              (*s_phead)->token_type == POW)) {  // because 1^-2 is correct
    node_t tmp_node = {NULL, U_MINUS, PRIOR_4, 0};
    fill_node(&tmp_node, pcontainer);
  } else if (symb == '(' && prev_address == QUEUE) {  // NUM( -> NUM*(
    create_mult(prev_address, s_phead, pcontainer);
    *str -= 1;
  } else if (symb == '(' && prev_address == STACK) {
    node_t tmp_node = {NULL, OPEN_BRACKET, PRIOR_1, 0};
    fill_node(&tmp_node, pcontainer);
  } else {
    error = INCORRECT_INPUT;
  }
  *str += 1;
  return error;
}

/// @brief
/// @param str
/// @param pcontainer
/// @return
int function_packer(char** str, node_t* pcontainer) {
  int error = OK;
  char* bracket = strchr(*str, '(');
  char* after_function_char_ptr = strpbrk(*str, "()1234567890.+-*/^%");
  if (bracket == NULL || bracket > after_function_char_ptr)
    error = INCORRECT_INPUT;

  MATH_FUNCTIONS_NAMES;
  char after_function_char = '\0';
  if (after_function_char_ptr != NULL) {
    after_function_char = *after_function_char_ptr;
    *after_function_char_ptr = '\0';
  }
  int func_id = 0;
  while (func_id < MATH_FUNCTIONS_NUMBER &&
         strcmp(*str, math_functions_names[func_id]))
    func_id++;
  if (func_id == MATH_FUNCTIONS_NUMBER) {
    error = UNDEFINED_TOKEN;
  } else {
    pcontainer->token_type = func_id;
    pcontainer->token_priority = PRIOR_4;
    if (after_function_char_ptr != NULL)
      *after_function_char_ptr = after_function_char;
    *str = after_function_char_ptr;
  }
  return error;
}
