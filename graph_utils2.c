/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:50:06 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/10 15:03:46 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"

void		graph_link_add(t_graph *g, int from, int to, int copy)
{
	if (g && (!copy || copy == 2))
	{
		g->matrix[from][to] = 1;
		g->matrix[to][from] = 1;
	}
	if (g && (copy == 1 || copy == 2))
	{
		g->matrix_copy[from][to] = 1;
		g->matrix_copy[to][from] = 1;
	}
}

void		graph_link_del(t_graph **g, int from, int to, int copy)
{
	if (g && (*g) && (!copy || copy == 2))
	{
		(*g)->matrix[from][to] = 0;
		(*g)->matrix[to][from] = 0;
	}
	if (g && (*g) && (copy == 1 || copy == 2))
	{
		(*g)->matrix_copy[from][to] = 0;
		(*g)->matrix_copy[to][from] = 0;
	}
}

void		graph_close_node(t_graph *g, int node)
{
	int	i;

	if (g)
	{
		i = 0;
		while (i < g->verts_n)
		{
			graph_link_del(&g, node, i, 1);
			i++;
		}
	}
}

void        paths_resote_links(t_path **paths, t_graph *g)
{
	int     i;
	int     j;
	t_node  *current;
	t_node  *next;

	i = 0;
	while (paths[i])
	{
		j = 0;
		current = paths[i]->path[j];
		while (current && paths[i]->path[j + 1])
		{
			current = paths[i]->path[j];
			next = paths[i]->path[j + 1];
			graph_link_add(g, current->id, next->id, 1);
			j++;
		}
		i++;
	}
}

int			graph_links_num(t_graph *g, int node)
{
	int	j;
	int	counter;

	j = 0;
	counter = 0;
	while (j < g->verts_n)
	{
		if (g->matrix_copy[node][j] && node != j)
			counter++;
		j++;
	}
	return (counter);
}
