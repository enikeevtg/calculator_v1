# UTILITIES
CC = gcc
LEAKS =# leaks -atExit --
RM = rm -rf

# FILENAMES
SRC_DIR = ./src/
SRC = $(wildcard $(SRC_DIR)*.c)

tmp:
#	gcc test_structures.c $(SRC_DIR)*.c
	gcc test_parsing_v1.c $(SRC_DIR)*.c
	$(LEAKS) ./a.out
	$(RM) a.out


# SERVICES
style:
	clang-format --style=google -n *.h *.c $(SRC)

gost:
	clang-format --style=google -i *.h *.c $(SRC)

clean:
	$(RM) a.out
