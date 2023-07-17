#ifndef SMARTCALC_SMART_CALC_H_
#define SMARTCALC_SMART_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_structures.h"

enum error_codes {
  OK,
  TOO_LONG_STRING,
  DATA_STRUCT_OVERFLOW,
  DATA_STRUCT_UNDERFLOW,
  STACK_UNDERFLOW,
  STACK_OVERFLOW,
  QUEUE_OVERFLOW
};

// FUNCTIONS
// data structures processing
int push(int struct_type, node_t** head, node_t* data);
int pop(node_t** head, node_t* node);
void node_filling(node_t* src, node_t* dest);
int node_from_queue_to_stack(node_t** q_head, node_t** s_head);
int node_from_stack_to_queue(node_t** s_head, node_t** q_head);

// calculator
void string_processing(const char* str/*, node_t** s_head, node_t** q_head */);

#endif  // SMARTCALC_SMART_CALC_H_
