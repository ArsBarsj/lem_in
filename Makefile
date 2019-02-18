SRCI = read.c check_input.c utils.c
OBJI = $(SRCI:.c=.o)
LIB = libft/libft.a
FLAGS = -Werror -Wall -Wextra
GCC = gcc
NAME = lem_in

all: $(LIB) $(NAME)

$(LIB):
	make -C libft/ all
$(NAME): $(OBJI)
	$(GCC) $(FLAGS) $(OBJI) -L libft -lft -o $(NAME)
%.o: %.c
	$(GCC) $(FLAGS) -c $< -o $@ -I.
clean:
	rm -f *.o
	make -C libft/ clean
fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
re: fclean all
