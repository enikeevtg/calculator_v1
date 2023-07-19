/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

int value_token(char* dest, char** number);
int operator_token(char* dest, char** operator);
int function_token(char* dest, char** function);

/// @brief string splitting
/// @param str source string
/// @param tokens array of token strings
/// @return error code
int split_string_to_tokens(const char* str, char** tokens) {
  int error_code = OK;

  NUMBERS_CHARS;
  OPERATORS_CHARS;
  FUNCTIONS_FIRST_LETTERS;

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
  FUNCTIONS_NAMES;
  char* char_after_function_ptr = strpbrk(*function, "(1234567890.");
  char char_after_function = *char_after_function_ptr;
  *char_after_function_ptr = '\0';
  int i = 0;
  while (i < FUNCTIONS_NUMBER && strcmp(*function, functions_names[i])) i++;
  if (i == FUNCTIONS_NUMBER) {
    error_code = UNDEFINED_TOKEN;
  } else {
    strcat(dest, functions_names[i]);
    *char_after_function_ptr = char_after_function;
    *function = char_after_function_ptr;
  }
  return error_code;
}
