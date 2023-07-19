/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

int close_bracket_processing(int prev_address, node_t** s_head,
                             node_t** q_head);

int container_packing(int prev_address, node_t** s_head, char** str,
                      node_t* container_p);
int value_packer(char** str, node_t* container_p);
int operator_packer(int prev_address, node_t** s_head, char** str,
                    node_t* container_p);
int function_packer(char** str, node_t* container_p);
int container_sending(int* address, node_t** s_head, node_t** q_head,
                      node_t* container_p);

/// @brief converting from infix notation to reverse Polish notation
/// @param str
/// @param s_head
/// @param q_head
/// @return
int convert_infix_to_RPN(const char* str, node_t* q_head) {
  int error = OK;

  char* current_str = (char*)str;
  node_t* s_head = NULL;
  int address = STACK;
  node_t container = {0};

  // printf("\n");
  // log_info("s_head %p", s_head);
  // log_info("q_head %p\n", *q_head);

  TOKEN_CHARS;

  while (!error && !(*current_str == '\0' && s_head == NULL)) {
    if (*current_str == ')') {
      // log_info(" OPERATOR: \')\'");
      error = close_bracket_processing(address, &s_head, &q_head);
      current_str++;
    } else if (*current_str == '\0') {
      while (s_head != NULL) node_from_stack_to_queue(&s_head, &q_head);
      // log_info(" END of string detected");
      s_head = NULL;
    } else if (*current_str == ' ') {
      current_str++;
    } else if (strchr(token_chars, *current_str)) {
      error = container_packing(address, &s_head, &current_str, &container);
      if (error == OK) {
        error = container_sending(&address, &s_head, &q_head, &container);
        // printf("\n");
      }
      // if (error) log_info("ERROR %d", error);
    } else {
      error = UNDEFINED_TOKEN;
      // log_info("UNDEFINED_TOKEN detected: %c", *current_str);
    }
  }

  if (error) struct_removing(&s_head);

  return error;
}

int close_bracket_processing(int prev_address, node_t** s_head,
                             node_t** q_head) {
  if (prev_address == STACK && (*s_head)->token_type == OPEN_BRACKET)
    return EMPTY_BRACKETS;
  if (prev_address == STACK) return INCORRECT_INPUT;

  int error = OK;
  while (*s_head && (*s_head)->token_type != OPEN_BRACKET)
    node_from_stack_to_queue(s_head, q_head);
  if (*s_head != NULL) {
    node_removing(s_head);
  } else {
    error = UNBALANCED_BRACKETS;
  }
  if (error == OK && *s_head &&
      ((*s_head)->token_type == U_PLUS || (*s_head)->token_type == U_MINUS))
    node_from_stack_to_queue(s_head, q_head);

  return error;
}

int container_packing(int prev_address, node_t** s_head, char** str,
                      node_t* container_p) {
  int error = OK;

  NUMBERS_CHARS;
  OPERATORS_CHARS;
  char token_symbol = **str;

  if (strchr(numbers_chars, token_symbol)) {
    error = value_packer(str, container_p);
  } else if (strchr(operators_chars, token_symbol)) {
    error = operator_packer(prev_address, s_head, str, container_p);
  } else {  // functions case
    error = function_packer(str, container_p);
  }
  return error;
}

int value_packer(char** str, node_t* container_p) {
  int error = OK;

  container_p->token_type = NUMBER;
  sscanf(*str, "%lf", &(container_p->token_value));
  // log_info("NUMBER:   value = %lf", container_p->token_value);

  NUMBERS_CHARS;
  *str += strspn(*str, numbers_chars);
  return OK;
}

int operator_packer(int prev_address, node_t** s_head, char** str,
                    node_t* container_p) {
  int error = OK;
  // if (*s_head) log_info("token_type on stack head is %d",
  // (*s_head)->token_type);
  char symb = **str;
  if (symb == '+' && prev_address == QUEUE) {
    container_p->token_type = PLUS;
    container_p->token_priority = PRIOR_2;
    container_p->token_value = 0;
  } else if (symb == '-' && prev_address == QUEUE) {
    container_p->token_type = MINUS;
    container_p->token_priority = PRIOR_2;
    container_p->token_value = 0;
  } else if (symb == '*' && prev_address == QUEUE) {
    container_p->token_type = MULT;
    container_p->token_priority = PRIOR_3;
    container_p->token_value = 0;
  } else if (symb == '/' && prev_address == QUEUE) {
    container_p->token_type = DIV;
    container_p->token_priority = PRIOR_3;
    container_p->token_value = 0;
  } else if (symb == '%' && prev_address == QUEUE) {
    container_p->token_type = MOD;
    container_p->token_priority = PRIOR_3;
    container_p->token_value = 0;
  } else if (symb == '^' && prev_address == QUEUE) {
    container_p->token_type = POW;
    container_p->token_priority = PRIOR_4;
    container_p->token_value = 0;
  } else if (symb == '+' && prev_address == STACK &&
             (*s_head == NULL || (*s_head)->token_type == OPEN_BRACKET ||
              (*s_head)->token_type == POW)) {  // because 1^-2 is correct
    container_p->token_type = U_PLUS;
    container_p->token_priority = PRIOR_5;
    container_p->token_value = 0;
  } else if (symb == '-' && prev_address == STACK &&
             (*s_head == NULL || (*s_head)->token_type == OPEN_BRACKET ||
              (*s_head)->token_type == POW)) {  // because 1^-2 is correct
    container_p->token_type = U_MINUS;
    container_p->token_priority = PRIOR_5;
    container_p->token_value = 0;
  } else if (symb == '(') {
    container_p->token_type = OPEN_BRACKET;
    container_p->token_priority = PRIOR_1;
    container_p->token_value = 0;
  } else {
    error = INCORRECT_INPUT;
  }
  *str += 1;
  // log_info("OPERATOR: operator_id is %d \'%c\'", container_p->token_type,
  // symb);
  return error;
}

int function_packer(char** str, node_t* container_p) {
  int error = OK;

  FUNCTIONS_NAMES;
  char* char_after_function_ptr = strpbrk(*str, "(1234567890x");
  char char_after_function = *char_after_function_ptr;
  *char_after_function_ptr = '\0';

  int func_id = 0;
  while (func_id < FUNCTIONS_NUMBER && strcmp(*str, functions_names[func_id]))
    func_id++;
  if (func_id == FUNCTIONS_NUMBER) {
    error = UNDEFINED_TOKEN;
  } else {
    // log_info("FUNCTION: function_id is %d \'%s\'", func_id, *str);
    container_p->token_type = func_id;
    container_p->token_priority = PRIOR_5;
    *char_after_function_ptr = char_after_function;
    *str = char_after_function_ptr;
  }
  return error;
}

int container_sending(int* address, node_t** s_head, node_t** q_head,
                      node_t* container_p) {
  int error = OK;
  // log_info("PREV_ADDRESS is %d", *address);
  *address = STACK;
  if (container_p->token_type < PLUS) {
    error = push(*address, s_head, container_p);
  } else if (container_p->token_type < NUMBER) {
    while (!error && *s_head != NULL &&
           container_p->token_priority <= (*s_head)->token_priority) {
      error = node_from_stack_to_queue(s_head, q_head);
    }
    if (!error) error = push(*address, s_head, container_p);
  } else {
    *address = QUEUE;
    error = push(*address, q_head, container_p);
  }
  // log_info("ADDRESS is %d", *address);
  // log_info("s_head %p", *s_head);
  // log_info("q_head %p", *q_head);
  return error;
}
