# UTILITIES
CC = gcc
LEAKS =# leaks -atExit -- #
RM = rm -rf

# UTILITIES OPTIONS
CF = -Wall -Werror -Wextra
DEBUG = -DDEBUG

# FILENAMES
ATTEMPT_DIR = ./00_attempt_at_writing/
DATA_STRUCT_DIR = ./01_data_structs_processing/
EVAL_DIR = ./02_evaluations/
SRC = $(wildcard $(DATA_STRUCT_DIR)*.c)
SRC += $(wildcard $(EVAL_DIR)*.c)
TESTS_DIR = ./03_tests/

build: clean
	$(CC) $(CF) main.c $(SRC) -o calculator

calc:
	$(LEAKS)./calculator

tmp: clean
	$(CC) $(ATTEMPT_DIR)*.c $(SRC) $(DEBUG)
	$(LEAKS)./a.out

# SERVICES
style:
	clang-format --style=google -n *.h *.c $(SRC)

gost:
	clang-format --style=google -i *.h *.c $(SRC)

clean:
	$(RM) a.out
