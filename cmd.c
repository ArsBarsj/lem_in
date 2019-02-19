/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:18:58 by arseny            #+#    #+#             */
/*   Updated: 2019/02/19 23:37:42 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "lemin.h"

int		ft_is_start(char *line)
{
	// static int flag[2];

	if (ft_strequ(line, "##start"))
		return (1);
	else if (ft_strequ(line, "##end"))
		return (2);
	return (0);
}

int		ft_manage_cmd(t_config **config, int flag, int id, int flags[2])
{
	if (flag == 1 && flags[0] >= 0)
		return (0);
	else if (flag == 2 &&  flags[1] >= 0)
		return (0);
	else if (flag == 1)
	{
		(*config)->start_id = id;
		flags[0] = 1;
		return (1);
	}
	else if (flag == 2)
	{
		(*config)->end_id = id;
		flags[1] = 1;
		return(1);
	}
	return (0);
}

int		ft_is_link(char *line)
{
	char **set;
	int len;

	set = ft_strsplit(line, '-');
	if (!set)
		return (0);
	len = 0;
	while (set[len])
		len++;
	if (len != 2)
		return (0);
	return (1);
}
