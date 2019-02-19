/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:51:53 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/19 03:20:37 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"

t_node		*node_new(int id, char *name)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	new_node->id = id;
	new_node->name = name;
	new_node->distance = 2147483647;
	new_node->is_free = 1;
	return (new_node);
}

void		node_del(t_node **n)
{
	if (n && (*n))
	{
		if ((*n)->name)
			free((*n)->name);
		free((*n));
		(*n) = NULL;
	}
}
