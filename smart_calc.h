#ifndef SMARTCALC_SRC_H_
#define SMARTCALC_SRC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum error_codes {
  OK,
  TOO_LONG_STRING,
  DATA_STRUCT_OVERFLOW,
  DATA_STRUCT_UNDERFLOW,
  STACK_UNDERFLOW,
  STACK_OVERFLOW,
  QUEUE_OVERFLOW
};

typedef enum {
  NUMBER,
  VAR,
  LEFT_BRACKET,
  PLUS,
  MINUS,
  MULT,
  DIV,
  POW,
  MOD,
  U_PLUS,
  U_MINUS,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG
} token_t;

typedef enum { O1, O2, O3, O4 } token_p;

typedef struct node_tag {
  struct node_tag* next_node_ptr;
  token_t token_type;
  token_p token_priority;
  double token_value;
} node_t; /* 24 bytes size */

#define DEFAULT_Q_SIZE 21
#define STACK 1
#define QUEUE 2

// FUNCTIONS
int push(int struct_type, node_t** head, node_t* data);
int pop(node_t** head, node_t* node);
void node_filling(node_t* dest, node_t* src);
int node_move(int dest_struct_type, node_t** dest_head, node_t** src_head);

#endif  // SMARTCALC_SRC_H_
