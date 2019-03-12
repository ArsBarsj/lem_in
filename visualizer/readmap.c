#include <unistd.h>
#include "visu.h"

void	read_file(t_visu *visu, int fd)
{
	// visu->tabfile = 2;///
	ft_config(fd, &visu->config);
	visu->fileline = read_all_file(fd, visu->fileline, 1024);
}

char	*read_all_file(int fd, char *buf, int buf_siz)
{
	int		ret;
	char	*links;
	int		space;
	int		used;

	links = ft_strnew(buf_siz);
	buf = ft_strnew(buf_siz);
	if (!links || !buf)
		return (NULL);
	space = buf_siz + 1;
	used = 0;
	while ((ret = read(fd, buf, buf_siz)) > 0)
	{
		buf[ret] = '\0';
		if (space - used > ret)
			ft_strcpy(links + used, buf);
		else
		{
			str_remalloc(&links, buf, space * 2, used);
			space *= 2;
		}
		used += ret;
	}
	free(buf);
	return (links);
}

int	ft_config(int fd, t_config **config)
{
	char	*line;
	int		flag[2];
	t_tree  *root;

	flag[0] = -1;
	flag[1] = -1;
	line = NULL;
	if (!ft_read_ants(&line, config, fd))
		return (0);
	else if (!ft_read_rooms(&line, config, fd, flag) || !(*config)->head)
		return (0);
	root = tree_create(config);
	if (!ft_read_links(&line, fd, config, root))
	{
		tree_del(root);
	 	return (0);
	}
	tree_del(root);
	return (1);
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