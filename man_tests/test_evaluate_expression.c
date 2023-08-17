#include "../console_calc.h"

int main() {
  char input_str[255] = "-2^2^3";
  printf("%s\n", input_str);

  node_t* q_root = NULL;
  double result = 0;

  int error = convert_infix_to_RPN(input_str, &q_root);
  node_t* q_head = q_root;
  int i = 0;
  while (!error && q_head) {
    printf("#%d: type = %d, prio = %d, value = %lf\n", i, q_head->token_type,
           q_head->token_priority, q_head->token_value);
    q_head = q_head->pnext;
    i++;
  }

  if (!error) error = evaluate_expression(q_root, &result);

  if (error) {
    ERRORS_MESSAGES;
    printf("error_code = %s\n", errors_msg[error]);
  } else
    printf("%lf", result);
  return 0;
}
