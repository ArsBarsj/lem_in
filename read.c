/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 16:36:57 by arseny            #+#    #+#             */
/*   Updated: 2019/02/28 19:45:28 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "datatypes.h"
#include <stdio.h>
#include <unistd.h>
#include "lemin.h"

void		config_del(t_config *config)
{
	if (config->head)
		node_list_del(&config->head);
	if (config->links)
		del_tab(config->links, config->rooms_n);
	free(config);
}

void        print_file(char **line, int fd)
{
	if ((*line = read_links_file(fd, *line, 1024)))
	{
		ft_printf("%s\n", *line);
		free(*line);
	}
}

int         ft_read_map(int fd, t_config **config)
{
	char	*line;
	int     flag[2];
	t_tree	*root;

	flag[0] = -1;
	flag[1] = -1;
	line = NULL;
	if (!ft_read_ants(&line, config, fd))
	{
		print_file(&line, fd);
		return (0);
	}
	else if (!ft_read_rooms(&line, config, fd, flag) || !(*config)->head)
	{
		print_file(&line, fd);
		return (0);
	}
	root = tree_create(config);
	ft_read_links(&line, fd, config, root);
	tree_del(root);
	return (1);
}

int			ft_read_ants(char **line, t_config **config, int fd)
{
	while (get_next_line(fd, line) > 0 && (ft_is_comm(*line) || ft_is_cmd(*line)))
	{
		ft_printf("%s\n", *line);
		if (ft_is_start(*line))
		{
			free(*line);
			return (0);
		}
		free(*line);
	}
	ft_printf("%s\n", *line);
	if (*line && ft_check_ant(*line))
	{
		(*config)->ants = ft_atoi(*line);
		free(*line);
		return (1);
	}
	free(*line);
	return (0);
}

int         ft_check(char **line)
{
	if ((ft_is_comm(*line) || ft_is_cmd(*line) || ft_is_room(*line)
	     || ft_strlen(*line) == 0))
		return (1);
	return (0);
}

int is_error(char **line, t_config **config, int id, int flag[2])
{
	if ((ft_is_start(*line) && !ft_manage_cmd(config, ft_is_start(*line), id, flag)) ||
	    (ft_is_room(*line) && !ft_check_room(*line)) || ft_strlen(*line) == 0)
	{
		free(*line);
		return (1);
	}
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

int 		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_config *config;
	t_graph	*g;

	config = (t_config *)malloc(sizeof(t_config));
	config->head = NULL;
	config->end_id = -1;
	config->start_id = -1;
	config->links = NULL;
	// int	fd = open(argv[1], O_RDONLY);
	int x = ft_read_map(0, &config);
	if (x && (config->start_id < 0 || config->end_id < 0 || config->start_id >= config->rooms_n))
	{
		config_del(config);
		error();
	}
	else if (!x || config->start_id == config->end_id)
	{
		config_del(config);
		error();
	}
	g = graph_create(config);
	if (!solve(g, config->start_id, config->end_id))
		ft_printf("ERROR\n");
	// print_map(g, g->matrix, g->verts_n);
	graph_del(&g);
	config_del(config);
	return (0);
}