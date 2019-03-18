#include "visu.h"

void    free_visu(t_visu *v)
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
	if (v->init_SDL == 1)
		SDL_Quit();
	if (v->init_TTF == 1)
		TTF_Quit();
	exit(1);
}

