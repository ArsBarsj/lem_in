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

t_config	*ft_read_map(int fd, t_config **config)
{
	char	*line;
	int		start;
	int		end;

	if (!ft_read_ants(&line, config, fd))
		return (NULL);
	else if (!ft_read_rooms(&line, config, fd))
		return (NULL); // add clear all mallocs
	return (*config);
}

int			ft_read_ants(char **line, t_config **config, int fd)
{
	get_next_line(fd, line);
	while (ft_is_comm(*line) || ft_is_cmd(*line))
	{
		if (ft_is_start(*line))
			return (0);
		get_next_line(fd, line);
	}
	if (!ft_check_ant(*line))
		return (0);
	(*config)->ants = ft_atoi(*line);
	return (1);
}

int			ft_read_rooms(char **line, t_config **config, int fd)
{
	int		id;
	t_node	*prev;

	id = 0;
	prev = NULL;
	get_next_line(fd, line);
	while (ft_is_comm(*line) || ft_is_cmd(*line) || ft_is_room(*line))
	{
		if (ft_is_start(line) && !ft_manage_cmd(line, config, ft_is_start(line), id))
			return (0);
		else if (ft_is_room(*line) && ft_check_room(*line))
		{
			prev = ft_add_node(line, id++, prev);
			if (id == 1)
				(*config)->head = prev;
		}
		else if (ft_is_room(*line) && !ft_check_room(*line))
		{
			node_del(&(*config)->head);
			return (0);
		}
		get_next_line(fd, line);
	}
	return (1);
}

#include <stdio.h>
int 		main(int argc, char **argv)
{
	(void)argc;
	t_config *config;
	config = (t_config *)malloc(sizeof(t_config));
	config->ants = 0;
	config->end_id = 88;
	config->start_id = 14;
	config->head = NULL;
	int	fd = open(argv[1], O_RDONLY);
	config = ft_read_map(fd, &config);
	if (config)
		printf("%d\n", config->ants);
	else 
		printf("ERROR\n");
	return (0);
}