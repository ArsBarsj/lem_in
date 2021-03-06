/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreutel <ttreutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 00:47:13 by arseny            #+#    #+#             */
/*   Updated: 2019/03/02 23:31:25 by ttreutel         ###   ########.fr       */
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
		return (0);
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
	return (1);
}

int		ft_str_arr_len(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

int		ft_is_link(char *line)
{
	char	**tab;

	if (!ft_strlen(line))
		return (0);
	if (!(tab = ft_strsplit(line, '-')))
		return (0);
	if (ft_str_arr_len(tab) != 2)
	{
		ft_clean_str_arr(tab);
		return (0);
	}
	ft_clean_str_arr(tab);
	return (1);
}
