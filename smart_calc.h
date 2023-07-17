#ifndef SMARTCALC_SMART_CALC_H_
#define SMARTCALC_SMART_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_structures.h"

enum error_codes {
  OK,
  MEMORY_ACCESS_ERROR,
  TOO_LONG_STRING,
  UNDEFINED_TOKEN,
  UNBALANCED_BRACKETS,
  DATA_STRUCT_OVERFLOW,
  DATA_STRUCT_UNDERFLOW,
  STACK_UNDERFLOW,
  STACK_OVERFLOW,
  QUEUE_OVERFLOW
};

#define FUNCTIONS_NUMBER 9
#define FUNCTIONS_NAMES_MAX_LENGTH 5
#define FUNCTIONS_NAMES                                                        \
  const char functions_names[FUNCTIONS_NUMBER][FUNCTIONS_NAMES_MAX_LENGTH] = { \
      "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"}

// FUNCTIONS
// data structures processing
int push(int struct_type, node_t** head, node_t* data);
int pop(node_t** s_head, node_t* node);
void node_filling(node_t* src, node_t* dest);
void node_removing(node_t** head);
void struct_removing(node_t** head);
int node_from_queue_to_stack(node_t** q_head, node_t** s_head);
int node_from_stack_to_queue(node_t** s_head, node_t** q_head);

// calculator
int string_processing(const char* str, node_t** s_head, node_t** q_head);
int string_processing_v1(const char* str, char** tokens);

#endif  // SMARTCALC_SMART_CALC_H_
