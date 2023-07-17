/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

int operators_to_str(char* dest, char** operator);
int value_to_str(char* dest, char** number);
int function_to_str(char* dest, char** function);

int string_processing_v1(const char* str, char** tokens) {
  int error_code = OK;
  const char operators[] = "+-*/()^%";
  const char functions_first_letters[] = "cstal";
  const char numbers[] = "1234567890.";
  char* ptr = (char*)str;

  int token_index = 0;
  while (!error_code && *ptr != '\0') {
    if (strchr(operators, *ptr)) {
      error_code = operators_to_str(tokens[token_index], &ptr);
      token_index++;
    } else if (strchr(numbers, *ptr)) {
      error_code = value_to_str(tokens[token_index], &ptr);
      token_index++;
    } else if (strchr(functions_first_letters, *ptr)) {
      error_code = function_to_str(tokens[token_index], &ptr);
      token_index++;
    } else if (*ptr == ' ') {
      ptr++;
    } else {
      error_code = UNDEFINED_TOKEN;
    }
  }
}

int operators_to_str(char* dest, char** operator) {
  strncat(dest, *operator, 1);
  (*operator)++;
  return OK;
}

int value_to_str(char* dest, char** number) {
  const char numbers[] = "1234567890.";
  size_t number_length = strspn(*number, numbers);
  strncat(dest, *number, number_length);
  *number += number_length;
  return OK;
}

int function_to_str(char* dest, char** function) {
  int error_code = OK;
  FUNCTIONS_NAMES;
  char* bracket = strpbrk(*function, "(");
  *bracket = '\0';
  int i = 0;
  while (i < FUNCTIONS_NUMBER && strcmp(*function, functions_names[i])) i++;
  if (i == FUNCTIONS_NUMBER) {
    error_code = UNDEFINED_TOKEN;
  } else {
    strcat(dest, functions_names[i]);
    strcat(dest, "(");
    *bracket = '(';
    *function += strlen(functions_names[i]) + 1;
  }
  return error_code;
}
