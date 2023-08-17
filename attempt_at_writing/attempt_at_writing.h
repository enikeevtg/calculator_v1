#ifndef CONSOLE_CALC_00_ATTEMPT_AT_WRITING_00_ATTEMPT_AT_WRITING_H_
#define CONSOLE_CALC_00_ATTEMPT_AT_WRITING_00_ATTEMPT_AT_WRITING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum error_codes {
  OK,
  UNDEFINED_TOKEN,
  DATA_STRUCT_UNDERFLOW,
  DATA_STRUCT_OVERFLOW,
  TOO_LONG_STRING,
  EMPTY_EXPRESSION,
  MEMORY_ACCESS_ERROR,  // ! test_split_string_to_tokens.c
  UNBALANCED_BRACKETS,
  EMPTY_BRACKETS,
  INCORRECT_INPUT,
  EMPTY_QUEUE,
  STACK_UNDERFLOW,  // ! push.c
  STACK_OVERFLOW,   // ! push.c
  QUEUE_OVERFLOW,   // ! push.c
  INCORRECT_FUNCTION_ARGUMENT
};

#define ERRORS_MESSAGES_NUMBERS 15
#define ERRORS_MESSAGE_MAX_SIZE 28
#define ERRORS_MESSAGES                                                 \
  char errors_msg[ERRORS_MESSAGES_NUMBERS][ERRORS_MESSAGE_MAX_SIZE] = { \
      "OK",                                                             \
      "UNDEFINED_TOKEN",                                                \
      "DATA_STRUCT_UNDERFLOW",                                          \
      "DATA_STRUCT_OVERFLOW",                                           \
      "TOO_LONG_STRING",                                                \
      "EMPTY_EXPRESSION",                                               \
      "MEMORY_ACCESS_ERROR",                                            \
      "UNBALANCED_BRACKETS",                                            \
      "EMPTY_BRACKETS",                                                 \
      "INCORRECT_INPUT",                                                \
      "EMPTY_QUEUE",                                                    \
      "STACK_UNDERFLOW",                                                \
      "STACK_OVERFLOW",                                                 \
      "QUEUE_OVERFLOW",                                                 \
      "INCORRECT_FUNCTION_ARGUMENT"}

#define MATH_FUNCTIONS_NUMBER 9
#define MATH_FUNCTIONS_NAMES_LENGTH 5
#define MATH_FUNCTIONS_NAMES                                   \
  const char math_functions_names                              \
      [MATH_FUNCTIONS_NUMBER][MATH_FUNCTIONS_NAMES_LENGTH] = { \
          "cos",  "sin",  "tan", "acos", "asin",               \
          "atan", "sqrt", "ln",  "log"}  // sequence is the same that in
                                         // "typedef enum token_type {...}
                                         // token_t"

int split_string_to_tokens(const char* str, char** tokens);

#endif  // CONSOLE_CALC_00_ATTEMPT_AT_WRITING_00_ATTEMPT_AT_WRITING_H_
