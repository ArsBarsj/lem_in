#ifndef LEM_IN_VISU_H
# define LEM_IN_VISU_H
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_ttf.h>
# include "../libft/libft.h"
# include "../datatypes.h"
#include "../lemin.h"

typedef struct 		s_visu
{
	SDL_Window		*window;
	SDL_Renderer	*screen;
	SDL_Event	    event;
	SDL_Color       text_color;
	SDL_Texture     *texture;
	TTF_Font        *font;
	char			*fileline;
	char			**tabfile;
	t_config		*config;
	t_graph         *graph;
	t_path          **paths;
	t_path          **best;
	int				height_r;
	int				width_r;
	SDL_Rect		place;
	int             init_SDL;
	int             init_window;
	int             init_screen;
	int             init_TTF;
	int             init_font;
	int             init_read;
}					t_visu;

typedef struct      s_vlink
{
	int             startx;
	int             starty;
	int             endx;
	int             endy;
}                   t_vlink;

void				init_visu(t_visu *visu);
int    				read_file(t_visu *visu, int fd);
int					str_remalloc(char **str, char *new_s, int size, int used);
char				*read_all_file(int fd, char *buf, int buf_siz);
int					ft_read_ants(char **line, t_config **config, int fd);
int					ft_read_rooms(char **line, t_config **config, int fd, int flag[2]);
int					ft_config(int fd, t_config **config, char **line);
SDL_Rect			init_coor(int x, int y, int w, int h);
SDL_Color	        init_color(int r, int g, int b, int a);
void                draw_links(t_visu *v);
void                draw_paths(t_visu *v, t_path **paths, t_config *cfg);
void				draw_room(t_visu *v, t_node *room);
void                free_visu(t_visu *v);
void	            config_del(t_config *config);
#endif
