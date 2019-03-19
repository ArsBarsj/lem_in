/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:46:08 by fkuhn             #+#    #+#             */
/*   Updated: 2019/03/19 18:47:30 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"

void		adj_matrix_init(int **m, int size)
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
