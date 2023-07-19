#include "smart_calc.h"

int tokens_array_alloc(char*** tokens_array, size_t tokens_array_size,
                       int tokens_number, int token_max_length);

int main() {
  char input_str[255] = "(-123.123456 + 321) / 23 * 1% sin18 * ln(11)";
  printf("source string: \"%s\"\n", input_str);

  char** tokens_array;
  int tokens_number = 32;
  int token_max_length = 11;
  size_t tokens_array_size = tokens_number * sizeof(char*) +
                             tokens_number * token_max_length * sizeof(char);
  int error_code = tokens_array_alloc(&tokens_array, tokens_array_size,
                                      tokens_number, token_max_length);

  if (error_code == OK)
    error_code = split_string_to_tokens(input_str, tokens_array);

  if (error_code == OK) {
    printf("tokens:\n");
    int i = 0;
    while (tokens_array[i][0] != '\0') {
      printf("\t#%2d:  \"%s\"\n", i + 1, tokens_array[i]);
      i++;
    }
    printf("\n");
  } else {
    printf("error_code: %d\n", error_code);
  }

  free(tokens_array);

  return 0;
}

int tokens_array_alloc(char*** tokens_array, size_t tokens_array_size,
                       int tokens_number, int token_max_length) {
  int error_code = OK;
  *tokens_array = (char**)calloc(tokens_array_size, 1);
  if (*tokens_array == NULL) {
    error_code = MEMORY_ACCESS_ERROR;
  } else {
    char* first_token = (char*)*tokens_array + tokens_number * sizeof(char*);
    for (int i = 0; i < tokens_number; i++)
      (*tokens_array)[i] = first_token + i * token_max_length * sizeof(char*);
  }
  return error_code;
}
