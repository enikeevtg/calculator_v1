/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

int close_bracket_processing(int prev_address, node_t** s_head,
                             node_t** q_head_ptr);

int container_packing(int prev_address, node_t** s_head, char** str,
                      node_t* container_ptr);
int value_packer(char** str, node_t* container_ptr);
int operator_packer(int prev_address, node_t** s_head, char** str,
                    node_t* container_ptr);
int function_packer(char** str, node_t* container_ptr);
int container_sending(int* address, node_t** s_head, node_t** q_head_ptr,
                      node_t* container_ptr);

/// @brief converting from infix notation to reverse Polish notation
/// @param str
/// @param q_head_ptr queue head pointer pointer.
/// Initial it is pointing to queue root.
/// When function is doing it is redefined to queue head,
/// but in the end of function it is redefined to first queue node pointer
/// @return error code
int convert_infix_to_RPN(const char* str, node_t** q_head_ptr) {
  int error = OK;

  char* current_str = (char*)str;
  node_t* s_head = NULL;
  node_t* q_root = NULL;
  int address = STACK;
  node_t container = {0};
  TOKEN_CHARS;

  while (!error && !(*current_str == '\0' && s_head == NULL)) {
    if (*current_str == ')') {
      error = close_bracket_processing(address, &s_head, q_head_ptr);
      current_str++;
    } else if (*current_str == '\0') {
      while (s_head != NULL) node_from_stack_to_queue(&s_head, q_head_ptr);
      s_head = NULL;
    } else if (*current_str == ' ') {
      current_str++;
    } else if (strchr(token_chars, *current_str)) {
      error = container_packing(address, &s_head, &current_str, &container);
      if (error == OK) {
        error = container_sending(&address, &s_head, q_head_ptr, &container);
      }
    } else {
      error = UNDEFINED_TOKEN;
    }
    if (q_root == NULL) q_root = *q_head_ptr;
  }
  if (error) {
    log_info("ERROR %d", error);
    struct_removing(&s_head);
    struct_removing(&q_root);
  }
  *q_head_ptr = q_root;
  return error;
}

int close_bracket_processing(int prev_address, node_t** s_head,
                             node_t** q_head_ptr) {
  if (prev_address == STACK && (*s_head)->token_type == OPEN_BRACKET)
    return EMPTY_BRACKETS;
  if (prev_address == STACK) return INCORRECT_INPUT;

  int error = OK;
  while (*s_head && (*s_head)->token_type != OPEN_BRACKET)
    node_from_stack_to_queue(s_head, q_head_ptr);
  if (*s_head != NULL) {
    node_removing(s_head);
  } else {
    error = UNBALANCED_BRACKETS;
  }
  if (error == OK && *s_head &&
      ((*s_head)->token_type == U_PLUS || (*s_head)->token_type == U_MINUS))
    node_from_stack_to_queue(s_head, q_head_ptr);

  return error;
}

int container_packing(int prev_address, node_t** s_head, char** str,
                      node_t* container_ptr) {
  int error = OK;

  NUMBERS_CHARS;
  OPERATORS_CHARS;
  char token_symbol = **str;

  if (strchr(numbers_chars, token_symbol)) {
    error = value_packer(str, container_ptr);
  } else if (strchr(operators_chars, token_symbol)) {
    error = operator_packer(prev_address, s_head, str, container_ptr);
  } else {  // functions case
    error = function_packer(str, container_ptr);
  }
  return error;
}

int value_packer(char** str, node_t* container_ptr) {
  int error = OK;

  container_ptr->token_type = NUMBER;
  sscanf(*str, "%lf", &(container_ptr->token_value));
  // log_info("NUMBER:   value = %lf", container_ptr->token_value);

  NUMBERS_CHARS;
  *str += strspn(*str, numbers_chars);
  return OK;
}

int operator_packer(int prev_address, node_t** s_head, char** str,
                    node_t* container_ptr) {
  int error = OK;
  // if (*s_head) log_info("token_type on stack head is %d",
  // (*s_head)->token_type);
  char symb = **str;
  if (symb == '+' && prev_address == QUEUE) {
    node_t tmp_node = {NULL, PLUS, PRIOR_2, 0};
    node_filling(&tmp_node, container_ptr);
  } else if (symb == '-' && prev_address == QUEUE) {
    node_t tmp_node = {NULL, MINUS, PRIOR_2, 0};
    node_filling(&tmp_node, container_ptr);
  } else if (symb == '*' && prev_address == QUEUE) {
    node_t tmp_node = {NULL, MULT, PRIOR_3, 0};
    node_filling(&tmp_node, container_ptr);
  } else if (symb == '/' && prev_address == QUEUE) {
    node_t tmp_node = {NULL, DIV, PRIOR_3, 0};
    node_filling(&tmp_node, container_ptr);
  } else if (symb == '%' && prev_address == QUEUE) {
    node_t tmp_node = {NULL, MOD, PRIOR_3, 0};
    node_filling(&tmp_node, container_ptr);
  } else if (symb == '^' && prev_address == QUEUE) {
    node_t tmp_node = {NULL, POW, PRIOR_4, 0};
    node_filling(&tmp_node, container_ptr);
  } else if (symb == '+' && prev_address == STACK &&
             (*s_head == NULL || (*s_head)->token_type == OPEN_BRACKET ||
              (*s_head)->token_type == POW)) {  // because 1^-2 is correct
    node_t tmp_node = {NULL, U_PLUS, PRIOR_5, 0};
    node_filling(&tmp_node, container_ptr);
  } else if (symb == '-' && prev_address == STACK &&
             (*s_head == NULL || (*s_head)->token_type == OPEN_BRACKET ||
              (*s_head)->token_type == POW)) {  // because 1^-2 is correct
    node_t tmp_node = {NULL, U_MINUS, PRIOR_5, 0};
    node_filling(&tmp_node, container_ptr);
  } else if (symb == '(') {
    node_t tmp_node = {NULL, OPEN_BRACKET, PRIOR_1, 0};
    node_filling(&tmp_node, container_ptr);
  } else {
    error = INCORRECT_INPUT;
  }
  *str += 1;
  // log_info("OPERATOR: operator_id is %d \'%c\'", container_ptr->token_type,
  // symb);
  return error;
}

int function_packer(char** str, node_t* container_ptr) {
  int error = OK;

  FUNCTIONS_NAMES;
  char* char_after_function_ptr = strpbrk(*str, "1234567890(x");
  char char_after_function = *char_after_function_ptr;
  *char_after_function_ptr = '\0';

  int func_id = 0;
  while (func_id < FUNCTIONS_NUMBER && strcmp(*str, functions_names[func_id]))
    func_id++;
  if (func_id == FUNCTIONS_NUMBER) {
    error = UNDEFINED_TOKEN;
  } else {
    // log_info("FUNCTION: function_id is %d \'%s\'", func_id, *str);
    container_ptr->token_type = func_id;
    container_ptr->token_priority = PRIOR_5;
    *char_after_function_ptr = char_after_function;
    *str = char_after_function_ptr;
  }
  return error;
}

int container_sending(int* address, node_t** s_head, node_t** q_head_ptr,
                      node_t* container_ptr) {
  int error = OK;
  // log_info("PREV_ADDRESS is %d", *address);
  *address = STACK;
  if (container_ptr->token_type < PLUS) {  // functions and '('
    error = push(*address, s_head, container_ptr);
  } else if (container_ptr->token_type < NUMBER) {  // operators
    while (!error && *s_head != NULL &&
           container_ptr->token_priority <= (*s_head)->token_priority) {
      error = node_from_stack_to_queue(s_head, q_head_ptr);
    }
    if (!error) error = push(*address, s_head, container_ptr);
  } else {
    *address = QUEUE;
    error = push(*address, q_head_ptr, container_ptr);
  }
  // log_info("ADDRESS is %d", *address);
  // log_info("s_head %p", *s_head);
  // log_info("q_head_ptr %p", *q_head_ptr);
  return error;
}
