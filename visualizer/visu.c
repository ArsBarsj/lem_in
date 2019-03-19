/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreutel <ttreutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:22:24 by ttreutel          #+#    #+#             */
/*   Updated: 2019/03/19 18:32:18 by ttreutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	ft_init_sdl_screen(t_visu *visu)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		free_visu(visu);
	visu->init_sdl = 1;
	if ((visu->window = SDL_CreateWindow("lem-in map",
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2000, 1200,
									SDL_WINDOW_SHOWN)) == NULL)
		free_visu(visu);
	visu->init_window = 1;
	if ((visu->screen = SDL_CreateRenderer(visu->window, -1, 0)) == NULL)
		free_visu(visu);
	visu->init_screen = 1;
	if (TTF_Init() == -1)
	{
		ft_printf("TTF_Init: %s\n", TTF_GetError());
		free_visu(visu);
	}
	visu->init_ttf = 1;
	visu->font = TTF_OpenFont("visualizer/font.ttf", 14);
	if (visu->font == NULL)
		free_visu(visu);
	visu->init_font = 1;
	SDL_SetRenderDrawColor(visu->screen, 96, 128, 255, 255);
	SDL_RenderClear(visu->screen);
}

void	ft_loop_it(t_visu *v)
{
	int		loop;

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

int		main(void)
{
	t_visu		*visu;

	visu = (t_visu *)malloc(sizeof(t_visu));
	init_visu(visu);
	if (!(visu->init_read = read_file(visu, 0)))
		free_visu(visu);
	ft_init_sdl_screen(visu);
	draw_links(visu);
	draw_paths(visu, visu->paths, visu->config);
	while (visu->config->head)
	{
		draw_room(visu, visu->config->head);
		visu->config->head = visu->config->head->next;
	}
	config_del(visu->config);
	ft_loop_it(visu);
	free_visu(visu);
	return (0);
}

void	make_path(t_visu *visu, int i)
{
	while (visu->tabfile[i])
	{
		if (!ft_strcmp(visu->tabfile[i], "ERROR!"))
			free_visu(visu);
		i++;
	}
	ft_clean_str_arr(visu->tabfile);
	visu->graph = graph_create(visu->config);
	visu->best = bfs_ways2(visu->config->start_id, visu->config->end_id,
							visu->graph);
	visu->paths = solve_inner2(visu->graph, visu->config, visu->best,
					get_lines_n(visu->best, visu->config->ants));
}
