#include "visu.h"

void draw_room(t_visu *v, t_node *room) {
	v->place = init_coor(room->x, room->y, v->width_r, v->height_r);
	SDL_SetRenderDrawColor(v->screen, 47, 24, 71, 255);
	SDL_RenderFillRect(v->screen, &v->place);
}
