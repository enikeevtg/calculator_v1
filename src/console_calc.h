#ifndef CONSOLE_CALC_CONSOLE_CALC_H_
#define CONSOLE_CALC_CONSOLE_CALC_H_

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

#define MAX_INPUT_STR_LEN 255
#define TOLERANCE 1E-7

enum error_codes {
  OK,
  TOO_LONG_EXPRESSION,
  EMPTY_EXPRESSION,
  UNDEFINED_TOKEN,
  DATA_STRUCT_UNDERFLOW,
  DATA_STRUCT_OVERFLOW,
  UNBALANCED_BRACKETS,
  EMPTY_BRACKETS,
  INCORRECT_INPUT,
  EMPTY_QUEUE,
  ACOS_ERROR,
  ASIN_ERROR,
  LN_ERROR,
  LOG_ERROR,
  SQRT_ERROR
};

#define ERRORS_MESSAGES_NUMBERS 15
#define ERRORS_MESSAGE_MAX_SIZE 22
#define ERRORS_MESSAGES                                                 \
  char errors_msg[ERRORS_MESSAGES_NUMBERS][ERRORS_MESSAGE_MAX_SIZE] = { \
      "OK",                                                             \
      "TOO_LONG_EXPRESSION",                                            \
      "EMPTY_EXPRESSION",                                               \
      "UNDEFINED_TOKEN",                                                \
      "DATA_STRUCT_UNDERFLOW",                                          \
      "DATA_STRUCT_OVERFLOW",                                           \
      "UNBALANCED_BRACKETS",                                            \
      "EMPTY_BRACKETS",                                                 \
      "INCORRECT_INPUT",                                                \
      "EMPTY_QUEUE",                                                    \
      "ACOS_ARGUMENT_ERROR",                                            \
      "ASIN_ARGUMENT_ERROR",                                            \
      "LN_ARGUMENT_ERROR",                                              \
      "LOG_ARGUMENT_ERROR",                                             \
      "SQRT_ARGUMENT_ERROR"}

#define MATH_FUNCTIONS_NUMBER 9
#define MATH_FUNCTIONS_NAMES_LENGTH 5
#define MATH_FUNCTIONS_NAMES                                   \
  const char math_functions_names                              \
      [MATH_FUNCTIONS_NUMBER][MATH_FUNCTIONS_NAMES_LENGTH] = { \
          "cos",  "sin",  "tan", "acos", "asin",               \
          "atan", "sqrt", "ln",  "log"}  // sequence is the same that in
                                         // "typedef enum token_type {...}
                                         // token_t"

#define CALC_FUNCTIONS_NUMBER 17
#define CALC_FUNCTIONS_POINTERS                                 \
  double (*calc_functions[CALC_FUNCTIONS_NUMBER])() = {         \
      cos,      sin,       tan,      acos,   asin,    atan,     \
      sqrt,     log,       log10,    u_plus, u_minus, add_calc, \
      sub_calc, mult_calc, div_calc, fmod,   pow}
// sequence is the same that in "typedef enum token_type {...} token_t", but
// without OPEN_BRACKET

// FUNCTIONS
// data structures processing
int push(int address, node_t** phead, node_t* pdata);
int pop(node_t** phead, node_t* pnode);
void fill_node(node_t* src, node_t* dest);
void remove_head_node(node_t** phead);
void remove_struct(node_t** phead);
void move_node_from_queue_to_stack(node_t** q_phead, node_t** s_phead);
void move_node_from_stack_to_queue(node_t** s_phead, node_t** q_phead);

// converter
int convert_infix_to_RPN(const char* str, node_t** q_proot);
int close_bracket_processing(int prev_address, node_t** s_phead,
                             node_t** q_phead);
int end_of_expression_processing(node_t** s_phead, node_t** q_phead);
int token_processing(int* paddress, char** current_str, node_t** s_phead,
                     node_t** q_phead, node_t* pcontainer);
int container_packing(int prev_address, char** str, node_t** s_phead,
                      node_t* pcontainer);
int value_packer(char** str, node_t* pcontainer);
int operator_packer(int prev_address, char** str, node_t** s_phead,
                    node_t* pcontainer);
int function_packer(char** str, node_t* pcontainer);
void create_mult(int prev_address, node_t** s_phead, node_t* pcontainer);
int container_sending(int* paddress, node_t** s_phead, node_t** q_phead,
                      node_t* pcontainer);

// evaluator
int evaluate_expression(node_t* q_root, double* result);
int numerical_calculation(node_t** s_phead, token_t function_id);
double u_plus(double value);
double u_minus(double value);
double add_calc(double value_1, double value_2);
double sub_calc(double value_1, double value_2);
double mult_calc(double value_1, double value_2);
double div_calc(double value_1, double value_2);

#endif  // CONSOLE_CALC_CONSOLE_CALC_H_
