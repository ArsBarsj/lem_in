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

t_step  *create_step(char *step, t_visu *v)
{
	char    **tab;
	t_step  *newstep;
	t_node  *tmp;

	tab = ft_strsplit(step, '-');
	newstep = (t_step *)malloc(sizeof(t_step));
	newstep->ant = v->arr[ft_atoi(tab[0] + 1) - 1];
	tmp = v->config->head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, tab[1]))
		{
			newstep->room = tmp;
			break;
		}
		tmp = tmp->next;
	}
	newstep->next = NULL;
}

t_turn  *create_turn(void)
{
	t_turn  *turn;

	if (!(turn = (t_turn *)malloc(sizeof(t_turn))))
		return (NULL);
	turn->step = NULL;
	turn->next = NULL;
	return (turn);
}

t_step  *fill_steps(t_visu *v, char **tab)
{
	t_step  *head;
	t_step  *prev;
	int i;

	i = 1;
	head = create_step(tab[0], v);
	prev = head;
	while (tab[i])
	{
		prev->next = create_step(tab[i], v);
		prev = prev->next;
		i++;
	}
	return (head);
}

void    manage_turns(t_visu *v, char *line, t_turn **curr)
{
	char    **tab;
	t_turn  *turn;

	if (v->turns == NULL)
	{
		v->turns = create_turn();
		*curr = v->turns;
		turn = *curr;
	}
	else
	{
		(*curr)->next = create_turn();
		turn = (*curr)->next;
		*curr = turn;
	}

	tab = ft_strsplit(line, ' ');
	turn->step = fill_steps(v, tab);
	ft_clean_str_arr(tab);
}

int     read_file(t_visu *visu, int fd)
{
	int     i;
	t_tree  *root;
	t_turn  *tmp;

	i = 0;
	if (!ft_config(fd, &visu->config))
		return (0);
	visu->fileline = read_all_file(fd, visu->fileline, 1024);
	visu->tabfile = ft_strsplit(visu->fileline, '\n');
	root = tree_create(&visu->config);
	visu->config->links = ft_create_link_v(&visu->config);
	while (visu->tabfile[i] && visu->tabfile[i][0] != 0
			&& ft_set_link_v(visu->tabfile[i], &visu->config, root))
		i++;
	visu->arr = ant_new_list(visu->config->ants);
	tmp = NULL;
	while (visu->tabfile[i])
	{
		if (!ft_strcmp(visu->tabfile[i], "ERROR!"))
			return (0);
		manage_turns(visu, visu->tabfile[i], &tmp);
		i++;
	}
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

int	ft_config(int fd, t_config **config)
{
	char	*line;
	int		flag[2];

	flag[0] = -1;
	flag[1] = -1;
	line = NULL;
	if (!ft_read_ants(&line, config, fd))
		return (0);
	else if (!ft_read_rooms(&line, config, fd, flag) || !(*config)->head)
		return (0);
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