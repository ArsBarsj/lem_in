/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:08:24 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/15 23:23:38 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"

int		bfs(int start_id, int end_id, t_graph *graph)
{
	/* start_id и end_id - номера комнаты старта и конца */
	int		i;
	int		visited[graph->verts_n];
	int		current;
	t_queue	*q;

	q = queue_new(start_id);
	init_arr(visited, graph->verts_n);
	visited[start_id] = 1;
	graph->nodes[start_id]->distance = 0;
	while (q)
	{
		current = queue_pop(&q);
		i = 0;
		while (i < graph->verts_n)
		{
			if (graph->matrix[current][i] && !visited[i])
			{
				queue_push(&q, queue_new(i));
				visited[i] = 1;
				graph->nodes[i]->distance = graph->nodes[current]->distance + 1;
			}
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
