/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 01:33:36 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/25 11:33:17 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"
#include "libft/libft.h"

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

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size && !(m[i][j] = 0))
		{
			;
		}
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
	if (g && *g)
	{
		if ((*g)->matrix)
			del_tab((*g)->matrix, (*g)->verts_n);
		if ((*g)->matrix_copy)
			del_tab((*g)->matrix_copy, (*g)->verts_n);
		if ((*g)->ants)
			ants_del(&(*g)->ants);
		free((*g)->nodes);
		free((*g));
		*g = NULL;
	}
}

void		ants_del(t_ant ***ants)
{
	int	i;

	i  = 0;
	if (ants && *ants)
	{
		while (ants && (*ants)[i])
		{
			free((*ants)[i]);
			i++;
		}
		free(*ants);
		*ants = NULL;
	}
}

t_ant		**ant_new_list(int n)
{
	t_ant	**ants;
	int		i;

	ants = (t_ant **)malloc(sizeof(t_ant *) * (n + 1));
	if (!ants)
		return (NULL);
	i = 0;
	while (i < n)
	{
		ants[i] = (t_ant *)malloc(sizeof(t_ant));
		if (!ants[i])
		{
			ants_del(&ants);
			return (NULL); // need free or exit
		}
		ants[i]->id = i;
		ants[i]->step = 0;
		ants[i]->path_id = 0;
		ants[i]->node = NULL;
		i++;
	}
	ants[i] = NULL;
	return (ants);
}

t_graph		*graph_new(int verts_n, int ants_n)
{
	t_graph		*g;
	// int			i;

	// i = 0;
	g = (t_graph *)malloc(sizeof(t_graph));
	if (g == NULL)
		return (NULL);
	g->verts_n = verts_n;
	g->matrix = adjmatrix_new(verts_n);
	g->matrix_copy = adjmatrix_new(verts_n);
	g->nodes = (t_node **)malloc((verts_n + 1) * sizeof(t_node *));
	if (!g->nodes)
		graph_del(&g);
	// while (i < g->verts_n)
	// {
		// g->nodes[i] = node_new(i, NULL, 0, 0);
		// i++;
	// }
	g->nodes[verts_n] = NULL;
	g->ants_n = ants_n;
	g->ants = ant_new_list(ants_n); // Start instead 0
	if (g->matrix == NULL)
		return (NULL);
	return (g);
}

t_graph		*graph_create(t_config *cfg)
{
	t_graph	*g;
	t_node	*head;
	int		i;
	int		j;
	int     tmp;

	if (!(g = graph_new(cfg->rooms_n, cfg->ants)))
		return (NULL);
	head = cfg->head;
	while (head)
	{
		g->nodes[head->id] = head;
		head = head->next;
	}
	i = -1;
	tmp = g->verts_n;
	while (++i < tmp)
	{
		j = -1;
		while (++j < tmp)
		{
			g->matrix[i][j] = cfg->links[i][j];
			g->matrix_copy[i][j] = cfg->links[i][j];
		}
	}
	i = -1;
	head = g->nodes[cfg->start_id];
	while (++i < g->ants_n)
	{
		g->ants[i]->node = head;
	}
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
			else if (path->path[i]->id == start)
				graph_link_del(g, start, path->path[i + 1]->id, 1);
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
