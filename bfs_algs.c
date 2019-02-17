/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_algs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 23:42:47 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/18 02:22:47 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "datatypes.h"

int	find_paths_number(t_graph *g, int start, int end)
{
	t_dqueue	*path;
	int			counter;
	int			node_id;

	counter = 0;
	while ((path  = bfs_path(start, end, g)))
	{
		counter++;
		while (path)
		{
			node_id = dqueue_pop(&path);
			if (node_id != start && node_id != end)
				graph_close_node(g, node_id);
			else if (node_id == start && dqueue_peak(path) == end)
				graph_link_del(g, start, end, 1);
		}
	}
	graph_restore_copy(g);
	return (counter);
}

t_dqueue	**get_paths(t_graph *g, int start, int end)
{
	t_dqueue	**paths;
	int			paths_num;
	int			i;

	paths_num = find_paths_number(g, start, end);
	paths = (t_dqueue **)malloc(sizeof(t_dqueue *) * paths_num + 1);
	if (!paths)
		return (NULL);
	i = 0;
	while (i < paths_num)
	{
		paths[i] = bfs_path(start, end, g);
		graph_close_path(g, paths[i], start, end);
		i++;
	}
	paths[i] = NULL;
	i = 0;
	// while (paths[i])
	// {
		// while (paths[i])
			// ft_printf("%d->", dqueue_pop(&paths[i]));
		// i++;
		// ft_printf("\n");
	// }
	return (paths);
}
