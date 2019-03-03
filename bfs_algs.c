/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_algs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 23:42:47 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/03 18:04:39 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "datatypes.h"

int		find_paths_number(t_graph *g, int start, int end)
{
	t_node		**path;
	int			counter;
	int			node_id;
	int			i;

	counter = 0;
	while ((path = bfs_path(start, end, g)))
	{
		counter++;
		i = 0;
		while (path[i])
		{
			node_id = path[i]->id;
			if (node_id != start && node_id != end)
				graph_close_node(g, node_id);
			else if (node_id == start && path[i + 1] && path[i + 1]->id == end)
				graph_link_del(g, start, end, 1);
			i++;
		}
		if (i == 1)
			return (counter);
		free(path);
	}
	graph_restore_copy(g);
	return (counter);
}

t_path	**get_paths(t_graph *g, int start, int end)
{
	t_path		**paths;
	int			paths_num;
	int			i;

	paths_num = find_paths_number(g, start, end);
	paths = (t_path **)malloc(sizeof(t_path *) * (paths_num + 1));
	if (!paths)
		return (NULL);
	i = 0;
	while (i < paths_num)
	{
		paths[i] = path_new(bfs_path(start, end, g));
		graph_close_path(g, paths[i], start, end);
		i++;
	}
	paths[i] = NULL;
	graph_restore_copy(g);
	return (paths);
}

void	select_path(t_graph *g, int end, t_path **paths, int ant_i)
{
	int			i;
	static int	paths_n = 0;

	i = 0;
	if (!paths_n)
		paths_n = count_paths(paths);
	while (i < paths_n && g->ants_n - (paths[i]->len - paths[0]->len) >= 2)
		i++;
	i = (i == 0 ? 0 : i - 1);
	while (i >= 0 && !ant_move(&g->ants[ant_i], g, paths[i], end))
		i--;
	if (g->ants[ant_i])
		g->ants[ant_i]->path_id = i;
}

void	solve_inner(t_graph *g, t_config *c, t_path **paths, int pn)
{
	int			total_ants;
	int			i;
	int			p_counter;
	static int	paths_n = 0;

	total_ants = g->ants_n;
	if (!paths_n)
		paths_n = count_paths(paths);
	while (g->ants_n)
	{
		i = 0;
		p_counter = 0;
		while (i < total_ants && pn)
		{
			if (g->ants[i] && g->ants[i]->node->id == c->start_id)
			{
				if (p_counter <= paths_n)
					select_path(g, c->end_id, paths, i);
				p_counter++;
			}
			else if (g->ants[i])
				ant_move(&g->ants[i], g, paths[g->ants[i]->path_id], c->end_id);
			i++;
		}
		paths_resote_links(paths, g);
		write(1, "\n", 1);
	}
}

int		solve(t_graph *g, t_config *cfg)
{
	t_path	**paths;
	int		paths_n;

	if (!(paths = get_paths(g, cfg->start_id, cfg->end_id)))
		return (0);
	if (!(paths_n = count_paths(paths)))
	{
		paths_del(&paths);
		return (0);
	}
	solve_inner(g, cfg, paths, paths_n);
	paths_del(&paths);
	return (1);
}
