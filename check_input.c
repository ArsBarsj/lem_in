/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arseny <arseny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 00:47:13 by arseny            #+#    #+#             */
/*   Updated: 2019/02/16 03:07:52 by arseny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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
	if (j != 3)
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
