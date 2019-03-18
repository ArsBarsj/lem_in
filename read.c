/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 16:36:57 by arseny            #+#    #+#             */
/*   Updated: 2019/03/18 20:51:08 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lemin.h"

int			ft_read_map(int fd, t_config **config)
{
	char	*line;
	int		flag[2];
	t_tree	*root;

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

int			main(void)
{
	t_config	*cfg;
	int			x;

	cfg = (t_config *)malloc(sizeof(t_config));
	ft_init_config(&cfg);
	x = ft_read_map(0, &cfg);
	ft_printf("\n");
	if (x && (cfg->start_id < 0 || cfg->end_id < 0))
	{
		config_del(cfg);
		error();
	}
	else if (start_end_error(cfg))
	{
		config_del(cfg);
		error();
	}
	start_dance(cfg);
	return (0);
}
