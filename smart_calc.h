#ifndef SMARTCALC_SRC_H_
#define SMARTCALC_SRC_H_

#include <math.h>
#include <stdio.h>
#include <string.h>

enum error_codes { OK, TOO_LONG_STRING, STACK_UNDERFLOW, STACK_OVERFLOW,QUEUE_OVERFLOW };

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

typedef struct stack_tag {
  struct stack_tag* prev_node;
  token_t token_type;
  token_p token_priority;
  double token_value;
} stack_node_t; /* 24 bytes size */

typedef struct queue_tag {
  struct queue_tag* next_node;
  token_t token_type;
  double token_value;
} queue_node_t; /* 24 bytes size */

#define DEFAULT_Q_SIZE 21

#endif  // SMARTCALC_SRC_H_
