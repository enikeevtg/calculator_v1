/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

int close_bracket_processing(int prev_address, node_t** s_head_ptr,
                             node_t** q_head_ptr);
int end_of_expression_processing(node_t** s_head_ptr, node_t** q_head_ptr);
int token_processing(int* address, char** current_str, node_t** s_head_ptr,
                     node_t** q_head_ptr, node_t* container_ptr);
int container_packing(int prev_address, char** str, node_t** s_head_ptr,
                      node_t* container_ptr);
int value_packer(char** str, node_t* container_ptr);
int operator_packer(int prev_address, node_t** s_head_ptr, char** str,
                    node_t* container_ptr);
int function_packer(char** str, node_t* container_ptr);
int container_sending(int* address, node_t** s_head_ptr, node_t** q_head_ptr,
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
  const char token_first_chars[] = "1234567890.+-*/^%(cstal";

  while (!error && !(*current_str == '\0' && s_head == NULL)) {
    if (*current_str == ')') {
      container.token_type = CLOSE_BRACKET;
      error = close_bracket_processing(address, &s_head, q_head_ptr);
      current_str++;
    } else if (*current_str == '\0') {
      error = end_of_expression_processing(&s_head, q_head_ptr);
    } else if (*current_str == ' ') {
      current_str++;
    } else if (strchr(token_first_chars, *current_str)) {
      error = token_processing(&address, &current_str, &s_head, q_head_ptr,
                               &container);
    } else {
      error = UNDEFINED_TOKEN;
    }
    if (q_root == NULL) q_root = *q_head_ptr;
  }  // while

  if (error != OK) {
    remove_struct(&s_head);
    remove_struct(&q_root);
  }
  *q_head_ptr = q_root;
  return error;
}

int close_bracket_processing(int prev_address, node_t** s_head_ptr,
                             node_t** q_head_ptr) {
  if (prev_address == STACK && (*s_head_ptr)->token_type == OPEN_BRACKET)
    return EMPTY_BRACKETS;
  if (prev_address == STACK) return INCORRECT_INPUT;

  int error = OK;
  while (*s_head_ptr && (*s_head_ptr)->token_type != OPEN_BRACKET)
    move_node_from_stack_to_queue(s_head_ptr, q_head_ptr);
  if (*s_head_ptr != NULL) {
    remove_head_node(s_head_ptr);
  } else {
    error = UNBALANCED_BRACKETS;
  }
  return error;
}

int end_of_expression_processing(node_t** s_head_ptr, node_t** q_head_ptr) {
  int error = OK;
  while (*s_head_ptr != NULL && (*s_head_ptr)->token_type != OPEN_BRACKET)
    move_node_from_stack_to_queue(s_head_ptr, q_head_ptr);
  if (*s_head_ptr != NULL) error = UNBALANCED_BRACKETS;
  return error;
}

int token_processing(int* address_ptr, char** current_str, node_t** s_head_ptr,
                     node_t** q_head_ptr, node_t* container_ptr) {
  int error = OK;

  error =
      container_packing(*address_ptr, current_str, s_head_ptr, container_ptr);
  if (error == OK) {
    error =
        container_sending(address_ptr, s_head_ptr, q_head_ptr, container_ptr);
  }
  return error;
}

int container_packing(int prev_address, char** str, node_t** s_head_ptr,
                      node_t* container_ptr) {
  int error = OK;

  const char numbers_chars[] = "1234567890.";
  const char operators_chars[] = "+-*/^%()";
  char token_symbol = **str;

  if (strchr(numbers_chars, token_symbol)) {
    if (prev_address == QUEUE && container_ptr->token_type != CLOSE_BRACKET) {
      error = INCORRECT_INPUT;
    } else if (prev_address == QUEUE &&
               container_ptr->token_type == CLOSE_BRACKET) {  // )NUM -> )*NUM
      char* mult_char_str = "*";
      operator_packer(prev_address, s_head_ptr, &mult_char_str, container_ptr);
    } else {
      error = value_packer(str, container_ptr);
    }
  } else if (strchr(operators_chars, token_symbol)) {
    error = operator_packer(prev_address, s_head_ptr, str, container_ptr);
  } else {  // functions case
    if (prev_address == QUEUE || container_ptr->token_type == CLOSE_BRACKET) {
      char* mult_char_str = "*";
      operator_packer(prev_address, s_head_ptr, &mult_char_str, container_ptr);
    } else {
      error = function_packer(str, container_ptr);
    }
  }
  return error;
}

int value_packer(char** str, node_t* container_ptr) {
  container_ptr->token_type = NUMBER;
  sscanf(*str, "%lf", &(container_ptr->token_value));
  const char numbers_chars[] = "1234567890";
  *str += strspn(*str, numbers_chars);
  if (**str == '.') {
    (*str)++;
    *str += strspn(*str, numbers_chars);
  }
  return OK;
}

int operator_packer(int prev_address, node_t** s_head_ptr, char** str,
                    node_t* container_ptr) {
  int error = OK;
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
             (*s_head_ptr == NULL ||
              (*s_head_ptr)->token_type == OPEN_BRACKET ||
              (*s_head_ptr)->token_type == POW)) {  // because 1^-2 is correct
    node_t tmp_node = {NULL, U_PLUS, PRIOR_5, 0};
    node_filling(&tmp_node, container_ptr);
  } else if (symb == '-' && prev_address == STACK &&
             (*s_head_ptr == NULL ||
              (*s_head_ptr)->token_type == OPEN_BRACKET ||
              (*s_head_ptr)->token_type == POW)) {  // because 1^-2 is correct
    node_t tmp_node = {NULL, U_MINUS, PRIOR_5, 0};
    node_filling(&tmp_node, container_ptr);
  } else if (symb == '(' && prev_address == QUEUE) {  // NUM( -> NUM*(
    node_t tmp_node = {NULL, MULT, PRIOR_3, 0};
    node_filling(&tmp_node, container_ptr);
    *str -= 1;
  } else if (symb == '(' && prev_address == STACK) {
    node_t tmp_node = {NULL, OPEN_BRACKET, PRIOR_1, 0};
    node_filling(&tmp_node, container_ptr);
  } else {
    error = INCORRECT_INPUT;
  }
  *str += 1;
  return error;
}

int function_packer(char** str, node_t* container_ptr) {
  char* after_function_char_ptr = strpbrk(*str, "1234567890.+-*/^%(");
  if (after_function_char_ptr == NULL) return INCORRECT_INPUT;

  int error = OK;

  MATH_FUNCTIONS_NAMES;
  char after_function_char = *after_function_char_ptr;
  *after_function_char_ptr = '\0';
  int func_id = 0;
  while (func_id < MATH_FUNCTIONS_NUMBER &&
         strcmp(*str, math_functions_names[func_id]))
    func_id++;
  if (func_id == MATH_FUNCTIONS_NUMBER) {
    error = UNDEFINED_TOKEN;
  } else {
    container_ptr->token_type = func_id;
    container_ptr->token_priority = PRIOR_5;
    *after_function_char_ptr = after_function_char;
    *str = after_function_char_ptr;
  }
  return error;
}

int container_sending(int* address, node_t** s_head_ptr, node_t** q_head_ptr,
                      node_t* container_ptr) {
  int error = OK;
  *address = STACK;
  if (container_ptr->token_type < PLUS) {  // functions and '('
    error = push(*address, s_head_ptr, container_ptr);
  } else if (container_ptr->token_type < NUMBER) {  // operators
    while (!error && *s_head_ptr != NULL &&
           container_ptr->token_priority <= (*s_head_ptr)->token_priority) {
      error = move_node_from_stack_to_queue(s_head_ptr, q_head_ptr);
    }
    if (!error) error = push(*address, s_head_ptr, container_ptr);
  } else {
    *address = QUEUE;
    error = push(*address, q_head_ptr, container_ptr);
  }
  return error;
}
