#include "../lemin.h"
#include "../datatypes.h"
#include "visu.h"
#include <stdio.h>

void	ft_init_sdl_screen(t_visu *visu)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		exit(2);
	if ((visu->window = SDL_CreateWindow("lem-in map", 
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000,
					1000,  SDL_WINDOW_SHOWN)) == NULL)
		exit(2);
	if ((visu->screen = SDL_CreateRenderer(visu->window, -1, 0)) == NULL)
		exit(2);
}

int main(int ac, char **av)
{
	t_visu		visu;
	int			loop;

	(void)ac;
	int fd = open(av[1], O_RDONLY);
	init_visu(&visu);
	read_file(&visu, fd);
	ft_init_sdl_screen(&visu);
	SDL_SetRenderDrawColor(visu.screen, 96, 128, 255, 255);
	SDL_RenderClear(visu.screen);
	while (visu.config->head)
	{
		draw_room(&visu, visu.config->head);
		visu.config->head = visu.config->head->next;
	}
	loop = 1;
	while (loop)
	{
		if (SDL_PollEvent(&(visu.event)))
		{
			if (visu.event.type == SDL_QUIT)
				loop = 0;
		}
		if (loop == 0)
			break ;
		SDL_RenderPresent(visu.screen);
		SDL_Delay(16);
	}
	SDL_DestroyRenderer(visu.screen);
	SDL_DestroyWindow(visu.window);
	SDL_Quit();
	return (0);
}
