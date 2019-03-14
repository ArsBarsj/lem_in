SRCI = read.c check_input.c utils.c node.c cmd.c graph.c bfs_algs.c bfs_alg_utils.c bfs_alg_utils2.c ants.c bfs.c queue.c path.c path_utils.c get_lines_utils.c tree.c read_links.c read_links_utils.c graph_utils.c graph_utils2.c checking.c tree_utils.c bfs_utils.c
OBJI = $(SRCI:.c=.o)
LIB = libft/libft.a
FLAGS = -Werror -Wall -Wextra
GCC = gcc
NAME = lem-in

all: $(LIB) $(NAME)

$(LIB):
	@make -C libft/ all
$(NAME): $(OBJI)
	@$(GCC) $(FLAGS) $(OBJI) -L libft -lft -o $(NAME)
%.o: %.c
	@$(GCC) $(FLAGS) -c -g $< -o $@ -I.
clean:
	rm -f *.o
	make -C libft/ clean
fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
re: fclean all
