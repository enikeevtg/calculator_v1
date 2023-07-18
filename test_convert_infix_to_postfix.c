#include "smart_calc.h"

int main() {
  char input_str[255] = "(-123.123456 + 321) / 23 * 1% sin(18) * ln(11)";
  printf("%s\n", input_str);

  node_t stack = {0};
  node_t* s_head = &stack;
  node_t queue = {0};
  node_t* q_head = &queue;

  int error_code = convert_infix_to_postfix(input_str, &s_head, &q_head);

  if (error_code == OK) {
    int i = 0;
    while (tokens_array[i][0] != '\0') {
      printf("\"%s\"\t", tokens_array[i]);
      i++;
    }
    printf("\n");
  } else {
    printf("error_code: %d\n", error_code);
  }

  free(tokens_array);

  return 0;
}
