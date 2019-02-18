/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 20:57:43 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/19 00:30:21 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "datatypes.h"

int	ant_move(t_ant **a, t_graph *g, t_path *path, int end)
{
	int	to;

	// if (a->step + 1 >= path->len)
		// return (0);
	if ((*a) && g && g->nodes[path->path[(*a)->step + 1]->id]->is_free)
	{
		// ft_printf("KKKKKKKKKKKKKK\n");
		to = g->nodes[path->path[(*a)->step + 1]->id]->id;
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
