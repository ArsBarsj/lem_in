/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:08:24 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/19 18:39:35 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"

int			bfs(int start_id, int end_id, t_graph *graph)
{
	int			i;
	int			visited[graph->verts_n];
	int			current;
	t_dqueue	*q;

	bfs_setup(&q, start_id, visited, graph);
	while (q)
	{
		current = dqueue_pop(&q);
		i = -1;
		while (++i < graph->verts_n)
		{
			if (graph->matrix_copy[current][i] && !visited[i])
			{
				bfs_update_state(&q, i, visited, graph);
				graph->nodes[i]->distance = graph->nodes[current]->distance + 1;
			}
		}
		if (current == end_id)
		{
			dqueue_del(&q);
			return (graph->nodes[end_id]->distance);
		}
	}
	return (2147483647);
}

int			bfs_modified(int start_id, int end_id, t_graph *g, int *pred)
{
	int			i;
	int			visited[g->verts_n];
	int			current;
	t_dqueue	*q;

	bfs_setup(&q, start_id, visited, g);
	while (q)
	{
		current = dqueue_pop(&q);
		i = -1;
		while (++i < g->verts_n)
		{
			if (g->matrix_copy[current][i] && !visited[i])
			{
				bfs_mod_update(i, current, visited, pred);
				dqueue_push(&q, dqueue_new(i));
			}
		}
		if (current == end_id)
		{
			dqueue_del(&q);
			return (1);
		}
	}
	return (0);
}

t_node		**bfs_path(int start, int end, t_graph *g)
{
	int			pred[g->verts_n];
	int			dist[g->verts_n];
	t_node		**path;
	int			crawl;
	int			i;

	init_arr(pred, g->verts_n, -1);
	init_arr(dist, g->verts_n, 2147483647);
	if (!bfs_modified(start, end, g, pred))
		return (NULL);
	i = path_len_innr(pred, end);
	path = (t_node **)malloc(sizeof(t_node *) * (i + 1));
	if (!path)
		return (NULL);
	path[i] = NULL;
	crawl = end;
	i--;
	path[i--] = g->nodes[end];
	while (pred[crawl] != -1)
	{
		path[i] = g->nodes[pred[crawl]];
		crawl = pred[crawl];
		i--;
	}
	return (path);
}

t_path		**bfs_ways2(int start, int end, t_graph *g)
{
	int		count;
	t_path	**tmp;
	t_path	**tab;
	int		capacity;
	int		i;

	count = 0;
	tab = (t_path **)malloc(sizeof(t_path *) * 2);
	capacity = 1;
	while ((tab[count] = path_new(bfs_path(start, end, g))))
	{
		graph_close_path(g, tab[count++], start, end);
		if (capacity < count + 1)
		{
			i = -1;
			tmp = (t_path **)malloc(sizeof(t_path *) * (capacity * 2));
			while (++i < count)
				tmp[i] = tab[i];
			free(tab);
			tab = tmp;
			capacity *= 2;
		}
		tab[count] = NULL;
	}
	return (tab);
}
