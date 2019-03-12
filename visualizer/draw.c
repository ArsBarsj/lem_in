#include "visu.h"
#include <stdio.h>
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

void    draw_id(t_visu *v, t_node *room)
{
	SDL_Surface     *text;

	text = NULL;
	if (v->font == NULL)
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	if (TTF_SizeText(v->font, ft_itoa(room->id), &v->place.w, &v->place.h) == -1)
		exit(2);
	if ((v->place.x = room->x + ((v->width_r - v->place.w) / 2)) < 0)
		v->place.x = 0;
	if ((v->place.y = room->y + (v->height_r - v->place.h) / 2) < 0)
		v->place.x = 0;
	text = TTF_RenderText_Blended(v->font, room->name, v->text_color);
	v->texture = SDL_CreateTextureFromSurface(v->screen, text);
	SDL_RenderCopy(v->screen, v->texture, NULL, &v->place);
	SDL_FreeSurface(text);
	SDL_DestroyTexture(v->texture);
}

void    draw_room(t_visu *v, t_node *room) {
	v->place = init_coor(room->x, room->y, v->width_r, v->height_r);
	if (v->config->start_id == room->id)
		SDL_SetRenderDrawColor(v->screen, 120, 188, 97, 255);
	else if (v->config->end_id == room->id)
		SDL_SetRenderDrawColor(v->screen, 199, 62, 29, 255);
	else
		SDL_SetRenderDrawColor(v->screen, 47, 24, 71, 255);
	SDL_RenderFillRect(v->screen, &v->place);
	draw_id(v, room);
}
