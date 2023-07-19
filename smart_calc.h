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
  MEMORY_ACCESS_ERROR,  // ! test_split_string_to_tokens.c
  UNBALANCED_BRACKETS,
  EMPTY_BRACKETS,
  INCORRECT_INPUT,
  STACK_UNDERFLOW,  // ! push.c
  STACK_OVERFLOW,   // ! push.c
  QUEUE_OVERFLOW    // ! push.c
};

#define TOKEN_CHARS const char token_chars[] = "1234567890.+-*/^%()cstal"
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
int convert_infix_to_RPN(const char* str, node_t** q_head);
int split_string_to_tokens(const char* str, char** tokens);

#endif  // SMARTCALC_SMART_CALC_H_
