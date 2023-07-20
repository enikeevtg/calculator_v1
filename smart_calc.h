#ifndef SMARTCALC_SMART_CALC_H_
#define SMARTCALC_SMART_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_structures.h"

#ifdef DEBUG
#define log_info(M, ...) \
  fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define log_info(M, ...)
#endif

enum error_codes {
  OK,
  UNDEFINED_TOKEN,
  DATA_STRUCT_UNDERFLOW,
  DATA_STRUCT_OVERFLOW,
  TOO_LONG_STRING,
  EMPTY_EXPRESSION,
  MEMORY_ACCESS_ERROR,  // ! test_split_string_to_tokens.c
  UNBALANCED_BRACKETS,
  EMPTY_BRACKETS,
  INCORRECT_INPUT,
  EMPTY_QUEUE,
  STACK_UNDERFLOW,  // ! push.c
  STACK_OVERFLOW,   // ! push.c
  QUEUE_OVERFLOW    // ! push.c
};

#define ERRORS_MESSAGES_NUMBERS 14
#define ERRORS_MESSAGE_MAX_SIZE 22
#define ERRORS_MESSAGES                                                 \
  char errors_msg[ERRORS_MESSAGES_NUMBERS][ERRORS_MESSAGE_MAX_SIZE] = { \
      "OK",                                                             \
      "UNDEFINED_TOKEN",                                                \
      "DATA_STRUCT_UNDERFLOW",                                          \
      "DATA_STRUCT_OVERFLOW",                                           \
      "TOO_LONG_STRING",                                                \
      "EMPTY_EXPRESSION",                                               \
      "MEMORY_ACCESS_ERROR",                                            \
      "UNBALANCED_BRACKETS",                                            \
      "EMPTY_BRACKETS",                                                 \
      "INCORRECT_INPUT",                                                \
      "EMPTY_QUEUE",                                                    \
      "STACK_UNDERFLOW",                                                \
      "STACK_OVERFLOW",                                                 \
      "QUEUE_OVERFLOW"}

#define OPERATORS_CHARS const char operators_chars[] = "+-*/^%()"
#define FUNCTIONS_FIRST_LETTERS const char functions_first_letters[] = "cstal"
#define NUMBERS_CHARS const char numbers_chars[] = "1234567890."
#define FUNCTIONS_NUMBER 9
#define FUNCTIONS_NAMES_MAX_LENGTH 5
#define FUNCTIONS_NAMES                                                        \
  const char functions_names[FUNCTIONS_NUMBER][FUNCTIONS_NAMES_MAX_LENGTH] = { \
      "cos",  "sin",  "tan", "acos", "asin",                                   \
      "atan", "sqrt", "ln",  "log"}  // sequence is the same that in
                                     // "typedef enum token_type {...}
                                     // token_t"

#define CALC_FUNCTIONS_NUMBER 17
#define C_FUNCTIONS_POINTERS                                      \
  double (*c_functions[CALC_FUNCTIONS_NUMBER])() = {              \
      cos,      sin,       tan,      acos,     asin,    atan,     \
      sqrt,     log,       log10,    u_plus,   u_minus, add_calc, \
      sub_calc, mult_calc, div_calc, mod_calc, pow_calc}

// FUNCTIONS
// data structures processing
int push(int address, node_t** head, node_t* data);
int pop(node_t** s_head, node_t* node);
void node_filling(node_t* src, node_t* dest);
void node_removing(node_t** head);
void struct_removing(node_t** head);
int node_from_queue_to_stack(node_t** q_head, node_t** s_head);
int node_from_stack_to_queue(node_t** s_head, node_t** q_head);

// calculator
int split_string_to_tokens(const char* str, char** tokens);
int convert_infix_to_RPN(const char* str, node_t** q_head);
int expression_solver(node_t* q_root, double variable, double* result);
int numerical_calculation(node_t** s_head, token_t function_id);

#endif  // SMARTCALC_SMART_CALC_H_
