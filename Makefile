.PHONY: all test gcov gcov_report style gost clean

# UTILITIES
CC = gcc
MK = mkdir -p
RM = rm -rf
OS := $(shell uname)
ifeq ($(OS), Darwin)
#	LEAKS = CK_FORK=no leaks --atExit --
	REPORT_OPEN = open
else ifeq ($(OS), Linux)
	LEAKS =
	REPORT_OPEN = xdg-open
endif

# UTILITIES OPTIONS
DEBUG = -DDEBUG
CF = -Wall -Werror -Wextra
STD = -std=c11 -pedantic
ASAN = -g -fsanitize=address
ifeq ($(OS), Darwin)
	TEST_FLAGS = -lcheck
else ifeq ($(OS), Linux)
	TEST_FLAGS = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

# FILENAMES
ATTEMPT_DIR = ./attempt_at_writing/

SRC_DIR = ./src/
DATA_STRUCT_DIR = $(SRC_DIR)01_data_structs_processing/
EVAL_DIR = $(SRC_DIR)02_evaluations/
SRC = $(wildcard $(DATA_STRUCT_DIR)*.c)
SRC += $(wildcard $(EVAL_DIR)*.c)

MAN_TESTS_DIR = ./man_tests/
TESTS_DIR = ./tests/
TESTS_SRC = $(wildcard $(TESTS_DIR)*.c)
TEST_EXE = ./tests_run
EXE = ./calculator

all: build launch

build: clean
	$(CC) $(CF) $(SRC_DIR)main.c $(SRC) -o $(EXE)

launch:
	$(LEAKS)$(EXE)

# TESTS
man_test: clean
#	$(CC) $(ATTEMPT_DIR)*.c $(DEBUG)
#	$(CC) $(MAN_TESTS_DIR)test_structures.c $(SRC)
#	$(CC) $(MAN_TESTS_DIR)test_convert_infix_to_RPN.c $(SRC) $(DEBUG)
	$(CC) $(MAN_TESTS_DIR)test_evaluate_expression.c $(SRC) $(DEBUG)
	$(LEAKS)./a.out

test: clean
	@$(CC) $(CF) $(ASAN) $(TESTS_SRC) $(SRC) -o $(TEST_EXE) $(TEST_FLAGS)
	@$(LEAKS) $(TEST_EXE)

gcov: gcov_report

gcov_report: clean
	@$(CC) $(CF) $(GCOV_FLAGS) $(ASAN) $(TESTS_SRC) $(SRC) -o $(TEST_EXE) $(TEST_FLAGS)
	@$(LEAKS) $(TEST_EXE)
	@lcov -t "./gcov" -o report.info --no-external -c -d .
	@genhtml -o report report.info
	@gcovr -r . --html-details -o ./report/coverage_report.html
	@$(REPORT_OPEN) ./report/index.html
	@rm -rf *.gcno *.gcda gcov_test *.info

# SERVICES
style:
	clang-format --style=google -n *.h *.c $(SRC)

gost:
	clang-format --style=google -i *.h *.c $(SRC)

clean:
	@$(RM) a.out
	@$(RM) *.gcno *.gcda
	@$(RM) *.dSYM
	@$(RM) ./report/
	@$(RM) $(TEST_EXE)
	@$(RM) $(EXE)
