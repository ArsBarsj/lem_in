/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:12:27 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/03 15:40:17 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	links_cleanup(char *line, char **tab)
{
	if (line)
		free(line);
	if (tab)
		ft_clean_str_arr(tab);
}

int		count_lines(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			count++;
		i++;
	}
	return (count);
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

int		check_empty_lines(char **tab, char *line)
{
	int	len;
	int	tab_len;
	int	lines;

	len = ft_strlen(line);
	lines = count_lines(line);
	tab_len = ft_str_arr_len(tab);
	if (tab_len < lines && line[len - 1] == '\n')
		return (0);
	if (tab_len < lines && line[len - 1] == '\n')
		return (0);
	return (1);
}

int		start_end_error(t_config *cfg)
{
	if (cfg)
	{
		if (cfg->start_id >= cfg->rooms_n || cfg->end_id >= cfg->rooms_n)
			return (1);
		if (cfg->start_id == cfg->end_id)
			return (1);
		if (cfg->start_id < 0 || cfg->end_id < 0)
			return (1);
	}
	return (0);
}
