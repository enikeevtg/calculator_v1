/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../console_calc.h"
node_t* create_new_node(node_t* pdata, node_t* next);

/// @brief stack and queue common function for data adding to new node
/// @version v.2
/// @param address STACK or QUEUE structure
/// @param phead head of structure
/// @param pdata
/// @return error code
int push(int address, node_t** phead, node_t* pdata) {
  int error = DATA_STRUCT_OVERFLOW;

  if (address == STACK || *phead == NULL) {
    *phead = create_new_node(pdata, *phead);
  } else if (address == QUEUE) {
    (*phead)->pnext = create_new_node(pdata, NULL);
    *phead = (*phead)->pnext;
  }
  if (*phead != NULL) error = OK;
  return error;
}

node_t* create_new_node(node_t* pdata, node_t* next) {
  node_t* pnew_node = (node_t*)calloc(1, sizeof(node_t));
  if (pnew_node) {
    pnew_node->pnext = next;
    fill_node(pdata, pnew_node);
  }
  return pnew_node;
}
