/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 02:15:52 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/05 02:43:28 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"

t_dqueue	*dqueue_new(int id)
{
	t_dqueue	*q;

	q = (t_dqueue *)malloc(sizeof(t_dqueue));
	if (q == NULL)
		return (NULL);
	q->next = NULL;
	q->node_id = id;
	return (q);
}

void		dqueue_push_front(t_dqueue **head, t_dqueue *elem)
{
	if (head && (*head) && elem)
	{
		elem->next = *head;
		*head = elem;
	}
}

void		dqueue_push(t_dqueue **head, t_dqueue *elem)
{
	t_dqueue	*tmp;

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

int			dqueue_pop(t_dqueue **head)
{
	int			ret;
	t_dqueue	*tmp;

	if (head && (*head))
	{
		ret = (*head)->node_id;
		tmp = (*head);
		(*head) = (*head)->next;
		free(tmp);
		return (ret);
	}
	return (-1);
}

void		dqueue_del(t_dqueue **head)
{
	t_dqueue	*tmp;

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
