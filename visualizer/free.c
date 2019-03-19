/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreutel <ttreutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:18:25 by ttreutel          #+#    #+#             */
/*   Updated: 2019/03/19 18:51:21 by ttreutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	free_visu(t_visu *v)
{
	if (v->fileline != NULL)
		free(v->fileline);
	if (v->graph)
		graph_del(&v->graph);
	if (v->paths)
		paths_del(&v->paths);
	if (v->init_screen == 1)
		SDL_DestroyRenderer(v->screen);
	if (v->init_window == 1)
		SDL_DestroyWindow(v->window);
	if (v->init_ttf == 1)
		TTF_Quit();
	if (v->init_sdl == 1)
		SDL_Quit();
	exit(1);
}
