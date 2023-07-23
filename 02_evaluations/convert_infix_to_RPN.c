/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

int close_bracket_processing(int prev_address, node_t** s_phead,
                             node_t** q_phead);
int end_of_expression_processing(node_t** s_phead, node_t** q_phead);
int token_processing(int* address, char** current_str, node_t** s_phead,
                     node_t** q_phead, node_t* pcontainer);
int container_packing(int prev_address, char** str, node_t** s_phead,
                      node_t* pcontainer);
int value_packer(char** str, node_t* pcontainer);
int operator_packer(int prev_address, node_t** s_phead, char** str,
                    node_t* pcontainer);
int function_packer(char** str, node_t* pcontainer);
void create_mult(int prev_address, node_t** s_phead, node_t* pcontainer);
int container_sending(int* address, node_t** s_phead, node_t** q_phead,
                      node_t* pcontainer);

/// @brief converting from infix notation to reverse Polish notation
/// @param str
/// @param q_phead queue head pointer pointer.
/// Initial it is pointing to queue root.
/// When function is doing it is redefined to queue head,
/// but in the end of function it is redefined to first queue node pointer
/// @return error code
int convert_infix_to_RPN(const char* str, node_t** q_phead) {
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
      error = close_bracket_processing(address, &s_head, q_phead);
      current_str++;
    } else if (*current_str == '\0') {
      error = end_of_expression_processing(&s_head, q_phead);
    } else if (*current_str == ' ') {
      current_str++;
    } else if (strchr(token_first_chars, *current_str)) {
      error = token_processing(&address, &current_str, &s_head, q_phead,
                               &container);
    } else {
      error = UNDEFINED_TOKEN;
    }
    if (q_root == NULL) q_root = *q_phead;
  }  // while

  if (error != OK) {
    remove_struct(&s_head);
    remove_struct(&q_root);
  }
  *q_phead = q_root;
  return error;
}

/// @brief
/// @param prev_address
/// @param s_phead
/// @param q_phead
/// @return
int close_bracket_processing(int prev_address, node_t** s_phead,
                             node_t** q_phead) {
  if (prev_address == STACK && (*s_phead)->token_type == OPEN_BRACKET)
    return EMPTY_BRACKETS;
  if (prev_address == STACK) return INCORRECT_INPUT;

  int error = OK;
  while (*s_phead && (*s_phead)->token_type != OPEN_BRACKET)
    move_node_from_stack_to_queue(s_phead, q_phead);
  if (*s_phead != NULL) {
    remove_head_node(s_phead);
  } else {
    error = UNBALANCED_BRACKETS;
  }
  return error;
}

/// @brief
/// @param s_phead
/// @param q_phead
/// @return
int end_of_expression_processing(node_t** s_phead, node_t** q_phead) {
  int error = OK;
  while (*s_phead != NULL && (*s_phead)->token_type != OPEN_BRACKET)
    error = move_node_from_stack_to_queue(s_phead, q_phead);
  if (!error && *s_phead != NULL) error = UNBALANCED_BRACKETS;
  return error;
}

/// @brief
/// @param address_ptr
/// @param current_str
/// @param s_phead
/// @param q_phead
/// @param pcontainer
/// @return
int token_processing(int* address_ptr, char** current_str, node_t** s_phead,
                     node_t** q_phead, node_t* pcontainer) {
  int error = OK;

  error = container_packing(*address_ptr, current_str, s_phead, pcontainer);
  if (error == OK) {
    error = container_sending(address_ptr, s_phead, q_phead, pcontainer);
  }
  return error;
}

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
    error = operator_packer(prev_address, s_phead, str, pcontainer);
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
    (*str)++;
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
int operator_packer(int prev_address, node_t** s_phead, char** str,
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
    node_t tmp_node = {NULL, POW, PRIOR_6, 0};
    fill_node(&tmp_node, pcontainer);
  } else if (symb == '+' && prev_address == STACK &&
             (*s_phead == NULL || (*s_phead)->token_type == OPEN_BRACKET ||
              (*s_phead)->token_type == POW)) {  // because 1^-2 is correct
    node_t tmp_node = {NULL, U_PLUS, PRIOR_5, 0};
    fill_node(&tmp_node, pcontainer);
  } else if (symb == '-' && prev_address == STACK &&
             (*s_phead == NULL || (*s_phead)->token_type == OPEN_BRACKET ||
              (*s_phead)->token_type == POW)) {  // because 1^-2 is correct
    node_t tmp_node = {NULL, U_MINUS, PRIOR_5, 0};
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
  char* after_function_char_ptr = strpbrk(*str, "(1234567890.+-*/^%");
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
    pcontainer->token_priority = PRIOR_5;
    if (after_function_char_ptr != NULL)
      *after_function_char_ptr = after_function_char;
    *str = after_function_char_ptr;
  }
  return error;
}

/// @brief 
/// @param prev_address 
/// @param s_phead 
/// @param pcontainer 
void create_mult(int prev_address, node_t** s_phead, node_t* pcontainer) {
  char* mult_char_str = "*";
  operator_packer(prev_address, s_phead, &mult_char_str, pcontainer);
}

/// @brief
/// @param address
/// @param s_phead
/// @param q_phead
/// @param pcontainer
/// @return
int container_sending(int* address, node_t** s_phead, node_t** q_phead,
                      node_t* pcontainer) {
  int error = OK;
  *address = STACK;
  if (pcontainer->token_type <= OPEN_BRACKET) {  // functions and '('
    error = push(STACK, s_phead, pcontainer);
  } else if (pcontainer->token_type < POW) {  // left-associative operators
    while (!error && *s_phead != NULL &&
           pcontainer->token_priority <= (*s_phead)->token_priority) {
      error = move_node_from_stack_to_queue(s_phead, q_phead);
    }
    if (!error) error = push(STACK, s_phead, pcontainer);
  } else if (pcontainer->token_type == POW) {  // right-associative POW
    while (!error && *s_phead != NULL &&
           pcontainer->token_priority <= (*s_phead)->token_priority && (*s_phead)->token_type != POW) {
      error = move_node_from_stack_to_queue(s_phead, q_phead);
    }
    if (!error) error = push(STACK, s_phead, pcontainer);
  } else {  // if NUMBER or VAR
    error = push(QUEUE, q_phead, pcontainer);
    *address = QUEUE;
  }
  return error;
}
