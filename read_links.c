/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:35:51 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/25 13:09:08 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "datatypes.h"
#include "lemin.h"

int		**ft_create_links(t_config **config)
{
	int		i;
	int		j;
	int		**links;

	if (!(links = (int **)malloc(sizeof(int *) * (*config)->rooms_n)))
		return (NULL); // Free everything
	i = 0;
	while (i < (*config)->rooms_n)
	{
		links[i] = (int *)malloc(sizeof(int) * (*config)->rooms_n);
		if (!links[i])
		{
			return (NULL);// Free everything
		}
		j = 0;
		while (j < (*config)->rooms_n)
			links[i][j++] = 0; // Use here init_arr from master branch.
		i++;
	}
	return (links);
}

int		ft_set_link(char *line, t_config **config, t_tree *root)
{
	char	**splited;
	int		from;
	int		to;

	if (line && (ft_is_comm(line) || (ft_is_cmd(line) && !ft_is_start(line))))
		return (1);
	if (!ft_is_link(line) || !(splited = ft_strsplit(line, '-')))
		return (0);
	from = tree_get(root, splited[0])->room->id;
	to  = tree_get(root, splited[1])->room->id;
	if (from < 0 || to < 0)
	{
		free(line);
		ft_clean_str_arr(splited);
		return (0);
	}
	(*config)->links[from][to] = 1;
	(*config)->links[to][from] = 1;
	ft_clean_str_arr(splited);
	return (1);
}

int		str_remalloc(char **str, char *new_s, int size, int used)
{
	char *tmp;

	tmp = (char *)malloc(sizeof(char) * size * 2);
	if (!tmp)
		return (0);
	ft_strcpy(tmp, *str);
	free(*str);
	*str = tmp;
	ft_strcpy((*str) + used, new_s);
	return (1);
}

char	*read_links_file(int fd, char *buf, int buf_siz)
{
	int		ret;
	char	*links;
	int		space;
	int		used;

	links = (char *)malloc(sizeof(char) * buf_siz + 1);
	buf = (char *)malloc(sizeof(char) * buf_siz + 1);
	if (!links || !buf)
		return (NULL);
	space = buf_siz + 1;
	used = 0;
	while ((ret = read(fd, buf, buf_siz)) > 0)
	{
		buf[ret] = '\0';
		if (space - used > ret)
		{
			ft_strcpy(links + used, buf);
			used += ret;
		}
		else
		{
			str_remalloc(&links, buf, space * 2, used);
			space *= 2;
			used += ret;
		}
	}
	free(buf);
	return (links);
}

int		ft_read_links(char **line, int fd, t_config **config, t_tree *root)
{
	int		ret;
	int		buf_siz;
	char	**tab;
	int		i;

	buf_siz = 1024;
	if (!((*config)->links = ft_create_links(config)))
		return (0);
	if (!(ret = ft_set_link(*line, config, root)))
		return (0);
	free(*line);
	*line = read_links_file(fd, *line, buf_siz);
	if (!(*line))
		return (0);
	tab = ft_strsplit(*line, '\n');
	i = 0;
	while (tab[i])
	{
		if (!(ret = ft_set_link(tab[i], config, root)))
		{
			ft_clean_str_arr(tab);
			free(*line);
			return (0);
		}
		i++;
	}
	free(*line);
	ft_clean_str_arr(tab);
	return (1);
}
