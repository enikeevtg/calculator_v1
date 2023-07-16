#include "smart_calc.h"

int main() {
  printf("token_t size = %ld\n", sizeof(token_t));
  printf("token_p size = %ld\n", sizeof(token_p));
  printf("stack_node_t size = %ld\n", sizeof(stack_node_t));
  printf("queue_node_t size = %ld\n", sizeof(queue_node_t));

  stack_node_t node1 = {prev_node : NULL, token_type : LOG, token_priority : O4};
  stack_node_t* stack_head = &node1;
  stack_node_t node2 = {
    prev_node : &node1,
    token_type : NUMBER,
    token_value : 15.3
  };
  stack_head = &node2;
  
  stack_node_t* ptr = stack_head;
  int i = 0;
  while (ptr != NULL) {
    printf("\nnode #%d\n", i++);
    if (ptr->token_type == NUMBER) {
      printf("value = %lf\n", ptr->token_value);
    } else {
      printf("token_type = %d\ntoken_priority = %d\n", ptr->token_type, ptr->token_priority);
    }
    ptr = ptr->prev_node;
  }

  return 0;
}
