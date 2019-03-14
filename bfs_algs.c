/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_algs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 23:42:47 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/14 13:44:26 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "datatypes.h"

int		find_paths_number(t_graph *g, int start, int end)
{
	t_node		**path;
	int			counter;
	int			node_id;
	int			i;

	counter = 0;
	while ((path = bfs_path(start, end, g)))
	{
		counter++;
		i = 0;
		while (path[i])
		{
			node_id = path[i]->id;
			if (node_id != start && node_id != end)
				graph_close_node(g, node_id);
			else if (node_id == start && path[i + 1] && path[i + 1]->id == end)
				graph_link_del(&g, start, end, 1);
			i++;
		}
		if (i == 1)
			return (counter);
		free(path);
	}
	graph_restore_copy(g);
	return (counter);
}

t_path	**get_paths(t_graph *g, int start, int end)
{
	t_path		**paths;
	int			paths_num;
	int			i;

	paths_num = find_paths_number(g, start, end);
	paths = (t_path **)malloc(sizeof(t_path *) * (paths_num + 1));
	if (!paths)
		return (NULL);
	i = 0;
	while (i < paths_num)
	{
		paths[i] = path_new(bfs_path(start, end, g));
		graph_close_path(g, paths[i], start, end);
		i++;
	}
	paths[i] = NULL;
	graph_restore_copy(g);
	return (paths);
}

void	select_path(t_graph *g, int end, t_path **paths, int ant_i)
{
	int			i;
	static int	paths_n = 0;

	i = 0;
	if (!paths_n)
		paths_n = count_paths(paths);
	while (i < paths_n && g->ants_n - (paths[i]->len - paths[0]->len) >= 2)
		i++;
	i = (i == 0 ? 0 : i - 1);
	while (i >= 0 && !ant_move(&g->ants[ant_i], g, paths[i], end))
		i--;
	if (g->ants[ant_i])
		g->ants[ant_i]->path_id = i;
}

void	solve_inner(t_graph *g, t_config *c, t_path **paths, int pn)
{
	int			total_ants;
	int			i;
	int			p_counter;
	static int	paths_n = 0;

	total_ants = g->ants_n;
	if (!paths_n)
		paths_n = count_paths(paths);
	while (g->ants_n)
	{
		i = 0;
		p_counter = 0;
		while (i < total_ants && pn)
		{
			if (g->ants[i] && g->ants[i]->node->id == c->start_id)
			{
				if (p_counter <= paths_n)
					select_path(g, c->end_id, paths, i);
				p_counter++;
			}
			else if (g->ants[i])
				ant_move(&g->ants[i], g, paths[g->ants[i]->path_id], c->end_id);
			i++;
		}
		paths_resote_links(paths, g);
		write(1, "\n", 1);
	}
}

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

void	path_restore_links(t_path *path, t_graph *g)
{
	int		i;
	int		j;
	t_node	*current;

	if (!path || !g || !path->path)
		return ;
	i = 0;
	current = path->path[i];
	graph_link_add(g, current->id, path->path[i + 1]->id, 1);
	while (current)
	{
		j = 0;
		while (j < g->verts_n && i != 0)
		{
			if (g->matrix[current->id][j] && current->id != j)
				graph_link_add(g, current->id, j, 1);
			j++;
		}
		i++;
		current = path->path[i];
	}
}

void	get_lines_init_paths(t_path **p, int *ants, int n)
{
	int	i;

	i = 0;
	while (p[i] && *ants && i < n)
	{
		p[i]->ants_n = 1;
		(*ants)--;
		i++;
	}
}

void	get_lines_divide_ants(t_path **p, int *ants, int n)
{
	int	i;

	i = 0;
	while (*ants)
	{
		p[i]->ants_n++;
		(*ants)--;
		i = i + 1 < n ? i + 1 : 0;
	}
}

void	get_lines_inner(t_path **p, int ants, int n)
{
	int	i;
	int	prev_lines;
	int	curr_lines;

	get_lines_init_paths(p, &ants, n);
	prev_lines = p[n - 1]->len;
	i = 0;
	curr_lines = p[i]->len;
	while (ants && curr_lines != prev_lines && i < n)
	{
		while (curr_lines != prev_lines && ants && i < n)
		{
			p[i]->ants_n++;
			ants--;
			curr_lines = p[i]->len + p[i]->ants_n - 1;
		}
		i++;
		curr_lines = p[i]->len + p[i]->ants_n - 1;
	}
	get_lines_divide_ants(p, &ants, n);
}

void	get_lines_init_counters(int *total, int *curr, int *used)
{
	*total = 2147483647;
	*curr = 2147483646;
	*used = 1;
}

int		get_lines_max(t_path **p, int used)
{
	int	i;
	int	curr_lines;

	i = 0;
	curr_lines = p[0]->len + p[0]->ants_n - 1;
	while (p[i] && i < used - 1)
	{
		if (p[i]->len + p[i]->ants_n - 1 > curr_lines)
			curr_lines = p[i]->len + p[i]->ants_n - 1;
		i++;
	}
	return (curr_lines);
}

void	get_lines_reset_paths(t_path **p)
{
	int		i;

	i = 0;
	while (p[i])
	{
		p[i]->ants_n = 0;
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

void	path_close_all(t_graph *g, t_path **p, int start, int end)
{
	int	n;
	int	i;

	n = count_paths(p);
	i = -1;
	while (++i < n)
		graph_close_path(g, p[i], start, end);
}

int	graph_del_dead_ends(t_graph *g)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (i < g->verts_n)
	{
		if (graph_links_num(g, i) == 1)
		{
			graph_close_node2(g, i);
			counter++;
			i = -1;
		}
		i++;
	}
	return (counter);
}

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

int		reset_best(t_path ***best, int n, t_path ***tmp, t_path **alt)
{
	free(*tmp);
	*tmp = alt;
	path_del(&(*best)[n]);
	free(*best);
	*best = alt;
	return ((*best)[n]->len - 1);
}

void	go_next(t_graph *g, t_path **b, t_config *cfg, int *nm)
{
	graph_link_add(g, b[nm[0]]->path[nm[1] - 1]->id, b[nm[0]]->path[nm[1]]->id, 2);
	if (nm[1] > 1)
		nm[1]--;
	else
		nm[1] = update_state2(g, b, cfg, &(nm[0]));
}

void	skip_nodes(t_graph *g, t_path **b, int *nm)
{
	while (graph_links_num(g, b[nm[0]]->path[nm[1] - 1]->id) < 3 && nm[1] - 1)
		nm[1]--;
	graph_link_del(&g, b[nm[0]]->path[nm[1] - 1]->id, b[nm[0]]->path[nm[1]]->id, 2);
}

t_path	**find_new_path(t_graph *g, t_path **b, t_config *cfg, int *nm)
{
	skip_nodes(g, b, nm);
	return (bfs_ways2(cfg->start_id, cfg->end_id, g));
}

void	init_search(t_graph *g, t_path **b, t_config *cfg, int *nm)
{
	nm[2] = count_paths(b) - 1;
	nm[0] = -1;
	nm[1] = update_state2(g, b, cfg, &(nm[0]));
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
				nm[1] = reset_best(&best, nm[0], &tmp, alt);
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
	ft_printf("%d\n", g->ants_n);
	while (p[path_i])
	{
		tmp = 0;
		while (tmp < p[path_i]->ants_n)
		{
			g->ants[ant_i]->path_id = path_i;
			tmp++;
			ant_i++;
		}
		path_i++;
	}
	ft_printf("%d\n", ant_i);
}

void	solve_move(t_graph *g, t_config *c, t_path **paths)
{
	int			total_ants;
	int			i;
	// int			p_counter;
	static int	paths_n = 0;

	total_ants = g->ants_n;
	if (!paths_n)
		paths_n = count_paths(paths);
	while (g->ants_n)
	{
		paths_resote_links(paths, g);
		i = 0;
		// p_counter = 0;
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

	best = get_paths(g, cfg->start_id, cfg->end_id);
	min_lines = get_lines_n(best, g->ants_n);
	alt = solve_inner2(g, cfg, best, min_lines);
	// paths_print(alt);
	// ft_printf("%d\n", get_lines_n(alt, g->ants_n));
	ants_select_ways(g, alt);
	solve_move(g, cfg, alt);
	paths_del(&alt);
	return (1);
}
