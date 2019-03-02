/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 23:48:28 by fkuhn             #+#    #+#             */
/*   Updated: 2019/03/02 23:48:49 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	bfs_update_state(t_dqueue **q, int i, int *v, t_graph *g)
{
	if (q && g)
	{
		dqueue_push(q, dqueue_new(i));
		v[i] = 1;
	}
}

void	bfs_mod_update(int i, int curr, int *v, int *p)
{
	if (v && p)
	{
		v[i] = 1;
		p[i] = curr;
	}
}
