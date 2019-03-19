/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreutel <ttreutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:14:20 by ttreutel          #+#    #+#             */
/*   Updated: 2019/03/19 18:15:01 by ttreutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	draw_id(t_visu *v, t_node *room)
{
	SDL_Surface	*text;

	if (TTF_SizeUTF8(v->font, room->name, &v->place.w, &v->place.h) == -1)
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

void	draw_room(t_visu *v, t_node *room)
{
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
