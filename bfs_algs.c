/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_algs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 23:42:47 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/15 15:26:28 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "datatypes.h"

void		paths_print(t_path **paths)
{
	int		i;
	int		j;
	t_node	*current;
	t_node	*next;

	i = 0;
	while (paths[i])
	{
		j = 0;
		current = paths[i]->path[j];
		ft_printf("\033[0;31m%d:\033[0m (%s|%d)", i, current->name, current->id);
		while (current && paths[i]->path[j + 1])
		{
			current = paths[i]->path[j];
			next = paths[i]->path[j + 1];
			ft_printf("->(%s|%d)", next->name, next->id);
			j++;
		}
		ft_printf(" \033[0;32m[%d] ants= %d\033[0m", j, paths[i]->ants_n);
		ft_printf("\n");
		i++;
	}
}

int		get_lines_n(t_path **paths, int ants)
{
	int	curr_lines;
	int	prev_lines;
	int	used_paths;

	if (!paths[0])
		return (2147483647);
	get_lines_init_counters(&prev_lines, &curr_lines, &used_paths);
	get_lines_reset_paths(paths);
	while (paths[used_paths - 1] && prev_lines > curr_lines)
	{
		prev_lines = curr_lines;
		get_lines_inner(paths, ants, used_paths);
		curr_lines = get_lines_max(paths, used_paths);
		if (curr_lines > prev_lines)
			break ;
		used_paths++;
	}
	if (prev_lines < curr_lines)
	{
		get_lines_reset_paths(paths);
		get_lines_inner(paths, ants, used_paths - 1);
		return (get_lines_max(paths, used_paths - 1));
	}
	return (curr_lines - 1);
}

t_path	**solve_inner2(t_graph *g, t_config *cfg, t_path **best, int min_l)
{
	t_path	**tmp;
	t_path	**alt;
	int		nm[3];

	init_search(g, best, cfg, nm);
	while (nm[0] <= nm[2])
	{
		tmp = find_new_path(g, best, cfg, nm);
		if (count_paths(tmp) > 1)
		{
			alt = paths_sort(path_join(best, tmp, nm[0]));
			if (min_l > get_lines_n(alt, g->ants_n))
			{
				nm[1] = reset_best(&best, nm, &tmp, alt);
				min_l = get_lines_n(best, g->ants_n);
				update_state(g, best, cfg, nm[0]);
			}
			else
				free_alt_restore(alt, tmp, g);
		}
		else
			free_tmp_restore(tmp, g);
		go_next(g, best, cfg, nm);
	}
	return (best);
}

void	ants_select_ways(t_graph *g, t_path **p)
{
	int	ant_i;
	int	path_i;
	int	tmp;

	ant_i = 0;
	path_i = 0;
	while (p[path_i])
	{
		tmp = 0;
		while (tmp < p[path_i]->ants_n && g->ants[ant_i])
		{
			g->ants[ant_i]->path_id = path_i;
			tmp++;
			ant_i++;
		}
		path_i++;
	}
}

void	solve_move(t_graph *g, t_config *c, t_path **paths)
{
	int			total_ants;
	int			i;
	static int	paths_n = 0;

	total_ants = g->ants_n;
	if (!paths_n)
		paths_n = count_paths(paths);
	while (g->ants_n)
	{
		paths_resote_links(paths, g);
		i = 0;
		while (i < total_ants)
		{
			if (g->ants[i])
				ant_move(&g->ants[i], g, paths[g->ants[i]->path_id], c->end_id);
			i++;
		}
		write(1, "\n", 1);
	}
}

int		solve(t_graph *g, t_config *cfg)
{
	t_path	**best;
	t_path	**alt;
	int		min_lines;

	best = bfs_ways2(cfg->start_id, cfg->end_id, g);
	if (!count_paths(best))
	{
		free(best);
		return (0);
	}
	min_lines = get_lines_n(best, g->ants_n);
	alt = solve_inner2(g, cfg, best, min_lines);
	ants_select_ways(g, alt);
	solve_move(g, cfg, alt);
	paths_del(&alt);
	return (1);
}
