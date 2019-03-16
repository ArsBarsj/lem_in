/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 23:48:28 by fkuhn             #+#    #+#             */
/*   Updated: 2019/03/16 13:31:31 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"

void	bfs_setup(t_dqueue **q, int start, int *v, t_graph *g)
{
	if (q && g)
	{
		*q = dqueue_new(start);
		init_arr(v, g->verts_n, 0);
		v[start] = 1;
		g->nodes[start]->distance = 0;
	}
}

void	bfs_update_state(t_dqueue **q, int i, int *v, t_graph *g)
{
	if (q && g)
	{
		dqueue_push(q, dqueue_new(i));
		v[i] = 1;
	}
}

void	bfs_mod_update(int i, int curr, int *v, int *p)
{
	if (v && p)
	{
		v[i] = 1;
		p[i] = curr;
	}
}

void	path_restore_links(t_path *path, t_graph *g)
{
	int		i;
	int		j;
	t_node	*current;

	if (!path || !g || !path->path)
		return ;
	i = 0;
	current = path->path[i];
	graph_link_add(g, current->id, path->path[i + 1]->id, 1);
	while (current)
	{
		j = 0;
		while (j < g->verts_n && i != 0)
		{
			if (g->matrix[current->id][j] && current->id != j)
				graph_link_add(g, current->id, j, 1);
			j++;
		}
		i++;
		current = path->path[i];
	}
}

void	get_lines_reset_paths(t_path **p)
{
	int		i;

	i = 0;
	while (p[i])
	{
		p[i]->ants_n = 0;
		i++;
	}
}
