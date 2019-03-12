/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:08:24 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/13 00:09:43 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"

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

#include "libft/libft.h"

int		bfs_modified2(int start_id, int end_id, t_graph *g, int *pred)
{
	int			i;
	int			visited[g->verts_n];
	int			head;
	int			back;
	int			*q;

	// bfs_setup(&q, start_id, visited, g);
	q = (int *)malloc(sizeof(int) * g->verts_n);
	init_arr(q, g->verts_n, -1);
	head = 0;
	back = 0;
	q[head] = start_id;
	init_arr(visited, g->verts_n, 0);
	visited[start_id] = 1;
	g->nodes[start_id]->distance = 0;
	while (q[head] >= 0)
	{
		// ft_printf("%d\n", q[head]);
		// current = dqueue_pop(&q);
		i = -1;
		while (++i < g->verts_n)
		{
			if (g->matrix_copy[q[head]][i] && !visited[i])
			{
				bfs_mod_update(i, q[head], visited, pred);
				q[++back] = i;
				// dqueue_push(&q, dqueue_new(i));
			}
		}
		if (q[head] == end_id)
		{
			free(q);
			// dqueue_del(&q);
			return (1);
		}
		head++;
	}
	free(q);
	return (0);
}

t_node	**bfs_path(int start, int end, t_graph *g)
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

void	deep_copy(int ***dst, int **src, int siz)
{
	int	i;
	int	j;

	*dst = (int **)malloc(sizeof(int *) * siz);
	i = -1;
	while (++i < siz)
	{
		(*dst)[i] = (int *)malloc(sizeof(int) * siz);
		j = -1;
		while (++j < siz)
			(*dst)[i][j] = src[i][j];
	}
}

void	weak_copy(int **dst, int **src, int siz)
{
	int	i;
	int	j;

	i = -1;
	while (++i < siz)
	{
		j = -1;
		while (++j < siz)
			dst[i][j] = src[i][j];
	}
}

int		bfs_ways(int start, int end, t_graph *g)
{
	// int		**m_copy;
	int		count;
	t_path	*p;

	// deep_copy(&m_copy, g->matrix_copy, g->verts_n);
	count = 0;
	while ((p = path_new(bfs_path(start, end, g))))
	{
		graph_close_path(g, p, start, end);
		count++;
		path_del(&p);
	}
	// weak_copy(g->matrix_copy, m_copy, g->verts_n);
	// del_tab(m_copy, g->verts_n);
	return (count);
}

t_path		**bfs_ways2(int start, int end, t_graph *g)
{
	// int		**m_copy;
	int		count;
	t_path	**tmp;
	t_path	**tab;
	int		capacity;
	int		i;

	// deep_copy(&m_copy, g->matrix_copy, g->verts_n);
	count = 0;
	tab = (t_path **)malloc(sizeof(t_path *));
	capacity = 1;
	// weak_copy(g->matrix_copy, m_copy, g->verts_n);
	while ((tab[count] = path_new(bfs_path(start, end, g))))
	{
		graph_close_path(g, tab[count], start, end);
		count++;
		if (capacity < count + 1)
		{
			i = 0;
			tmp = (t_path **)malloc(sizeof(t_path *) * (capacity + 1));
			while (i < count)
			{
				tmp[i] = tab[i];
				i++;
			}
			free(tab);
			tab = tmp;
			capacity++;
		}
		tab[count] = NULL;
	}
	// tab[count] = NULL;
	// paths_print(tab);
	// weak_copy(g->matrix_copy, m_copy, g->verts_n);
	// del_tab(m_copy, g->verts_n);
	return (tab);
}

