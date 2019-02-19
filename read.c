/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 16:36:57 by arseny            #+#    #+#             */
/*   Updated: 2019/02/20 00:04:15 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "datatypes.h"
#include <stdio.h>
#include "lemin.h"
int		ft_read_links(char **line, t_config **config, int fd);

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
	else if (!ft_read_links(&line, config, fd))
		return (0);
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

int		ft_list_len(t_node *head)
{
	int		len;

	len = 0;
	if (head)
	{
		while (head)
		{
			len++;
			head = head->next;
		}
	}
	return (len);
}

int		**ft_create_links(t_config **config)
{
	int		i;
	int		j;
	int		rooms_len;
	int		**links;

	rooms_len = ft_list_len((*config)->head);
	if (!(links = (int **)malloc(sizeof(int *) * rooms_len)))
		return (NULL); // Free everything
	i = 0;
	while (i < rooms_len)
	{
		links[i] = (int *)malloc(sizeof(int) * rooms_len);
		if (!links[i])
		{
			return (NULL);// Free everything
		}
		j = 0;
		while (j < rooms_len)
			links[i][j++] = 0; // Use here init_arr from master branch.
		i++;
	}
	return (links);
}

int		ft_get_id_by_name(char *name, t_node *head)
{
	int	id;

	id = -1;
	if (head && name)
	{
		while (head)
		{
			id++;
			if (ft_strequ(head->name, name))
				return (id);
			head = head->next;
		}
	}
	return (id);
}

int		ft_str_arr_len(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

int		ft_read_links(char **line, t_config **config, int fd)
{
	char	**splited;
	int		from;
	int		to;

	if (!((*config)->links = ft_create_links(config)))
		return (0);
	splited = ft_strsplit(*line, '-');
	from = ft_get_id_by_name(splited[0], (*config)->head);
	to  = ft_get_id_by_name(splited[1], (*config)->head);
	(*config)->links[from][to] = 1;
	(*config)->links[to][from] = 1;
	free(*line);
	while (get_next_line(fd, line) > 0)
	{
		printf("%s\n", *line);
		if (!(splited = ft_strsplit(*line, '-')) || ft_str_arr_len(splited) > 2)
		{
			return (0); // Free everything
		}
		from = ft_get_id_by_name(splited[0], (*config)->head);
		to  = ft_get_id_by_name(splited[1], (*config)->head);
		(*config)->links[from][to] = 1;
		(*config)->links[to][from] = 1;
		free(*line);
		ft_clean_str_arr(splited);
	}
	return (1);
}

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

	print_matrix(config->links, ft_list_len(config->head));
	node_del(&config->head);
	free(config);
	return (0);
}