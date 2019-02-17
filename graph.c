/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 01:33:36 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/18 02:21:44 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"

void	init_arr(int *arr, int size, int value)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (i < size)
		{
			arr[i] = value;
			i++;
		}
	}
}

void	del_tab(int **tab, int size)
{
	int	i;

	i = 0;
	if (tab && *tab)
	{
		while (i < size)
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

void	adj_matrix_init(int **m, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			m[i][j] = 0;
			j++;
		}
		i++;
	}
}

int		**adjmatrix_new(int verts)
{
	int	**adj;
	int	i;

	adj = (int **)malloc(verts * sizeof(int *));
	if (adj == NULL)
		return(NULL);
	i = 0;
	while (i < verts)
	{
		adj[i] = (int *)malloc(verts * sizeof(int));
		if (adj == NULL)
		{
			del_tab(adj, i);
			return (NULL);
		}
		i++;
	}
	adj_matrix_init(adj, verts);
	return (adj);
}

void		graph_del(t_graph **g)
{
	int		i;

	if (g && *g)
	{
		if ((*g)->matrix)
			del_tab((*g)->matrix, (*g)->verts_n);
		if ((*g)->matrix_copy)
			del_tab((*g)->matrix_copy, (*g)->verts_n);
		i = 0;
		while (i < (*g)->verts_n)
		{
			node_del(&((*g)->nodes[i]));
			i++;
		}
		free((*g)->nodes);
		free((*g));
		*g = NULL;
	}
}

t_graph		*graph_new(int verts_n)
{
	t_graph		*g;

	g = (t_graph *)malloc(sizeof(t_graph));
	if (g == NULL)
		return (NULL);
	g->verts_n = verts_n;
	g->matrix = adjmatrix_new(verts_n);
	g->matrix_copy = adjmatrix_new(verts_n);
	g->nodes = (t_node **)malloc((verts_n + 1) * sizeof(t_node *));
	if (g->matrix == NULL)
		return (NULL);
	return (g);
}

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

void		graph_close_node(t_graph *g , int node)
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

void		graph_close_path(t_graph *g, t_dqueue *path, int start, int end)
{
	t_dqueue	*ptr;

	if (g && path)
	{
		ptr = path;
		while (path)
		{
			if (path->node_id != start && path->node_id != end)
				graph_close_node(g, path->node_id);
			else if (path->node_id == start)
				graph_link_del(g, start, path->next->node_id, 1);
			path = path->next;
		}
		path = ptr;
	}
}

void		graph_restore_copy(t_graph *g)
{
	int i;
	int	j;

	if (g)
	{
		i = 0;
		while (i < g->verts_n)
		{
			j = 0;
			while (j < g->verts_n)
			{
				g->matrix_copy[i][j] = g->matrix[i][j];
				j++;
			}
			i++;
		}
	}
}
