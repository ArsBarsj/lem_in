/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_algs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 23:42:47 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/11 01:13:48 by artemiy          ###   ########.fr       */
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

void	print_matrix(int **m, int size)
{
	int	i;
	int	j;
	int	first = 1;

	i = 0;
	if (m)
	{
		while (i < size)
		{
			j = 0;
			if (!first)
				ft_printf("%d| ", i);		
			while (j < size)
			{
				if (first)
				{
					ft_printf(" | ");
					while (j < size)
					{
						ft_printf("%d ", j);
						j++;
					}
					ft_printf("\n |--------------------\n");
					ft_printf("%d| ", i);	
					j = 0;
					first = 0;
				}
				ft_printf("%d ", m[i][j]);
				j++;
			}
			ft_printf("\n");
			i++;
		}
	}
}

void        paths_print(t_path **paths)
{
	int     i;
	int     j;
	t_node  *current;
	t_node  *next;

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

t_path	**get_paths2(t_graph *g, int start, int end)
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
	// graph_restore_copy(g);
	return (paths);
}

void        path_restore_links(t_path *path, t_graph *g)
{
	int     i;
	int		j;
	t_node  *current;
	// t_node  *next;

	i = 0;
	current = path->path[i];
	// while (current && path->path[i + 1])
	while (current)
	{
		// next = path->path[i + 1];
		j = 0;
		while (j < g->verts_n)
		{
			if (g->matrix[current->id][j] && current->id != j)
				graph_link_add(g, current->id, j, 1);
			j++;
		}
		// if (g->matrix[current->id][next->id])
			// graph_link_add(g, current->id, next->id, 1);
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
			curr_lines = p[i]->len +  p[i]->ants_n - 1;
		}
		i++;
		curr_lines = p[i]->len +  p[i]->ants_n - 1;
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
	curr_lines = p[0]->len +  p[0]->ants_n - 1;
	while (p[i] && i < used - 1)
	{
		if (p[i]->len +  p[i]->ants_n - 1 > curr_lines)
			curr_lines = p[i]->len +  p[i]->ants_n - 1;
		i++;
	}
	return (curr_lines - 1);
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
			break;
		used_paths++;
	}
	if (prev_lines < curr_lines)
	{
		get_lines_reset_paths(paths);
		get_lines_inner(paths, ants, used_paths - 1);
		return (get_lines_max(paths, used_paths - 1));
	}
	return (curr_lines);
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

void	solve_inner2(t_graph *g, t_config *cfg)
{
	t_path	**shortest;
	t_path	**best;
	t_path	**tmp;
	int		min_lines;
	int		n;
	int		m;

	shortest = get_paths(g, cfg->start_id, cfg->end_id);
	best = shortest;
	min_lines = get_lines_n(shortest, g->ants_n);
	n = count_paths(best) - 1;
	m = best[n]->len - 1;
	path_close_all(g, best, cfg->start_id, cfg->end_id);
	path_restore_links(best[n], g);
	while (n >= 0 && m >= 0)
	{
		ft_printf("%d, %d\n", n, m);
		// path_close_all(g, best, cfg->start_id, cfg->end_id);
		// path_restore_links(best[n], g);
		while (m - 1 && graph_links_num(g, best[n]->path[m - 1]->id) < 3)
			m--;
		graph_link_del(&g, best[n]->path[m - 1]->id, best[n]->path[m]->id, 2);
		if (bfs_ways(cfg->start_id, cfg->end_id, g) > 1)
		{
			graph_restore_copy(g);
			tmp = get_paths(g, cfg->start_id, cfg->end_id);
			if (min_lines > get_lines_n(tmp, g->ants_n))
			{
				best == shortest ? 0 : paths_del(&best);
				best = get_paths(g, cfg->start_id, cfg->end_id);
				// n = count_paths(best) - 1;
				m = best[n]->len - 1;
				min_lines = get_lines_n(best, g->ants_n);
				path_close_all(g, best, cfg->start_id, cfg->end_id);
				path_restore_links(best[n], g);
			}
			else
				paths_del(&tmp);
			// paths_print(best);
		}
		if (m > 1)
		{
			graph_link_add(g, best[n]->path[m - 1]->id, best[n]->path[m]->id, 2);
			m--;
		}
		else if (n > 0)
		{
			graph_link_add(g, best[n]->path[m - 1]->id, best[n]->path[m]->id, 2);
			n--;
			path_close_all(g, best, cfg->start_id, cfg->end_id);
			path_restore_links(best[n], g);
			m = best[n]->len - 1;
		}
		else
			break;
	}
	ft_printf("\n%d\n", min_lines);
	paths_print(best);
	paths_del(&shortest);
	paths_del(&best);
}

int		solve(t_graph *g, t_config *cfg)
{
	t_path	**paths;
	int		paths_n;

	if (!(paths = get_paths(g, cfg->start_id, cfg->end_id)))
		return (0);
	if (!(paths_n = count_paths(paths)))
	{
		paths_del(&paths);
		return (0);
	}
	// ft_printf("%d\n", get_lines_n(paths, g->ants_n));
	// paths_print(paths);
	solve_inner2(g, cfg);
	// solve_inner(g, cfg, paths, paths_n);
	paths_del(&paths);
	return (1);
}
