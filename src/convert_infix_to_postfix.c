/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

int right_bracket_processing(node_t** s_head, node_t** q_head);

int container_packing(int prev_address, node_t** s_head, char** str,
                      node_t* container);
int value_packer(char** str, node_t* container);
int operator_packer(int prev_address, node_t** s_head, char** str,
                    node_t* container);
// int function_packer(char* dest, char** function);

/// @brief
/// @param str
/// @param s_head
/// @param q_head
/// @return
int convert_infix_to_postfix(const char* str, node_t** s_head,
                             node_t** q_head) {
  int error_code = OK;

  TOKEN_CHARS;
  NUMBERS_CHARS;

  node_t container = {0};
  char* current_str = (char*)str;
  int address = STACK;

  while (!(*current_str == '\0' && *s_head == NULL) && !error_code) {
    if (*current_str == ')') {
      log_info("closing bracket detected");

      // if (address == STACK) {
      //   error_code = EMPTY_BRACKETS;
      // } else {
      //   error_code = right_bracket_processing(s_head, q_head);
      current_str++;
      // }
    } else if (*current_str == '\0') {
      // while (*s_head != NULL) node_from_stack_to_queue(s_head, q_head);
      log_info("end of string detected");
      *s_head = NULL;
    } else if (*current_str == ' ') {
      log_info("space detected");
      current_str++;
    } else if (strchr(token_chars, *current_str)) {
      error_code = container_packing(address, s_head, &current_str, &container);
      if (strchr(numbers_chars, *current_str)) address = QUEUE;
    } else {
      error_code = UNDEFINED_TOKEN;
      log_info("UNDEFINED_TOKEN detected: %c", *current_str);
    }
  }
}

int right_bracket_processing(node_t** s_head, node_t** q_head) {
  int error_code = OK;
  while (*s_head && (*s_head)->token_type < OPEN_BRACKET)
    node_from_stack_to_queue(s_head, q_head);
  if (*s_head) {
    node_removing(s_head);
  } else {
    error_code = UNBALANCED_BRACKETS;
  }
  return error_code;
}

int container_packing(int prev_address, node_t** s_head, char** str,
                      node_t* container) {
  int error_code = OK;

  NUMBERS_CHARS;
  OPERATORS_CHARS;
  // FUNCTIONS_FIRST_LATTERS;
  char token_symbol = **str;

  if (strchr(numbers_chars, token_symbol)) {
    error_code = value_packer(str, container);
  } else if (strchr(operators_chars, token_symbol)) {
    error_code = operator_packer(prev_address, s_head, str, container);
    (*s_head) = container;
  } else {  // functions case
    log_info("FUNCTION");

    (*str)++;
    error_code = 0;
  }

  return error_code;
}

int value_packer(char** str, node_t* container) {
  int error_code = OK;

  container->token_type = NUMBER;
  sscanf(*str, "%lf", &(container->token_value));

  NUMBERS_CHARS;
  size_t number_length = strspn(*str, numbers_chars);
  *str += number_length;

  log_info("NUMBER: value = %lf", number_length, container->token_value);

  return OK;
}

int operator_packer(int prev_address, node_t** s_head, char** str,
                    node_t* container) {
  int error_code = OK;

  char symb = **str;
  if (symb == '+') {
    if (prev_address == QUEUE) {
      container->token_type = PLUS;
      container->token_priority = PRIOR_2;
    } else if (prev_address == STACK &&
               ((*s_head)->next_node_ptr == NULL ||
                (*s_head)->token_type == OPEN_BRACKET)) {
      container->token_type = U_PLUS;
      container->token_priority = PRIOR_4;
    } else {
      error_code = OPERATORS_INPUT_ERROR;
    }
  } else if (symb == '-') {
    if (prev_address == QUEUE) {
      container->token_type = MINUS;
      container->token_priority = PRIOR_2;
    } else if (prev_address == STACK &&
               ((*s_head)->next_node_ptr == NULL ||
                (*s_head)->token_type == OPEN_BRACKET)) {
      container->token_type = U_MINUS;
      container->token_priority = PRIOR_4;
    } else {
      error_code = OPERATORS_INPUT_ERROR;
    }
  } else if (symb == '*') {
    container->token_type = MULT;
    container->token_priority = PRIOR_3;
  } else if (symb == '/') {
    container->token_type = DIV;
    container->token_priority = PRIOR_3;
  } else if (symb == '%') {
    container->token_type = MOD;
    container->token_priority = PRIOR_3;
  } else if (symb == '^') {
    container->token_type = POW;
    container->token_priority = PRIOR_4;
  } else if (symb == '(') {
    container->token_type = OPEN_BRACKET;
    container->token_priority = PRIOR_1;
  }
  *str += 1;
  log_info("OPERATOR: operator_code is %d", container->token_type);

  return error_code;
}
