/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arseny <arseny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 16:36:57 by arseny            #+#    #+#             */
/*   Updated: 2019/02/18 23:58:22 by arseny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "lemin.h"

int         ft_read_map(int fd, t_config **config)
{
	char	*line;
	int     flag[2];

	flag[0] = -1;
	flag[1] = -1;
	if (!ft_read_ants(&line, config, fd))
		return (0);
	else if (!ft_read_rooms(&line, config, fd, flag))
	{
		if ((*config)->head)
			node_del(&(*config)->head);
		free(line);
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
	if (ft_check_ant(*line))
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
			(ft_is_comm(*line) || ft_is_cmd(*line) || ft_is_room(*line)))
	{
		if ((ft_is_start(*line) && !ft_manage_cmd(config, ft_is_start(*line), id, flag)) ||
				(ft_is_room(*line) && !ft_check_room(*line)))
		{
			node_del(&(*config)->head);
			return (0);
		}
		else if (ft_is_room(*line) && ft_check_room(*line))
		{
			prev = ft_add_node(*line, id++, prev);
			if (id == 1)
				(*config)->head = prev;
		}
		free(*line);
	}
	if (ft_strlen(*line) == 0)
		return (0);
	return (1);
}

#include <stdio.h>
int 		main(int argc, char **argv)
{
	(void)argc;
	t_config *config;

	config = (t_config *)malloc(sizeof(t_config));
	config->ants = 0;
	config->end_id = 0;
	config->start_id = 0;
	config->head = NULL;

	int	fd = open(argv[1], O_RDONLY);
	int x = ft_read_map(fd, &config);

	if (config)
		printf("%d\nreturn of read_map = %d\n", config->ants, x);
	else 
		printf("ERROR\n");

	node_del(&config->head);
	free(config);
	return (0);
}