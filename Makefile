CC = gcc
RM = rm -rf

tmp:
	@gcc structures.c
	@./a.out
	@$(RM) a.out


# SERVICES
style:
	clang-format --style=google -n *.h *.c

gost:
	clang-format --style=google -i *.h *.c

clean:
	$(RM) a.out
