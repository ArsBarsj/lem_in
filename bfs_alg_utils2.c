/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_alg_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 20:53:43 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/16 13:33:55 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"

int		update_state2(t_graph *g, t_path **ways, t_config *cfg, int *n)
{
	(*n)++;
	path_close_all(g, ways, cfg->start_id, cfg->end_id);
	path_restore_links(ways[(*n)], g);
	if (ways[(*n)])
		return (ways[(*n)]->len - 1);
	return (0);
}

void	update_state(t_graph *g, t_path **ways, t_config *cfg, int n)
{
	path_close_all(g, ways, cfg->start_id, cfg->end_id);
	path_restore_links(ways[(n)], g);
}

void	free_alt_restore(t_path **alt, t_path **tmp, t_graph *g)
{
	free(alt);
	paths_resote_links(tmp, g);
	paths_del(&tmp);
}

void	free_tmp_restore(t_path **tmp, t_graph *g)
{
	paths_resote_links(tmp, g);
	paths_del(&tmp);
}

void	path_close_all(t_graph *g, t_path **p, int start, int end)
{
	int		n;
	int		i;
	int		j;
	t_node	**path;

	n = count_paths(p);
	i = -1;
	while (++i < n)
	{
		j = -1;
		path = p[i]->path;
		while (path[++j])
		{
			if (path[j]->id != start && path[j]->id != end)
				graph_close_node(g, path[j]->id);
		}
	}
}
