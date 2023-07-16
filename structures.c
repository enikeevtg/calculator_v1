#include "smart_calc.h"

int main() {
  printf("token_t size = %ld\n", sizeof(token_t));
  printf("token_p size = %ld\n", sizeof(token_p));
  printf("stack_node_t size = %ld\n", sizeof(stack_node_t));
  printf("queue_node_t size = %ld\n", sizeof(queue_node_t));

  stack_node_t* stack_head = NULL;
  
  stack_node_t node1 = {
    prev_node : NULL,
    token_type : LOG,
    token_priority : O4
  };
  
  stack_node_t node2 = {
    prev_node : &node1,
    token_type : NUMBER,
    token_value : 15.3
  };

  printf("&head_node = %p\n", stack_head);
  stack_push(&stack_head, &node1);
  printf("&head_node = %p\n", stack_head);
  stack_push(&stack_head, &node2);
  printf("&head_node = %p\n", stack_head);

  stack_node_t* ptr = stack_head;
  int i = 2;
  while (stack_pop(&stack_head, ptr) != STACK_UNDERFLOW) {
    printf("\nnode #%d\n", i--);
    printf("token_type = %d\ntoken_priority = %d\ntoken value = %lf\n", ptr->token_type, ptr->token_priority, ptr->token_value);
  }
  return 0;
}
