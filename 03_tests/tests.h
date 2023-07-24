#ifndef SMARTCALC_03_TESTS_TESTS_H_
#define SMARTCALC_03_TESTS_TESTS_H_

#include <check.h>
#include <stdlib.h>

#include "../console_calc.h"

Suite* test_push(void);
Suite* test_fill_node(void);
Suite* test_move_node(void);
Suite* test_close_bracket_processing(void);
Suite* test_end_of_expression_processing(void);
Suite* test_value_packer(void);
Suite* test_operator_packer(void);
Suite* test_function_packer(void);
Suite* test_container_packing(void);
Suite* test_container_sending(void);
Suite* test_token_processing(void);
Suite* test_errors_convert_infix_to_RPN(void);
Suite* test_convert_infix_to_RPN(void);
Suite* test_math_operations(void);
Suite* test_numerical_calculation(void);
Suite* test_evaluate_expression(void);

#endif // SMARTCALC_03_TESTS_TESTS_H_
