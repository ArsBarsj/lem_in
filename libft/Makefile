NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
src = $(wildcard ft_*.c)
obj = $(src:.c=.o)
CC = gcc

all: $(NAME)

$(NAME): $(obj)
	ar rcs $(NAME) $(obj)
%.o: %.c
	$(CC) $(CFLAGS) -c -g $< -o $@ -I.
clean:
	rm -f $(obj)
fclean: clean
	rm -f $(NAME)
re: fclean all
tclean: clean
	rm -f test test.o
test: $(NAME) test.c
	$(CC) -c -g -o test.o test.c -I.
	$(CC) -g -o test test.o -L ./ -lftprintf
