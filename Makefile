# UTILITIES
CC = gcc
LEAKS =# leaks -atExit --
RM = rm -rf

# UTILITIES OPTIONS
DEBUG = -DDEBUG

# FILENAMES
SRC_DIR = ./src/
SRC = $(wildcard $(SRC_DIR)*.c)

tmp: clean
#	gcc test_structures.c $(SRC_DIR)*.c
#	gcc test_split_string_to_tokens.c $(SRC_DIR)*.c $(DEBUG)
	gcc test_convert_infix_to_RPN.c $(SRC_DIR)*.c $(DEBUG)
#	gcc test_expression_solver.c $(SRC_DIR)*.c $(DEBUG)
	$(LEAKS) ./a.out


# SERVICES
style:
	clang-format --style=google -n *.h *.c $(SRC)

gost:
	clang-format --style=google -i *.h *.c $(SRC)

clean:
	$(RM) a.out
