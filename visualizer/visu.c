#include "../lemin.h"
#include "../datatypes.h"
#include "visu.h"
#include <stdio.h>

void	ft_init_sdl_screen(t_visu *visu)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit(2);
	if ((visu->window = SDL_CreateWindow("lem-in map", 
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200,
					1000,  SDL_WINDOW_SHOWN)) == NULL)
		exit(2);
	if ((visu->screen = SDL_CreateRenderer(visu->window, -1, 0)) == NULL)
		exit(2);
	if(TTF_Init()==-1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
	visu->font = TTF_OpenFont("/home/arseny/school21/Lem-in/visualizer/font.ttf", 14);
	if (visu->font == NULL)
		printf("AAAAAAAAbbbbbbbAAAAAAAAAAAAAAAA\n");
	SDL_SetRenderDrawColor(visu->screen, 96, 128, 255, 255);
	SDL_RenderClear(visu->screen);
}

void    ft_loop_it(t_visu *v)
{
	int     loop;

	SDL_RenderPresent(v->screen);
	loop = 1;
	while (loop)
	{
		if (SDL_PollEvent(&(v->event)))
		{
			if (v->event.type == SDL_QUIT)
				loop = 0;
		}
		if (loop == 0)
			break ;
		SDL_Delay(16);
	}
}

int main(int ac, char **av)
{
	t_visu		*visu;

	(void)ac;
	visu = (t_visu *)malloc(sizeof(t_visu));
	int fd = open(av[1], O_RDONLY);
	init_visu(visu);
	if (!read_file(visu, fd))
		return (1);
	ft_init_sdl_screen(visu);
	draw_links(visu);
	while (visu->config->head)
	{
		draw_room(visu, visu->config->head);
		visu->config->head = visu->config->head->next;
	}
	ft_loop_it(visu);
	free_visu(visu);
	return (0);
}
