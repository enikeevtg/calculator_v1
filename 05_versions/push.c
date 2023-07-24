/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

/// @brief stack and queue common function for data adding to new node
/// @version v.1
/// @param address STACK or QUEUE structure
/// @param phead head of structure
/// @param pdata
/// @return error code
int push_v2(int address, node_t** phead, node_t* pdata) {
  int error = DATA_STRUCT_OVERFLOW;
  node_t* new_node_ptr = (node_t*)calloc(1, sizeof(node_t));
  if (new_node_ptr != NULL) {
    error = OK;
    if (address == STACK) new_node_ptr->pnext = *phead;
    if (address == QUEUE && *phead != NULL) (*phead)->pnext = new_node_ptr;
    fill_node(pdata, new_node_ptr);
    *phead = new_node_ptr;
  }
  return error;
}

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
