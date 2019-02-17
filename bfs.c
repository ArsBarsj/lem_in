/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:08:24 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/17 23:33:16 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
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

void	bfs_update_state(t_dqueue **q, int i, int *v, t_graph *g, int curr)
{
	if (q && g)
	{
		dqueue_push(q, dqueue_new(i));
		v[i] = 1;
		g->nodes[i]->distance = g->nodes[curr]->distance + 1;
	}
}

void	bfs_mod_update(t_dqueue **q, int i, int curr, int *v, int *p)
{
	if (q && v && p)
	{
		v[i] = 1;
		p[i] = curr;
		dqueue_push(q, dqueue_new(i));
	}
}

int		bfs(int start_id, int end_id, t_graph *graph)
{
	int			i;
	int			visited[graph->verts_n];
	int			current;
	t_dqueue	*q;

	bfs_setup(&q, start_id, visited, graph);
	while (q)
	{
		current = dqueue_pop(&q);
		i = 0;
		while (i < graph->verts_n)
		{
			if (graph->matrix[current][i] && !visited[i])
				bfs_update_state(&q, i, visited, graph, current);
			i++;
		}
		if (current == end_id)
		{
			dqueue_del(&q);
			return (graph->nodes[end_id]->distance);
		}
	}
	return (2147483647);
}

int		bfs_modified(int start_id, int end_id, t_graph *g, int *pred)
{
	int			i;
	int			visited[g->verts_n];
	int			current;
	t_dqueue	*q;

	bfs_setup(&q, start_id, visited, g);
	while (q)
	{
		current = dqueue_pop(&q);
		i = 0;
		while (i < g->verts_n)
		{
			if (g->matrix[current][i] && !visited[i])
				bfs_mod_update(&q, i, current, visited, pred);
			i++;
		}
		if (current == end_id)
		{
			dqueue_del(&q);
			return (1);
		}
	}
	return (0);
}

int		*bfs_path(int start, int end, t_graph *g)
{
	int			pred[g->verts_n];
	int			dist[g->verts_n];
	t_dqueue	*path;
	int			crawl;

	init_arr(pred, g->verts_n, -1);
	init_arr(dist, g->verts_n, 2147483647);
	if (!bfs_modified(start, end, g, pred))
		exit(0);
	crawl = end;
	path = dqueue_new(crawl);
	while (pred[crawl] != -1)
	{
		dqueue_push_front(&path, dqueue_new(pred[crawl]));
		crawl = pred[crawl];
	}
	while (path)
	{
		printf("%d ", dqueue_pop(&path));
	}
	return (0);
}
