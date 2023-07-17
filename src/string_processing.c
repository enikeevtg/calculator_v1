/**
 * @author T. Enikeev
 * enikeeev.tg@gmail.com
 */

#include "../smart_calc.h"

char* operators_to_str(char* dest, char* operator);
char* value_to_str(char* dest, char* number);
char* function_to_str(char* dest, char* function);




void string_processing(const char* str/*, node_t** s_head, node_t** q_head */) {
  int error = 0;
  const char operators[] = "+-*/()^%";
  const char functions[] = "cstal";
  const char numbers[] = "1234567890.";
  char* ptr = (char*)str;
  
  size_t tmp_str_arr_size = 11 * sizeof(char*) + 11 * 5 * sizeof(char);
  char** tmp_str_arr = (char**)calloc(tmp_str_arr_size, 1);
  char* start = (char*)tmp_str_arr + 11 * sizeof(char*);
  for (int i = 0; i < 11; i++) tmp_str_arr[i] = start + i * 5 * sizeof(char*);
  printf("tmp_str_arr address: %p\n", tmp_str_arr);

  int str_index = 0;
  while (!error && *ptr != '\0') {
    // int str_index_length = 0;
    if (strchr(operators, *ptr)) {
      ptr = operators_to_str(tmp_str_arr[str_index], ptr);
      str_index++;
    }
    else if (strchr(numbers, *ptr)) {
      ptr = value_to_str(tmp_str_arr[str_index], ptr);
      str_index++;
    } else if (strchr(functions, *ptr)) {
      ptr = function_to_str(tmp_str_arr[str_index], ptr);
      str_index++;
    } else if (*ptr == ' ') {
      ptr++;
    }
    // else
    //   for (int i = 0; i < 4; i++) 
    //   error = 1;
    // if (!error && str_index_length != 0 && *ptr != ' ') {
    //   strncat(tmp_str_arr[str_index], ptr, str_index_length);
    //   str_index++;
    // } else if (!error) {
    //   ptr++;
    // }
    // ptr += str_index_length;
  }

  if (error)
    printf("error input!\n");
  else {
    int i = 0;
    while (tmp_str_arr[i][0] != '\0') {
      printf(" %s    ", tmp_str_arr[i]);
      i++;
    }
  }
    

  free(tmp_str_arr);
}


char* operators_to_str(char* dest, char* operator) {
  strncat(dest, operator, 1);
  return ++operator;
}

char* value_to_str(char* dest, char* number) {
  const char numbers[] = "1234567890.";
  size_t number_length = strspn(number, numbers);
  strncat(dest, number, number_length);
  return number + number_length;
}

char* function_to_str(char* dest, char* function) {
  const char functions[5][5] = {"cos(", "sin(", "tan(", "log(", "ln("};

  return;
}
