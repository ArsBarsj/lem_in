#include "visu.h"

void    free_visu(t_visu *v)
{
	config_del(v->config);
	free(v->fileline);
	if (v->window)
		SDL_DestroyWindow(v->window);
	if (v->screen)
		SDL_DestroyRenderer(v->screen);
	SDL_Quit();
}

