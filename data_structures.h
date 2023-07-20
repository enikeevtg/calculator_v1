#ifndef SMARTCALC_DATA_STRUCTURES_H_
#define SMARTCALC_DATA_STRUCTURES_H_

enum data_structure { STACK, QUEUE };

typedef enum token_type {
  COS,           // 'cos' : 0
  SIN,           // 'sin' : 1
  TAN,           // 'tan' : 2
  ACOS,          // 'acos' : 3
  ASIN,          // 'asin' : 4
  ATAN,          // 'atan' : 5
  SQRT,          // 'sqrt' : 6
  LN,            // 'ln' : 7
  LOG,           // 'log' : 8
  U_PLUS,        // '+' : 9
  U_MINUS,       // '-' : 10
  OPEN_BRACKET,  // '(' : 11
  PLUS,          // '+' : 12
  MINUS,         // '-' : 13
  MULT,          // '*' : 14
  DIV,           // '/' : 15
  MOD,           // '%' : 16
  POW,           // '^' : 17
  NUMBER,        // double number : 18
  VAR,           // variable 'x' : 19
  CLOSE_BRACKET,
  END_OF_EXPRESSION
} token_t;

typedef enum token_priority {
  PRIOR_1,
  PRIOR_2,
  PRIOR_3,
  PRIOR_4,
  PRIOR_5
} token_p;

typedef struct node_tag {
  struct node_tag* next_node_ptr;
  token_t token_type;
  token_p token_priority;
  double token_value;
} node_t; /* 24 bytes size */

#endif  // SMARTCALC_DATA_STRUCTURES_H_
