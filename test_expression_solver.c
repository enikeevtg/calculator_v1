#include "smart_calc.h"

int main() {
  char input_str[255] = "5 5";
  printf("%s\n", input_str);

  node_t* q_root = NULL;
  double result = 0;

  int error = convert_infix_to_RPN(input_str, &q_root);
  node_t* q_head = q_root;
  int i = 0;
  while (!error && q_head) {
    printf("#%d: type = %d, prio = %d, value = %lf\n", i, q_head->token_type,
           q_head->token_priority, q_head->token_value);
    q_head = q_head->next_node_ptr;
    i++;
  }

  if (!error) error = expression_solver(q_root, 0, &result);

  if (error)
    printf("error_code = %d\n", error);
  else
    printf("%lf", result);
  return 0;
}
