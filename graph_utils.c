/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:38:20 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/25 14:39:57 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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