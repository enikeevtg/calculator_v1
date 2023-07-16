#include "../smart_calc.h"


int stack_append(stack_node_t** stack_head, stack_node_t* data) {
  int error_code = OK;
  stack_node_t* new_node_ptr = (stack_node_t*)calloc(1, sizeof(stack_node_t));
  if (new_node_ptr == NULL) {
    error_code = STACK_OVERFLOW;
  } else {
    new_node_ptr->prev_node = *stack_head;
    new_node_ptr->token_type = data->token_type;
    new_node_ptr->token_priority = data->token_priority;
    *stack_head = new_node_ptr;
  }
  return error_code;
}

int stack_get(stack_node_t** stack_head, stack_node_t* node) {
  if (*stack_head == NULL) return STACK_UNDERFLOW;
  
  node->token_type = (*stack_head)->token_type;
  node->token_priority = (*stack_head)->token_priority;
  node->token_value = (*stack_head)->token_value;
  free(*stack_head);
  *stack_head = (*stack_head)->prev_node;
  return OK;
}

int stack_to_queue(stack_node_t** stack_head, queue_node_t** queue_head) {
  int error_code = OK;
  queue_node_t* new_q_node_ptr = (queue_node_t*)calloc(1, sizeof(queue_node_t));
  if (new_q_node_ptr == NULL) {
    error_code = QUEUE_OVERFLOW;
  } else {
    stack_get(stack_head, new_q_node_ptr);
    (*queue_head)->next_node = new_q_node_ptr;
    *queue_head = new_q_node_ptr;
  }
  return error_code;
}
