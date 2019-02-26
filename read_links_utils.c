/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:12:27 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/26 23:45:30 by artemiy          ###   ########.fr       */
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
