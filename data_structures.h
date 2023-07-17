#ifndef SMARTCALC_DATA_STRUCTURES_H_
#define SMARTCALC_DATA_STRUCTURES_H_

enum data_structure {STACK, QUEUE};

typedef enum token_type {
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

typedef enum token_priority { O1, O2, O3, O4 } token_p;

typedef struct node_tag {
  struct node_tag* next_node_ptr;
  token_t token_type;
  token_p token_priority;
  double token_value;
} node_t; /* 24 bytes size */

#endif  // SMARTCALC_DATA_STRUCTURES_H_
