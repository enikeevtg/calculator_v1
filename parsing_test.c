#include "smart_calc.h"

int main() {
  char input_str[255] = "(123 + 321) / 23 * 1%";
  // scanf("%s", input_str);
  printf("%s\n", input_str);

  node_t stack = {0};
  node_t queue = {0};
  
  string_processing(input_str);
  printf("\n%s\n", input_str);

  return 0;
}
