# UTILITIES
CC = gcc
LEAKS =# leaks -atExit --
RM = rm -rf

# UTILITIES OPTIONS
CF = -Wall -Werror -Wextra
DEBUG = -DDEBUG

# FILENAMES
DATA_STRUCT_DIR = ./01_data_structs/
CALC_DIR = ./02_calculations/
SRC = $(wildcard $(DATA_STRUCT_DIR)*.c)
SRC += $(wildcard $(CALC_DIR)*.c)
TESTS_DIR = ./03_tests/

build: clean
	$(CC) $(CF) main.c $(SRC) -o calculator

calc:
	./calculator

tmp: clean
	gcc $(TESTS_DIR)man_test_split_string_to_tokens.c $(SRC)*.c $(DEBUG)
	./a.out

# SERVICES
style:
	clang-format --style=google -n *.h *.c $(SRC)

gost:
	clang-format --style=google -i *.h *.c $(SRC)

clean:
	$(RM) a.out
