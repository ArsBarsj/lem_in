NAME=visu
LIB = ../libft/libft.a
FLAGS = -Werror -Wall -Wextra -g
GCC = gcc
SRC=visu.c init.c readmap.c draw.c ../read_links.c ../read_links_utils.c ../tree.c ../tree_utils.c ../checking.c ../cmd.c ../check_input.c ../node.c ../utils.c ../ants.c ../graph.c ../graph_utils.c ../graph_utils2.c
OBJI = $(SRC:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	@make -C ../libft/ all
$(NAME): $(OBJI)
	@$(GCC) $(FLAGS) $(OBJI) -lSDL2 -lSDL_ttf -L ../libft -lft -o $(NAME)
%.o: %.c
	@$(GCC) $(FLAGS) -c -g $< -o $@ -I.
clean:
	rm -f *.o
	make -C ../libft/ clean
fclean: clean
	rm -f $(NAME)
	make -C ../libft/ fclean
re: fclean all
