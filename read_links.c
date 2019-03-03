/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:35:51 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/03 15:39:00 by artemiy          ###   ########.fr       */
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
		return (NULL);
	i = 0;
	while (i < (*config)->rooms_n)
	{
		links[i] = (int *)malloc(sizeof(int) * (*config)->rooms_n);
		if (!links[i])
			return (NULL);
		j = 0;
		while (j < (*config)->rooms_n)
			links[i][j++] = 0;
		i++;
	}
	return (links);
}

int		ft_set_link(char *line, t_config **config, t_tree *root)
{
	char	**splited;
	t_tree	*from;
	t_tree	*to;

	if (line && (ft_is_comm(line) || (ft_is_cmd(line) && !ft_is_start(line))))
		return (1);
	if (ft_is_start(line))
		return (0);
	if (!ft_is_link(line) || !(splited = ft_strsplit(line, '-')))
		return (1);
	from = tree_get(root, splited[0]);
	to = tree_get(root, splited[1]);
	if (!from || !to)
	{
		ft_clean_str_arr(splited);
		return (0);
	}
	(*config)->links[from->room->id][to->room->id] = 1;
	(*config)->links[to->room->id][from->room->id] = 1;
	ft_clean_str_arr(splited);
	return (1);
}

char	*read_links_file(int fd, char *buf, int buf_siz)
{
	int		ret;
	char	*links;
	int		space;
	int		used;

	links = ft_strnew(buf_siz);
	buf = ft_strnew(buf_siz);
	if (!links || !buf)
		return (NULL);
	space = buf_siz + 1;
	used = 0;
	while ((ret = read(fd, buf, buf_siz)) > 0)
	{
		buf[ret] = '\0';
		if (space - used > ret)
			ft_strcpy(links + used, buf);
		else
		{
			str_remalloc(&links, buf, space * 2, used);
			space *= 2;
		}
		used += ret;
	}
	free(buf);
	return (links);
}

int		ft_links_proccess(char **tab, t_config **cfg, t_tree *root, char **line)
{
	int		i;
	int		ret;

	i = 0;
	while (tab[i])
	{
		write(1, tab[i], ft_strlen(tab[i]));
		write(1, "\n", 1);
		if (!(ret = ft_set_link(tab[i], cfg, root)))
		{
			links_cleanup(*line, tab);
			return (0);
		}
		i++;
	}
	return (1);
}

int		ft_read_links(char **line, int fd, t_config **cfg, t_tree *root)
{
	int		ret;
	char	**tab;

	if (*line)
		ft_printf("%s\n", *line);
	if (!*line || !((*cfg)->links = ft_create_links(cfg)))
		return (0);
	ret = ft_set_link(*line, cfg, root);
	free(*line);
	if (start_end_error((*cfg)))
		return (0);
	if (!ret || !(*line = read_links_file(fd, *line, 1024)))
		return (0);
	tab = ft_strsplit(*line, '\n');
	if (!check_empty_lines(tab, *line))
	{
		links_cleanup(*line, tab);
		return (1);
	}
	if (!ft_links_proccess(tab, cfg, root, line))
		return (0);
	links_cleanup(*line, tab);
	return (1);
}
