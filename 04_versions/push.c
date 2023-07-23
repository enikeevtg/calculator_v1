/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"

/// @brief the data adding to stack new node
/// @param s_phead pointer to head node pointer of stack
/// @param pdata data for new node of stack
/// @return error code
int stack_push(node_t** s_phead, node_t* pdata) {
  int error = OK;
  node_t* new_node_ptr = (node_t*)calloc(1, sizeof(node_t));
  if (new_node_ptr == NULL) {
    error = STACK_OVERFLOW;
  } else {
    new_node_ptr->pnext = *s_phead;
    fill_node(pdata, new_node_ptr);
    *s_phead = new_node_ptr;
  }
  return error;
}

/// @brief the data adding to queue new node
/// @param q_phead pointer to head node pointer of queue
/// @param pdata data for new node of stack
/// @return error code
int queue_push(node_t** q_phead, node_t* pdata) {
  int error = OK;
  node_t* new_node_ptr = (node_t*)calloc(1, sizeof(node_t));
  if (new_node_ptr == NULL) {
    error = QUEUE_OVERFLOW;
  } else {
    (*q_phead)->pnext = new_node_ptr;
    fill_node(pdata, new_node_ptr);
    *q_phead = new_node_ptr;
  }
  return error;
}
