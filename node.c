/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:51:53 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/20 22:15:21 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"
#include "lemin.h"

t_node		*node_new(int id, char *name, int x, int y)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	new_node->id = id;
	new_node->name = ft_strdup(name);
	new_node->distance = 2147483647;
	new_node->x = x;
	new_node->y = y;
	new_node->next = NULL;
	new_node->is_free = 1;
	return (new_node);
}

void		node_del(t_node **n)
{
	t_node	*next;
	if (n && *n)
	{
		while (*n)
		{
			if ((*n)->name)
				free((*n)->name);
			next = (*n)->next;
			free(*n);
			*n = next;
		}
	}
}

t_node		*ft_add_node(char *line, int id, t_node *prev)
{
	char	**opts;
	t_node	*room;

	opts = ft_strsplit(line, ' ');
	if (!opts)
		return (NULL);
	room = node_new(id, opts[0], ft_atoi(opts[1]), ft_atoi(opts[2]));
	if (!room)
	{
		ft_clean_str_arr(opts);
		return (NULL);
	}
	if (prev)
		prev->next = room;
	ft_clean_str_arr(opts);
	return (room);
}
