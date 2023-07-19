/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

int cos_solver(node_t** s_head) {
  double tmp = (*s_head)->token_value;
  (*s_head)->token_value = cos(tmp);
  return OK;
}

int sin_solver(node_t** s_head) {
  double tmp = (*s_head)->token_value;
  (*s_head)->token_value = sin(tmp);
  return OK;
}

int tan_solver(node_t** s_head) {
  double tmp = (*s_head)->token_value;
  (*s_head)->token_value = tan(tmp);
  return OK;
}

int acos_solver(node_t** s_head) {
  if (fabs((*s_head)->token_value > 1)) return ACOS + 100;

  double tmp = (*s_head)->token_value;
  (*s_head)->token_value = tan(tmp);
  return OK;
}
