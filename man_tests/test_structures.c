#include "../console_calc.h"

int main() {
  printf("token_t size = %ld\n", sizeof(token_t));
  printf("token_p size = %ld\n", sizeof(token_p));
  printf("stack_node_t size = %ld\n", sizeof(node_t));
  printf("node_t size = %ld\n", sizeof(node_t));

  node_t* stack_head = NULL;

  node_t node1 = {
    pnext : NULL,
    token_type : LOG,
    token_priority : PRIOR_4
  };

  node_t node2 = {
    pnext : &node1,
    token_type : NUMBER,
    token_value : 15.3
  };

  printf("&head_node = %p\n", stack_head);
  push(STACK, &stack_head, &node1);
  printf("&head_node = %p\n", stack_head);
  push(STACK, &stack_head, &node2);
  printf("&head_node = %p\n", stack_head);

  node_t* ptr = stack_head;
  int i = 2;
  while (pop(&stack_head, ptr) != DATA_STRUCT_UNDERFLOW) {
    printf("\nnode #%d\n", i--);
    printf("token_type = %d\ntoken_priority = %d\ntoken value = %lf\n",
           ptr->token_type, ptr->token_priority, ptr->token_value);
  }
  return 0;
}
