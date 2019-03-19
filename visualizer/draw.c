/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreutel <ttreutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:15:48 by ttreutel          #+#    #+#             */
/*   Updated: 2019/03/19 18:18:05 by ttreutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	draw_line(t_visu *v, t_vlink *l, int mx, int my)
{
	SDL_SetRenderDrawColor(v->screen, 0, 0, 0, 255);
	SDL_RenderDrawLine(v->screen, l->startx + mx, l->starty + my,
			l->endx + mx, l->endy + my);
	SDL_RenderDrawLine(v->screen, l->startx + mx + 1, l->starty + my,
						l->endx + mx + 1, l->endy + my);
	SDL_RenderDrawLine(v->screen, l->startx + mx, l->starty + my + 1,
						l->endx + mx, l->endy + my + 1);
}

void	set_link_coord(t_vlink *l, t_visu *v, int i, int j)
{
	t_node	*room;

	room = v->config->head;
	while (room && room->id != i)
		room = room->next;
	if (!room)
		return ;
	l->startx = room->x;
	l->starty = room->y;
	room = v->config->head;
	while (room && room->id != j)
		room = room->next;
	if (!room)
		return ;
	l->endx = room->x;
	l->endy = room->y;
	v->config->links[i][j] = 0;
	v->config->links[j][i] = 0;
}

void	draw_links(t_visu *v)
{
	int		i;
	int		j;
	t_vlink tmp_link;

	i = 0;
	while (i < v->config->rooms_n)
	{
		j = 0;
		while (j < v->config->rooms_n)
		{
			if (v->config->links[i][j] == 1)
			{
				set_link_coord(&tmp_link, v, i, j);
				draw_line(v, &tmp_link, v->width_r / 2, v->height_r / 2);
			}
			j++;
		}
		i++;
	}
}

void	draw_line_path(t_visu *v, t_vlink *l, int mx, int my)
{
	SDL_SetRenderDrawColor(v->screen, 244, 66, 86, 255);
	SDL_RenderDrawLine(v->screen, l->startx + mx, l->starty + my,
						l->endx + mx, l->endy + my);
	SDL_RenderDrawLine(v->screen, l->startx + mx + 1, l->starty + my,
						l->endx + mx + 1, l->endy + my);
	SDL_RenderDrawLine(v->screen, l->startx + mx, l->starty + my + 1,
						l->endx + mx, l->endy + my + 1);
}

void	draw_paths(t_visu *v, t_path **paths, t_config *cfg)
{
	int		i;
	int		j;
	t_vlink	tmp_link;

	i = 0;
	while (paths[i])
	{
		tmp_link.startx = v->graph->nodes[cfg->start_id]->x;
		tmp_link.starty = v->graph->nodes[cfg->start_id]->y;
		tmp_link.endx = paths[i]->path[0]->x;
		tmp_link.endy = paths[i]->path[0]->y;
		draw_line_path(v, &tmp_link, v->width_r / 2, v->height_r / 2);
		j = 1;
		while (paths[i]->path[j])
		{
			tmp_link.startx = paths[i]->path[j - 1]->x;
			tmp_link.starty = paths[i]->path[j - 1]->y;
			tmp_link.endx = paths[i]->path[j]->x;
			tmp_link.endy = paths[i]->path[j]->y;
			draw_line_path(v, &tmp_link, v->width_r / 2, v->height_r / 2);
			j++;
		}
		i++;
	}
}
