/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_alg_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 20:48:40 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/19 21:25:17 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"

int		reset_best(t_path ***best, int *nm, t_path ***tmp, t_path **alt)
{
	free(*tmp);
	*tmp = alt;
	path_del(&(*best)[nm[0]]);
	free(*best);
	*best = alt;
	nm[2] = count_paths(*best) - 1;
	return (1);
}

void	go_next(t_graph *g, t_path **b, t_config *cfg, int *nm)
{
	graph_link_add(g, b[nm[0]]->path[nm[1] - 1]->id,\
					b[nm[0]]->path[nm[1]]->id, 2);
	if (nm[1] < b[nm[0]]->len - 1)
	{
		nm[1]++;
		path_close_all(g, b, cfg->start_id, cfg->end_id);
		path_restore_links(b[nm[0]], g);
	}
	else
	{
		nm[0]++;
		path_close_all(g, b, cfg->start_id, cfg->end_id);
		path_restore_links(b[nm[0]], g);
		if (b[nm[0]])
			nm[1] = 1;
		else
			nm[1] = 0;
	}
}

void	skip_nodes(t_graph *g, t_path **b, int *nm)
{
	while (graph_links_num(g, b[nm[0]]->path[nm[1] - 1]->id) < 3 && nm[1] - 1)
		nm[1]--;
	graph_link_del(&g, b[nm[0]]->path[nm[1] - 1]->id,\
				b[nm[0]]->path[nm[1]]->id, 2);
}

t_path	**find_new_path(t_graph *g, t_path **b, t_config *cfg, int *nm)
{
	while (graph_links_num(g, b[nm[0]]->path[nm[1] - 1]->id) < 3 &&
			nm[1] + 1 < b[nm[0]]->len)
		nm[1]++;
	graph_link_del(&g, b[nm[0]]->path[nm[1] - 1]->id,\
					b[nm[0]]->path[nm[1]]->id, 2);
	return (bfs_ways2(cfg->start_id, cfg->end_id, g));
}

void	init_search(t_graph *g, t_path **b, t_config *cfg, int *nm)
{
	nm[2] = count_paths(b) - 1;
	nm[0] = -1;
	nm[1] = update_state2(g, b, cfg, &(nm[0]));
	nm[1] = 1;
}
