/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 01:33:36 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/16 01:52:18 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"

void	init_arr(int *arr, int size)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (i < size)
		{
			arr[i] = 0;
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
	g->nodes = (t_node **)malloc((verts_n + 1) * sizeof(t_node *));
	if (g->matrix == NULL)
		return (NULL);
	return (g);
}

void		graph_link_add(t_graph *g, int from, int to)
{
	if (g)
	{
		g->matrix[from][to] = 1;
		g->matrix[to][from] = 1;
	}
}

void		graph_link_del(t_graph *g, int from, int to)
{
	if (g)
	{
		g->matrix[from][to] = 0;
		g->matrix[to][from] = 0;
	}
}
