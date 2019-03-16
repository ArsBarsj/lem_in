/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 20:24:11 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/16 13:27:02 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"

void		path_join_copy(t_path **path, t_path **src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		path[i] = src[i];
		i++;
	}
}

t_path		**path_join(t_path **dst, t_path **src, int n)
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
	path_join_copy(path, dst, n);
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
	return (path);
}

t_path		**paths_sort(t_path **p)
{
	int		i;
	int		j;
	int		siz;
	t_path	*tmp;

	siz = count_paths(p);
	i = -1;
	while (++i < siz)
	{
		j = i - 1;
		while (++j < siz)
		{
			if (p[i]->len > p[j]->len)
			{
				tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
		}
	}
	return (p);
}
