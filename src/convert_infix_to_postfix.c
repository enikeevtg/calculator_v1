/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

int right_bracket_processing(int prev_address, node_t** s_head,
                             node_t** q_head);

int container_packing(int prev_address, node_t** s_head, char** str,
                      node_t* container_p);
int value_packer(char** str, node_t* container_p);
int operator_packer(int prev_address, node_t** s_head, char** str,
                    node_t* container_p);
int function_packer(char** str, node_t* container_p);

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
      // error_code = right_bracket_processing(s_head, q_head);
      current_str++;
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

int right_bracket_processing(int prev_address, node_t** s_head,
                             node_t** q_head) {
  if (prev_address == STACK && (*s_head)->token_type == OPEN_BRACKET)
    return EMPTY_BRACKETS;
  if (prev_address == STACK) return INCORRECT_INPUT;

  int error_code = OK;
  while (*s_head && (*s_head)->token_type != OPEN_BRACKET)
    node_from_stack_to_queue(s_head, q_head);
  if (*s_head != NULL) {
    node_removing(s_head);
  } else {
    error_code = UNBALANCED_BRACKETS;
  }
  if (error_code == OK && *s_head &&
      ((*s_head)->token_type == U_PLUS || (*s_head)->token_type == U_MINUS))
    node_from_stack_to_queue(s_head, q_head);

  return error_code;
}

int container_packing(int prev_address, node_t** s_head, char** str,
                      node_t* container_p) {
  int error_code = OK;

  NUMBERS_CHARS;
  OPERATORS_CHARS;
  // FUNCTIONS_FIRST_LETTERS;
  char token_symbol = **str;

  if (strchr(numbers_chars, token_symbol)) {
    error_code = value_packer(str, container_p);
  } else if (strchr(operators_chars, token_symbol)) {
    error_code = operator_packer(prev_address, s_head, str, container_p);
    *s_head = container_p;
  } else {  // functions case
    error_code = function_packer(str, container_p);
  }
  return error_code;
}

int value_packer(char** str, node_t* container_p) {
  int error_code = OK;

  container_p->token_type = NUMBER;
  sscanf(*str, "%lf", &(container_p->token_value));
  log_info("NUMBER: value = %lf", container_p->token_value);

  NUMBERS_CHARS;
  *str += strspn(*str, numbers_chars);
  return OK;
}

int operator_packer(int prev_address, node_t** s_head, char** str,
                    node_t* container_p) {
  int error_code = OK;

  char symb = **str;
  if (symb == '+' && prev_address == QUEUE) {
    container_p->token_type = PLUS;
    container_p->token_priority = PRIOR_2;
  } else if (symb == '-' && prev_address == QUEUE) {
    container_p->token_type = MINUS;
    container_p->token_priority = PRIOR_2;
  } else if (symb == '*' && prev_address == QUEUE) {
    container_p->token_type = MULT;
    container_p->token_priority = PRIOR_3;
  } else if (symb == '/' && prev_address == QUEUE) {
    container_p->token_type = DIV;
    container_p->token_priority = PRIOR_3;
  } else if (symb == '%' && prev_address == QUEUE) {
    container_p->token_type = MOD;
    container_p->token_priority = PRIOR_3;
  } else if (symb == '^' && prev_address == QUEUE) {
    container_p->token_type = POW;
    container_p->token_priority = PRIOR_4;
  } else if (symb == '+' && prev_address == STACK &&
             (*s_head == NULL || (*s_head)->token_type == OPEN_BRACKET ||
              (*s_head)->token_type == POW)) {  // because 1^-2 is correct
    container_p->token_type = U_PLUS;
    container_p->token_priority = PRIOR_5;
  } else if (symb == '-' && prev_address == STACK &&
             (*s_head == NULL || (*s_head)->token_type == OPEN_BRACKET ||
              (*s_head)->token_type == POW)) {  // because 1^-2 is correct
    container_p->token_type = U_MINUS;
    container_p->token_priority = PRIOR_5;
  } else if (symb == '(') {
    container_p->token_type = OPEN_BRACKET;
    container_p->token_priority = PRIOR_1;
  } else {
    error_code = INCORRECT_INPUT;
  }
  *str += 1;
  log_info("OPERATOR: operator_id is %d \'%c\'", container_p->token_type, symb);

  return error_code;
}

int function_packer(char** str, node_t* container_p) {
  int error_code = OK;

  FUNCTIONS_NAMES;
  char* char_after_function_ptr = strpbrk(*str, "(1234567890x");
  char char_after_function = *char_after_function_ptr;
  *char_after_function_ptr = '\0';

  int func_id = 0;
  while (func_id < FUNCTIONS_NUMBER && strcmp(*str, functions_names[func_id]))
    func_id++;
  if (func_id == FUNCTIONS_NUMBER) {
    error_code = UNDEFINED_TOKEN;
  } else {
    log_info("FUNCTION: func_id is %d \'%s\'", func_id, *str);
    container_p->token_type = func_id;
    container_p->token_priority = PRIOR_5;
    *char_after_function_ptr = char_after_function;
    *str = char_after_function_ptr;
  }
  return error_code;
}
