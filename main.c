#include <stdio.h>

#include "console_calc.h"

#define STR_MAX_LEN 256

int main() {
  char str[STR_MAX_LEN] = {0};
  fgets(str, STR_MAX_LEN, stdin);
  str[strlen(str) - 1] = '\0';

  int error = OK;
  node_t* q_root = NULL;

  double result = 0;

  error = convert_infix_to_RPN(str, &q_root);
  if (error == OK) error = evaluate_expression(q_root, &result);

  if (error == OK)
    printf("%lf", result);
  else {
    ERRORS_MESSAGES;
    printf("error: %s", errors_msg[error]);
  }

  return 0;
}
