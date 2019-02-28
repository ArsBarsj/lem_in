/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 20:57:43 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/28 17:49:04 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "datatypes.h"

int	ant_move(t_ant **a, t_graph *g, t_path *path, int end)
{
	int	to;

	if ((*a) && g && g->nodes[path->path[(*a)->step + 1]->id]->is_free &&
		g->matrix_copy[(*a)->node->id][path->path[(*a)->step + 1]->id])
	{
		to = g->nodes[path->path[(*a)->step + 1]->id]->id;
		graph_link_del(g, (*a)->node->id, to, 1);
		(*a)->node->is_free = 1;
		(*a)->node = g->nodes[to];
		(*a)->step++;
		ft_printf("L%d-%s ", (*a)->id, (*a)->node->name);
		if (to != end)
			(*a)->node->is_free = 0;
		else
		{
			g->ants_n -= 1;
			free((*a));
			(*a) = NULL;
		}
		return (1);
	}
	return (0);
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
			return (NULL);
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
