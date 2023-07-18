#ifndef SMARTCALC_DATA_STRUCTURES_H_
#define SMARTCALC_DATA_STRUCTURES_H_

enum data_structure { STACK, QUEUE };

typedef enum token_type {
  NUMBER,        // double number : 0
  VAR,           // variable 'x' : 1
  PLUS,          // '+' : 2
  MINUS,         // '-' : 3
  MULT,          // '*' : 4
  DIV,           // '/' : 5
  MOD,           // '%' : 6
  POW,           // '^' : 7
  U_PLUS,        // '+' : 8
  U_MINUS,       // '-' : 9
  OPEN_BRACKET,  // '(' : 10
  COS,           // 'cos' : 11
  SIN,           // 'sin' : 12
  TAN,           // 'tan' : 13
  ACOS,          // 'acos' : 14
  ASIN,          // 'asin' : 15
  ATAN,          // 'atan' : 16
  SQRT,          // 'sqrt' : 17
  LN,            // 'ln' : 18
  LOG            // 'log' : 19
} token_t;

typedef enum token_priority { PRIOR_1, PRIOR_2, PRIOR_3, PRIOR_4 } token_p;

typedef struct node_tag {
  struct node_tag* next_node_ptr;
  token_t token_type;
  token_p token_priority;
  double token_value;
} node_t; /* 24 bytes size */

#endif  // SMARTCALC_DATA_STRUCTURES_H_
