/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arseny <arseny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:18:58 by arseny            #+#    #+#             */
/*   Updated: 2019/03/07 23:47:53 by arseny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "lemin.h"

int		ft_is_start(char *line)
{
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
	else if (flag == 2 && flags[1] >= 0)
		return (0);
	else if (flag == 1)
	{
		(*config)->start_id = id;
		flags[0] = 1;
		if ((*config)->end_id == (*config)->start_id)
			return (0);
		return (1);
	}
	else if (flag == 2)
	{
		(*config)->end_id = id;
		flags[1] = 1;
		if ((*config)->end_id == (*config)->start_id)
			return (0);
		return (1);
	}
	return (0);
}

void	ft_init_config(t_config **config)
{
	(*config)->head = NULL;
	(*config)->end_id = -1;
	(*config)->start_id = -1;
	(*config)->links = NULL;
	(*config)->rooms_n = 0;
	(*config)->ants = -1;
}

void	start_dance(t_config *cfg)
{
	t_graph		*g;

	g = graph_create(cfg);
	if (!g)
	{
		config_del(cfg);
		error();
	}
	// if (g->matrix == NULL || !solve(g, cfg))
	// 	ft_printf("ERROR\n");
	graph_del(&g);
	config_del(cfg);
}
