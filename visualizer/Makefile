NAME=visu
LIB = ../libft/libft.a
FLAGS = -Werror -Wall -Wextra -g
SDLFLAGS = $(shell sdl2-config --cflags)
SDLLIB = $(shell sdl2-config --libs)
TTFFLAGS = -I~/.brew/Cellar/sdl2_ttf/2.0.14/include/SDL2
TFFLIB = -L~/.brew/Cellar/sdl2_ttf/2.0.14/lib
GCC = gcc
SRC=visu.c init.c readmap.c draw.c ../read_links.c ../read_links_utils.c ../tree.c ../tree_utils.c ../checking.c ../cmd.c ../check_input.c ../node.c ../utils.c ../ants.c ../graph.c ../graph_utils.c ../graph_utils2.c free.c
OBJI = $(SRC:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	make -C ../libft/ all
$(NAME): $(OBJI)
	$(GCC) $(OBJI) -o $(NAME) -L ../libft -lft $(FLAGS) $(SDLFLAGS) $(SDLLIB) $(TTFFLAGS) -lSDL2_ttf
%.o: %.c
	$(GCC) $(FLAGS) -c $< -o $@ $(SDLFLAGS) $(TTFFLAGS)
clean:
	rm -f *.o
	make -C ../libft/ clean
fclean: clean
	rm -f $(NAME)
	make -C ../libft/ fclean
re: fclean all
