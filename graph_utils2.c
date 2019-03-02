/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:50:06 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/02 23:23:06 by fkuhn            ###   ########.fr       */
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

void		graph_link_del(t_graph *g, int from, int to, int copy)
{
	if (g && (!copy || copy == 2))
	{
		g->matrix[from][to] = 0;
		g->matrix[to][from] = 0;
	}
	if (g && (copy == 1 || copy == 2))
	{
		g->matrix_copy[from][to] = 0;
		g->matrix_copy[to][from] = 0;
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
			graph_link_del(g, node, i, 1);
			i++;
		}
	}
}

int			dqueue_peak(t_dqueue *head)
{
	if (head)
	{
		return (head->node_id);
	}
	return (-1);
}
