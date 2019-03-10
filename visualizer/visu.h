//
// Created by arseny on 06.03.19.
//

#ifndef LEM_IN_VISU_H
# define LEM_IN_VISU_H
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include "../libft/libft.h"
# include "../datatypes.h"

typedef struct      s_room
{
	int             x;
	int             y;
	int             id;
	char            *name;
	struct s_room   *next;
}                   t_room;

typedef struct 		s_visu
{
	SDL_Window		*window;
	SDL_Renderer	*screen;
	SDL_Event	    event;
	SDL_Texture     *texture;
	SDL_Color       text_color;
	char			*fileline;
	char			*tabfile;
	t_config		*config;
	int				height_r;
	int				width_r;
	SDL_Rect		place;

}					t_visu;

void				init_visu(t_visu *visu);
void				read_file(t_visu *visu, int fd);
int					str_remalloc(char **str, char *new_s, int size, int used);
char				*read_all_file(int fd, char *buf, int buf_siz);
int					ft_read_ants(char **line, t_config **config, int fd);
int					ft_read_rooms(char **line, t_config **config, int fd, int flag[2]);
int					ft_config(int fd, t_config **config);
SDL_Rect			init_coor(int x, int y, int w, int h);
SDL_Color	        init_color(int r, int g, int b, int a);
void				draw_room(t_visu *v, t_node *room);
#endif
