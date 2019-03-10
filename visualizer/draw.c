#include "visu.h"

void    draw_line(t_visu *v, t_vlink *l, int mx, int my)
{
	SDL_SetRenderDrawColor(v->screen, 220, 0, 115, 255);
	SDL_RenderDrawLine(v->screen, l->startx + mx, l->starty + my,
			l->endx + mx, l->endy + my);
	SDL_RenderDrawLine(v->screen, l->startx + mx + 1, l->starty + my,
	                        l->endx + mx + 1, l->endy + my);
	SDL_RenderDrawLine(v->screen, l->startx + mx, l->starty + my + 1,
	                        l->endx + mx, l->endy + my + 1);
	SDL_RenderDrawLine(v->screen, l->startx + mx - 1, l->starty + my,
	                        l->endx + mx - 1, l->endy + my);
	SDL_RenderDrawLine(v->screen, l->startx + mx, l->starty + my - 1,
	                        l->endx + mx, l->endy + my - 1);
}

void    set_link_coord(t_vlink *l, t_visu *v, int i, int j)
{
	t_node *room;

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

void    draw_links(t_visu *v)
{
	int         i;
	int         j;
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

void    draw_room(t_visu *v, t_node *room) {
	v->place = init_coor(room->x, room->y, v->width_r, v->height_r);
	SDL_SetRenderDrawColor(v->screen, 47, 24, 71, 255);
	SDL_RenderFillRect(v->screen, &v->place);
}
