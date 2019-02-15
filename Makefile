NAME = lem-in
CFLAGS = -Wall -Wextra -Werror
src = $(wildcard *.c)
obj = $(src:.c=.o)
CC = gcc

all: libft/libft.a $(NAME)

$(NAME): $(obj)
	$(CC) $(CFLAGS) -g -o $(NAME) $(obj) -Llibft -lft
%.o: %.c
	$(CC) $(CFLAGS) -g -c $< -o $@ -I.
libft/libft.a:
	make -C libft/
clean:
	make -C libft/ clean
	rm -f $(obj)
fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)
re: fclean all