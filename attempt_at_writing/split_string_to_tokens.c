/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "attempt_at_writing.h"

int value_token(char* dest, char** number);
int operator_token(char* dest, char** operator);
int function_token(char* dest, char** function);

/// @brief string splitting
/// @param str source string
/// @param tokens array of token strings
/// @return error code
int split_string_to_tokens(const char* str, char** tokens) {
  int error_code = OK;

  const char numbers_chars[] = "1234567890.";
  const char operators_chars[] = "+-*/^%()";
  const char functions_first_letters[] = "cstal";

  char* ptr = (char*)str;

  int token_index = 0;
  while (!error_code && *ptr != '\0') {
    if (strchr(numbers_chars, *ptr)) {
      error_code = value_token(tokens[token_index], &ptr);
      token_index++;
    } else if (strchr(operators_chars, *ptr)) {
      error_code = operator_token(tokens[token_index], &ptr);
      token_index++;
    } else if (strchr(functions_first_letters, *ptr)) {
      error_code = function_token(tokens[token_index], &ptr);
      token_index++;
    } else if (*ptr == ' ') {
      ptr++;
    } else {
      error_code = UNDEFINED_TOKEN;
    }
  }
  return error_code;
}

int value_token(char* dest, char** number) {
  const char numbers[] = "1234567890.";
  size_t number_length = strspn(*number, numbers);
  strncat(dest, *number, number_length);
  *number += number_length;
  return OK;
}

int operator_token(char* dest, char** operator) {
  strncat(dest, *operator, 1);
  (*operator)++;
  return OK;
}

int function_token(char* dest, char** function) {
  int error_code = OK;
  char* bracket = strchr(*function, '(');
  char* after_function_char_ptr = strpbrk(*function, "(1234567890.+-*/^%");
  if (bracket == NULL || bracket > after_function_char_ptr)
    error_code = INCORRECT_INPUT;

  MATH_FUNCTIONS_NAMES;
  char after_function_char = '\0';
  if (after_function_char_ptr != NULL) {
    after_function_char = *after_function_char_ptr;
    *after_function_char_ptr = '\0';
  }
  int i = 0;
  while (i < MATH_FUNCTIONS_NUMBER &&
         strcmp(*function, math_functions_names[i]))
    i++;
  if (i == MATH_FUNCTIONS_NUMBER) {
    error_code = UNDEFINED_TOKEN;
  } else {
    strcat(dest, math_functions_names[i]);
    if (after_function_char_ptr != NULL)
      *after_function_char_ptr = after_function_char;
    *function = after_function_char_ptr;
  }
  return error_code;
}
