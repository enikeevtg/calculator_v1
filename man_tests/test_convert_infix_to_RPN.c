#include "../console_calc.h"

int main() {
  char input_str[255] =
      "-(-123.123456 + 321.1)- 3.5^-1.4 / 23.00001 * 1.0% sin18.46431 * "
      "ln(11.456-3.148)";
  printf("%s\n", input_str);

  node_t* q_root = NULL;

  int error = convert_infix_to_RPN(input_str, &q_root);

  int i = 0;
  while (!error && q_root) {
    printf("#%d: type = %d, prio = %d, value = %lf\n", i, q_root->token_type,
           q_root->token_priority, q_root->token_value);
    q_root = q_root->pnext;
    i++;
  }

  return 0;
}
