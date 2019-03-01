/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:01:44 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/01 13:12:37 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"

int		path_len(t_node **path)
{
	int	len;

	if (path)
	{
		len  = 0;
		while (path[len])
		{
			len++;
		}
		return (len);
	}
	return (-1);
}

t_path	*path_new(t_node **path)
{
	t_path	*p;

	if (path)
	{
		p = (t_path *)malloc(sizeof(t_path));
		if (!p)
			return (NULL);
		p->path = path;
		p->len = path_len(path) - 1;
		return (p);
	}
	return (NULL);
}

void	path_del(t_path **p)
{
	if (p && *p)
	{
		if ((*p)->path)
			free((*p)->path);
		free((*p));
		*p = NULL;
	}
}

void	paths_del(t_path ***p)
{
	int	i;

	i = 0;
	while (p && (*p)[i])
	{
		free((*p)[i]->path);
		free((*p)[i]);
		(*p)[i] = NULL;
		i++;
	}
	free(*p);
	*p = NULL;
}

int		count_paths(t_path **p)
{
	int	i;

	i = 0;
	if (p)
	{
		while (p[i])
			i++;
		return (i);
	}
	return (0);
}
