/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 02:15:52 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/15 23:22:59 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"

t_queue		*queue_new(int id)
{
	t_queue	*q;

	q = (t_queue *)malloc(sizeof(t_queue));
	if (q == NULL)
		return (NULL);
	q->next = NULL;
	q->node_id = id;
	return (q);
}

void	queue_push(t_queue **head, t_queue *elem)
{
	t_queue	*tmp;

	if (head && (*head) && elem)
	{
		tmp = (*head);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
	else
		(*head) = elem;	
}

int		queue_pop(t_queue **head)
{
	int		ret;
	t_queue	*tmp;

	if (head)
	{
		ret = (*head)->node_id;
		tmp = (*head);
		(*head) = (*head)->next;
		free(tmp);
		return (ret);
	}
	return (-1);
}

void	queue_del(t_queue **head)
{
	t_queue	*tmp;

	if (head && (*head))
	{
		while ((*head))
		{
			tmp = (*head);
			*head = (*head)->next;
			free(tmp);
		}
	}
}