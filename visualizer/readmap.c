#include <unistd.h>
#include "visu.h"

int		**ft_create_link_v(t_config **config)
{
	int		i;
	int		j;
	int		**links;

	if (!(links = (int **)malloc(sizeof(int *) * (*config)->rooms_n)))
		return (NULL);
	i = 0;
	while (i < (*config)->rooms_n)
	{
		links[i] = (int *)malloc(sizeof(int) * (*config)->rooms_n);
		if (!links[i])
			return (NULL);
		j = 0;
		while (j < (*config)->rooms_n)
			links[i][j++] = 0;
		i++;
	}
	return (links);
}

int		ft_set_link_v(char *line, t_config **config, t_tree *root)
{
	char	**splited;
	t_tree	*from;
	t_tree	*to;

	if (line && (ft_is_comm(line) || (ft_is_cmd(line) && !ft_is_start(line))))
		return (1);
	if (ft_is_start(line))
		return (0);
	if (!ft_is_link(line) || !(splited = ft_strsplit(line, '-')))
		return (1);
	from = tree_get(root, splited[0]);
	to = tree_get(root, splited[1]);
	if (!from || !to)
	{
		ft_clean_str_arr(splited);
		return (0);
	}
	(*config)->links[from->room->id][to->room->id] = 1;
	(*config)->links[to->room->id][from->room->id] = 1;
	ft_clean_str_arr(splited);
	return (1);
}

void make_path(t_visu *visu, int i)
{
	while (visu->tabfile[i])
	{
		if (!ft_strcmp(visu->tabfile[i], "ERROR!"))
			free_visu(visu);
		i++;
	}
	ft_clean_str_arr(visu->tabfile);
	visu->graph =graph_create(visu->config);
	visu->best = bfs_ways2(visu->config->start_id, visu->config->end_id, visu->graph);
	visu->paths = solve_inner2(visu->graph, visu->config, visu->best, get_lines_n(visu->best, visu->config->ants));
}

int     read_file(t_visu *visu, int fd)
{
	int     i;
	t_tree  *root;
	char    *line;

	i = 0;
	if (!ft_config(fd, &visu->config, &line))
		return (0);
	visu->fileline = read_all_file(fd, visu->fileline, 1024);
	visu->tabfile = ft_strsplit(visu->fileline, '\n');
	root = tree_create(&visu->config);
	visu->config->links = ft_create_link_v(&visu->config);
	ft_set_link_v(line, &visu->config, root);
	free(line);
	while (visu->tabfile[i] && visu->tabfile[i][0] != 0
			&& ft_set_link_v(visu->tabfile[i], &visu->config, root))
		i++;
	tree_del(root);
	make_path(visu, i);
	return (1);
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

int	ft_config(int fd, t_config **config, char **line)
{
	int		flag[2];

	flag[0] = -1;
	flag[1] = -1;
	if (!ft_read_ants(line, config, fd))
		return (0);
	else if (!ft_read_rooms(line, config, fd, flag) || !(*config)->head)
		return (0);
	return (1);
}
