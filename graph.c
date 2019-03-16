/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 01:33:36 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/16 13:41:58 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"
#include "libft/libft.h"

t_graph		*graph_new(int verts_n, int ants_n)
{
	t_graph		*g;

	if (verts_n == 0)
		return (NULL);
	g = (t_graph *)malloc(sizeof(t_graph));
	if (g == NULL)
		return (NULL);
	g->verts_n = verts_n;
	g->matrix = adjmatrix_new(verts_n);
	g->matrix_copy = adjmatrix_new(verts_n);
	g->nodes = (t_node **)malloc((verts_n + 1) * sizeof(t_node *));
	if (!g->nodes)
		graph_del(&g);
	g->nodes[verts_n] = NULL;
	g->ants_n = ants_n;
	g->ants = ant_new_list(ants_n);
	return (g);
}

t_graph		*graph_create(t_config *cfg)
{
	t_graph	*g;
	t_node	*head;
	int		i;
	int		j;

	if (!(g = graph_new(cfg->rooms_n, cfg->ants)))
		return (NULL);
	head = cfg->head;
	while (head)
	{
		g->nodes[head->id] = head;
		head = head->next;
	}
	i = -1;
	while (++i < g->verts_n && cfg->links)
	{
		j = -1;
		while (++j < g->verts_n)
			if (cfg->links[i][j])
				graph_link_add(g, i, j, 2);
	}
	i = -1;
	while (++i < g->ants_n)
		g->ants[i]->node = g->nodes[cfg->start_id];
	return (g);
}

void		graph_close_path(t_graph *g, t_path *path, int start, int end)
{
	int			i;

	if (g && path)
	{
		i = 0;
		while (path->path[i])
		{
			if (path->path[i]->id != start && path->path[i]->id != end)
				graph_close_node(g, path->path[i]->id);
			i++;
		}
	}
}

void		graph_restore_copy(t_graph *g)
{
	int i;
	int	j;

	if (g)
	{
		i = -1;
		while (++i < g->verts_n)
		{
			j = -1;
			while (++j < g->verts_n)
			{
				g->matrix_copy[i][j] = g->matrix[i][j];
			}
		}
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
		if (g->matrix[node][j] && node != j)
			counter++;
		j++;
	}
	return (counter);
}
