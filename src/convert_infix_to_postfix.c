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
void operator_package_filling(token_t type, token_p priority,
                              node_t** container_pp);
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
  if ((*s_head)->token_type >= OPEN_BRACKET) {
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
    (*s_head) = container_p;
  } else {  // functions case
    log_info("FUNCTION");

    (*str)++;
    error_code = 0;
  }

  return error_code;
}

int value_packer(char** str, node_t* container_p) {
  int error_code = OK;

  container_p->token_type = NUMBER;
  sscanf(*str, "%lf", &(container_p->token_value));

  NUMBERS_CHARS;
  size_t number_length = strspn(*str, numbers_chars);
  *str += number_length;

  log_info("NUMBER: value = %lf", number_length, container_p->token_value);

  return OK;
}

int operator_packer(int prev_address, node_t** s_head, char** str,
                    node_t* container_p) {
  int error_code = OK;

  char symb = **str;
  if (symb == '+' && prev_address == QUEUE) {
    operator_package_filling(PLUS, PRIOR_2, &container_p);
  } else if (symb == '-' && prev_address == QUEUE) {
    operator_package_filling(MINUS, PRIOR_2, &container_p);
  } else if (symb == '*' && prev_address == QUEUE) {
    operator_package_filling(MULT, PRIOR_3, &container_p);
  } else if (symb == '/' && prev_address == QUEUE) {
    operator_package_filling(DIV, PRIOR_3, &container_p);
  } else if (symb == '%' && prev_address == QUEUE) {
    operator_package_filling(MOD, PRIOR_3, &container_p);
  } else if (symb == '^' && prev_address == QUEUE) {
    operator_package_filling(POW, PRIOR_4, &container_p);
  } else if (symb == '+' && prev_address == STACK &&
             ((*s_head)->next_node_ptr == NULL ||
              (*s_head)->token_type == OPEN_BRACKET ||
              (*s_head)->token_type == POW)) {  // because 1^-2 is correct
    operator_package_filling(U_PLUS, PRIOR_4, &container_p);
  } else if (symb == '-' && prev_address == STACK &&
             ((*s_head)->next_node_ptr == NULL ||
              (*s_head)->token_type == OPEN_BRACKET ||
              (*s_head)->token_type == POW)) {  // because 1^-2 is correct
    operator_package_filling(U_MINUS, PRIOR_4, &container_p);
  } else if (symb == '(') {
    operator_package_filling(OPEN_BRACKET, PRIOR_1, &container_p);
  } else {
    error_code = INCORRECT_INPUT;
  }
  *str += 1;
  log_info("OPERATOR: operator_code is %d \'%c\'", container_p->token_type,
           symb);

  return error_code;
}

void operator_package_filling(token_t type, token_p priority,
                              node_t** container_pp) {
  (*container_pp)->token_type = type;
  (*container_pp)->token_priority = priority;
}
