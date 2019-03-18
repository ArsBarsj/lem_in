#include "visu.h"

void	init_visu(t_visu *visu)
{
	visu->window = NULL;
	visu->screen = NULL;
	visu->texture = NULL;
	visu->fileline = NULL;
	visu->tabfile = NULL;
	visu->config = (t_config *)malloc(sizeof(t_config));
	visu->graph = NULL;
	visu->paths = NULL;
	visu->best = NULL;
	ft_init_config(&visu->config);
	visu->height_r = 25;
	visu->width_r = 40;
	visu->text_color = init_color(255, 255, 255, 255);
	visu->init_SDL = 0;
	visu->init_window = 0;
	visu->init_screen = 0;
	visu->init_TTF = 0;
	visu->init_font = 0;
	visu->init_read = 0;
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

int			ft_read_ants(char **line, t_config **config, int fd)
{
	while (get_next_line(fd, line) > 0 && (ft_is_comm(*line)
	                                       || ft_is_cmd(*line)))
	{
		ft_printf("%s\n", *line);
		if (ft_is_start(*line))
		{
			free(*line);
			return (0);
		}
		free(*line);
	}
	if (line && *line)
		ft_putstr(*line);
	ft_putchar('\n');
	if (*line && ft_check_ant(*line))
	{
		(*config)->ants = ft_atoi(*line);
		free(*line);
		return (1);
	}
	free(*line);
	return (0);
}

int			ft_read_rooms(char **line, t_config **config, int fd, int flag[2])
{
	int		id;
	t_node	*prev;

	id = 0;
	prev = NULL;
	while (get_next_line(fd, line) > 0 && ft_check(line))
	{
		ft_printf("%s\n", *line);
		if (is_error(line, config, id, flag))
			return (0);
		else if (ft_is_room(*line) && ft_check_room(*line))
		{
			prev = ft_add_node(*line, id++, prev);
			if (id == 1)
				(*config)->head = prev;
		}
		if (ft_strlen(*line) != 0)
		{
			free(*line);
			*line = NULL;
		}
	}
	return (1);
}
