/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:01:44 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/13 01:06:54 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"

int		path_len(t_node **path)
{
	int	len;

	if (path)
	{
		len = 0;
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
		p->len = path_len(path);
		p->ants_n = 0;
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

int		path_cmp(t_path *p1, t_path *p2)
{
	int	i;

	i = 0;
	while (p1->path[i] && p2->path[i])
	{
		if (p1->path[i]->id != p2->path[i]->id)
			i++;
		else
			return (0);
	}
	return (1);
}

t_path	**path_join(t_path **dst, t_path **src, int n)
{
	t_path	**path;
	int		dlen;
	int		slen;
	int		i;

	dlen = count_paths(dst) - 1;
	slen = count_paths(src);
	if (!(path = (t_path **)malloc(sizeof(t_path *) * (dlen + slen + 1))))
		return (NULL);
	path[dlen + slen] = NULL;
	i = 0;
	while (i < n)
	{
		path[i] = dst[i];
		i++;
	}
	i = 0;
	while (i < dlen - n)
	{
		path[n + i] = dst[n + i + 1];
		i++;
	}
	i = 0;
	while (i < slen)
	{
		path[i + dlen] = src[i];
		i++;
	}
	// free(dst);
	// free(src);
	return (path);
}

void	paths_sort(t_path **p)
{
	int	i;
	int	j;
	int	siz;
	t_path	*tmp;

	siz = count_paths(p);
	i = 0;
	while (i < siz)
	{
		j = i;
		while (j < siz)
		{
			if (p[i]->len > p[j]->len)
			{
				tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
