/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arseny <arseny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 00:47:13 by arseny            #+#    #+#             */
/*   Updated: 2019/02/18 18:32:49 by arseny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdlib.h>

int		ft_check_ant(char *count)
{
	long long	num;
	int			i;

	i = 0;
	while (count[i])
		if (!ft_isdigit(count[i++]))
			return (0);
	num = ft_atoi(count);
	if (num <= 0)
		return(0);
	return (1);
}

int		ft_check_room(char *room)
{
	char	**set;
	int		j;

	set = ft_strsplit(room, ' ');
	if (!set)
		return (0);
	j = 0;
	while (set[j])
		j++;
	if (j != 3 || (!set[0] || set[0][0] == 'L'))
	{
		ft_clean_str_arr(set);
		return (0);
	}
	j = 1;
	while (j <= 2)
	{
		if (!ft_all_digit(set[j++]))
		{
			ft_clean_str_arr(set);
			return (0);
		}
	}
	ft_clean_str_arr(set);
	return (0);
}

int		ft_is_room(char *line)
{
	char	**set;
	int		j;

	set = ft_strsplit(line, ' ');
	if (!set)
		return (0);
	j = 0;
	while (set[j])
		j++;
	if (j != 3 || set[0][0] == '#' || set[0][0] == 'L')
	{
		ft_clean_str_arr(set);
		return (0);
	}
	ft_clean_str_arr(set);
	return (1);
}

int		ft_is_comm(char *line)
{
	int len;

	len = ft_strlen(line);
	if (line && line[0] == '#')
	{
		if (len >= 2 && line[1] == '#')
			return (0);
		return (1);
	}
	return (0);
}

int		ft_is_cmd(char *line)
{
	int len;

	len = ft_strlen(line);
	if (len >= 2)
	{
		if (line[0] == '#' && line[1] == '#')
			return (1);
		return (0);
	}
	return (0);
}