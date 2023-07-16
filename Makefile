# UTILITIES
CC = gcc
LEAKS =# leaks -atExit --
RM = rm -rf

# FILENAMES
SRC_DIR = ./src/

tmp:
	@gcc structures.c $(SRC_DIR)*.c
	@$(LEAKS) ./a.out
	@$(RM) a.out


# SERVICES
style:
	clang-format --style=google -n *.h *.c

gost:
	clang-format --style=google -i *.h *.c

clean:
	$(RM) a.out
