/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreutel <ttreutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 23:17:40 by ttreutel          #+#    #+#             */
/*   Updated: 2019/03/02 23:24:26 by ttreutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "datatypes.h"

int		ft_check(char **line)
{
	if ((ft_is_comm(*line) || ft_is_cmd(*line) || ft_is_room(*line)
		|| ft_strlen(*line) == 0))
		return (1);
	return (0);
}

int		is_error(char **line, t_config **config, int id, int flag[2])
{
	if ((ft_is_start(*line) &&
		!ft_manage_cmd(config, ft_is_start(*line), id, flag)) ||
		(ft_is_room(*line) && !ft_check_room(*line)) || ft_strlen(*line) == 0)
	{
		free(*line);
		return (1);
	}
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
	size_t len;

	len = ft_strlen(line);
	if (len >= 2)
	{
		if (line[0] == '#' && line[1] == '#')
			return (1);
		return (0);
	}
	return (0);
}
