/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 16:36:57 by arseny            #+#    #+#             */
/*   Updated: 2019/02/25 08:58:48 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "datatypes.h"
#include <stdio.h>
#include <unistd.h>
#include "lemin.h"

int		ft_read_links(char **line, int fd, t_config **config, t_tree *root);

int         ft_read_map(int fd, t_config **config)
{
	char	*line;
	int     flag[2];
	int		links;
	t_tree	*root;

	flag[0] = -1;
	flag[1] = -1;
	line = NULL;
	if (!ft_read_ants(&line, config, fd))
		return (0);
	else if (!ft_read_rooms(&line, config, fd, flag))
	{
		if ((*config)->head)
			node_list_del(&(*config)->head);
		free(line);
		return (0);
	}
	root = tree_create(config);
	if (!(links = ft_read_links(&line, fd, config, root)))
	{
		//tree_del(root);
		//config_del(config);
		return (0);
	}
	return (1);
}

int			ft_read_ants(char **line, t_config **config, int fd)
{
	while (get_next_line(fd, line) > 0 && (ft_is_comm(*line) || ft_is_cmd(*line)))
	{
		if (ft_is_start(*line))
		{
			free(*line);
			return (0);
		}
		free(*line);
	}
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
	while (get_next_line(fd, line) > 0 &&
			(ft_is_comm(*line) || ft_is_cmd(*line) || ft_is_room(*line)
			|| ft_strlen(*line) == 0))
	{
		if ((ft_is_start(*line) && !ft_manage_cmd(config, ft_is_start(*line), id, flag)) ||
				(ft_is_room(*line) && !ft_check_room(*line)) || ft_strlen(*line) == 0)
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

int		**ft_create_links(t_config **config)
{
	int		i;
	int		j;
	int		**links;

	if (!(links = (int **)malloc(sizeof(int *) * (*config)->rooms_n)))
		return (NULL); // Free everything
	i = 0;
	while (i < (*config)->rooms_n)
	{
		links[i] = (int *)malloc(sizeof(int) * (*config)->rooms_n);
		if (!links[i])
		{
			return (NULL);// Free everything
		}
		j = 0;
		while (j < (*config)->rooms_n)
			links[i][j++] = 0; // Use here init_arr from master branch.
		i++;
	}
	return (links);
}

int		ft_set_link(char *line, t_config **config, t_tree *root)
{
	char	**splited;
	int		from;
	int		to;

	if (line && (ft_is_comm(line) || (ft_is_cmd(line) && !ft_is_start(line))))
		return (1);
	if (!ft_is_link(line) || !(splited = ft_strsplit(line, '-')))
		return (0);
	from = tree_get(root, splited[0])->room->id;
	to  = tree_get(root, splited[1])->room->id;
	if (from < 0 || to < 0)
	{
		free(line);
		ft_clean_str_arr(splited);
		return (0);
	}
	(*config)->links[from][to] = 1;
	(*config)->links[to][from] = 1;
	ft_clean_str_arr(splited);
	return (1);
}

int		str_remalloc(char **str, char *new_s, int size, int used)
{
	char *tmp;

	tmp = (char *)malloc(sizeof(char) * size * 2);
	if (!tmp)
		return (0);
	ft_strcpy(tmp, *str);
	free(*str);
	*str = tmp;
	ft_strcpy((*str) + used, new_s);
	return (1);
}

char	*read_links_file(int fd, char *buf, int buf_siz)
{
	int		ret;
	char	*links;
	int		space;
	int		used;

	links = (char *)malloc(sizeof(char) * buf_siz + 1);
	buf = (char *)malloc(sizeof(char) * buf_siz + 1);
	if (!links || !buf)
		return (NULL);
	space = buf_siz + 1;
	used = 0;
	while ((ret = read(fd, buf, buf_siz)) > 0)
	{
		buf[ret] = '\0';
		if (space - used > ret)
		{
			ft_strcpy(links + used, buf);
			used += ret;
		}
		else
		{
			str_remalloc(&links, buf, space * 2, used);
			space *= 2;
			used += ret;
		}
	}
	free(buf);
	return (links);
}

int		ft_read_links(char **line, int fd, t_config **config, t_tree *root)
{
	int		ret;
	int		buf_siz;
	char	**tab;
	int		i;

	buf_siz = 1024;
	if (!((*config)->links = ft_create_links(config)))
		return (0);
	if (!(ret = ft_set_link(*line, config, root)))
		return (0);
	free(*line);
	*line = read_links_file(fd, *line, buf_siz);
	if (!(*line))
		return (0);
	tab = ft_strsplit(*line, '\n');
	i = 0;
	while (tab[i])
	{
		if (!(ret = ft_set_link(tab[i], config, root)))
		{
			ft_clean_str_arr(tab);
			free(*line);
			return (0);
		}
		i++;
	}
	free(*line);
	ft_clean_str_arr(tab);
	return (1);
}

int 		main(int argc, char **argv)
{
	(void)argc;
	t_config *config;
	// t_node	*head;
	// t_node	*tmp;
	t_graph	*g;

	config = (t_config *)malloc(sizeof(t_config));
	config->head = NULL;
	config->end_id = -1;
	config->start_id = -1;
	int	fd = open(argv[1], O_RDONLY);
	int x = ft_read_map(fd, &config);

	if (config->start_id < 0 || config->end_id < 0 || config->start_id == config->end_id)
		error();
	if (config && x)
	{
		printf("Ants number: %d\nStart id = %d\nEnd id = %d\n", config->ants, config->start_id, config->end_id);
		// printf("Links matrix:\n");
		// print_matrix(config->links, config->rooms_n);
		// printf("Nodes(%d):\n", config->rooms_n);
		// head = config->head;
		// tmp = head;
		// while (head)
		// {
			// printf("%5s [%d]\n",head->name, head->id);
			// head = head->next;
		// }
		// head = tmp;
	}
	else
		error();
	g = graph_create(config);
	printf("%d - start_id        -> %d\n", config->start_id, config->end_id);
	solve(g, config->start_id, config->end_id);
	// node_list_del(&config->head);
	graph_del(&g);
	del_tab(config->links, config->rooms_n);
	free(config);
	return (0);
}