#include "smart_calc.h"

int main() {
  char input_str[255] = "-(123.123456 + 321)- 3^-1 / 23 * 1% sin18 * ln(11-3)";
  printf("%s\n", input_str);

  node_t queue_node = {0};
  node_t* q_root = &queue_node;

  int error = convert_infix_to_RPN(input_str, q_root);

  int i = 0;
  while (!error && q_root) {
    printf("#%d: type = %d, prio = %d, value = %lf\n", i, q_root->token_type,
           q_root->token_priority, q_root->token_value);
    q_root = q_root->next_node_ptr;
    i++;
  }

  return 0;
}
