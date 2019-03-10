#include "../lemin.h"
#include "../datatypes.h"
#include "visu.h"

void	init_visu(t_visu *visu)
{
	visu->window = NULL;
	visu->screen = NULL;
	visu->fileline = NULL;
	visu->tabfile = NULL;
	visu->config = (t_config *)malloc(sizeof(t_config));
	ft_init_config(&visu->config);
	visu->height_r = 50;
	visu->width_r = 50;
	visu->text_color = init_color(255, 255, 255, 255);
	// visu->place = NULL;
}

SDL_Rect	init_coor(int x, int y, int w, int h)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

SDL_Color	init_color(int r, int g, int b, int a)
{
	SDL_Color	color;

	color.r = (Uint8)r;
	color.g = (Uint8)g;
	color.b = (Uint8)b;
	color.a = (Uint8)a;
	return (color);
}