/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:08:24 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/16 02:58:06 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"

void	bfs_setup(t_queue **q, int start, int *visited, t_graph *g)
{
	if (q && g)
	{
		*q = queue_new(start);
		init_arr(visited, g->verts_n);
		visited[start] = 1;
		g->nodes[start]->distance = 0;
	}
}

void	bfs_update_state(t_queue **q, int i, int *visited, t_graph *g, int curr)
{
	if (q && g)
	{
		queue_push(q, queue_new(i));
		visited[i] = 1;
		g->nodes[i]->distance = g->nodes[curr]->distance + 1;
	}
}

int		bfs(int start_id, int end_id, t_graph *graph)
{
	/* start_id и end_id - номера комнаты старта и конца */
	int		i;
	int		visited[graph->verts_n];
	int		current;
	t_queue	*q;

	bfs_setup(&q, start_id, visited, graph);
	while (q)
	{
		current = queue_pop(&q);
		i = 0;
		while (i < graph->verts_n)
		{
			if (graph->matrix[current][i] && !visited[i])
				bfs_update_state(&q, i, visited, graph, current);
			i++;
		}
		if (current == end_id)
		{
			queue_del(&q);
			return (graph->nodes[end_id]->distance);
		}
	}
	return (2147483647);
}
