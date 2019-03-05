/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_algs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 23:42:47 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/05 03:13:51 by artemiy          ###   ########.fr       */
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
		ft_printf("%d: (%s|%d)", i, current->name, current->id);
		while (current && paths[i]->path[j + 1])
		{
			current = paths[i]->path[j];
			next = paths[i]->path[j + 1];
			ft_printf("->(%s|%d)", next->name, next->id);
			j++;
		}
		ft_printf(" [%d] ants= %d", j, paths[i]->ants_n);
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
	t_node  *current;
	t_node  *next;

	i = 0;
	current = path->path[i];
	while (current && path->path[i + 1])
	{
		next = path->path[i + 1];
		graph_link_add(g, current->id, next->id, 2);
		i++;
		current = path->path[i];
	}
}

int		get_lines_n(t_path **paths, int ants)
{
	int	i;
	int	curr_lines;
	int	prev_lines;

	i = 0;
	if (!paths[i])
		return (2147483647);
	while (paths[i] && ants)
	{
		paths[i]->ants_n = 1;
		ants--;
		i++;
	}
	prev_lines = paths[i - 1]->len;
	i = 0;
	curr_lines = paths[i]->len;
	while (ants && curr_lines != prev_lines)
	{
		while (curr_lines != prev_lines && ants)
		{
			paths[i]->ants_n++;
			ants--;
			curr_lines = paths[i]->len +  paths[i]->ants_n - 1;
		}
		i = paths[i + 1] ? i + 1 : 0;
		curr_lines = paths[i]->len +  paths[i]->ants_n - 1;
	}
	i = 0;
	while (ants)
	{
		paths[i]->ants_n++;
		ants--;
		i = paths[i + 1] ? i + 1 : 0;
	}
	int	total_lines = paths[0]->len +  paths[0]->ants_n - 1;;
	i = 0;
	while (paths[++i])
	{
		if (paths[i]->len +  paths[i]->ants_n - 1 > total_lines)
			total_lines = paths[i]->len +  paths[i]->ants_n - 1;
	}
	return (total_lines - 1);
}

void	solve_inner2(t_graph *g, t_config *cfg)
{
	t_path	**shortest;
	t_path	**best;
	t_path	**tmp;
	t_dqueue	*closed_links = dqueue_new(-1);
	t_path	**tmp2;
	t_node	**new_path;
	int		min_lines;
	int		n;
	int		m;
	int		i;
	int		from;
	int		to;
	// int		original_n;

	shortest = get_paths(g, cfg->start_id, cfg->end_id);
	best = shortest;
	min_lines = get_lines_n(shortest, g->ants_n);
	n = count_paths(best) - 1; // index of last path
	m = best[n]->len - 1; // index of last element in last path
	ft_printf("count_paths = %d\n", n);
	// print_matrix(g->matrix_copy, g->verts_n);
	// while (g->matrix_copy[cfg->start_id][shortest[0]->path[1]->id] && n >= 0)
	while (n >= 0 && m >= 0)
	{
		ft_printf("min_lines = %d\n", min_lines);
		ft_printf("n = %d\n", n);
		ft_printf("m = %d\n", m);
		paths_print(best);

		path_restore_links(best[n], g);
		// print_matrix(g->matrix_copy, g->verts_n);
		ft_printf("%s|%d -> ",best[n]->path[m - 1]->name, best[n]->path[m - 1]->id);
		ft_printf("%s|%d\n",best[n]->path[m]->name, best[n]->path[m]->id);
		graph_link_del(&g, best[n]->path[m - 1]->id, best[n]->path[m]->id, 2);
		dqueue_push_front(&closed_links, dqueue_new(best[n]->path[m]->id));
		dqueue_push_front(&closed_links, dqueue_new(best[n]->path[m - 1]->id));
		// tmp = best[n];
		tmp2 = best;
		tmp = get_paths2(g, cfg->start_id, cfg->end_id);
		ft_printf("tmp\n", m);
		paths_print(tmp);
		if (min_lines > get_lines_n(tmp, g->ants_n))
		{
			// ft_printf("TMP ADD TO PATH\n", m);
			best == shortest ? 0 : free(best);
			best = tmp;
			if (closed_links)
				graph_link_add(g, dqueue_pop(&closed_links), dqueue_pop(&closed_links), 2);
			// new_path = bfs_path(cfg->start_id, cfg->end_id, g);
			while ((new_path = bfs_path(cfg->start_id, cfg->end_id, g)))
			{
				if (n == count_paths(best) - 1)
				{
					// resize
					tmp2 = best;
					best = (t_path **)malloc(sizeof(t_path *) * (count_paths(best) + 2));
					i = 0;
					while (i < count_paths(tmp2))
					{
						best[i] = tmp2[i];
						i++;
					}
					best[i] = path_new(new_path);
					best[i + 1] = NULL;
				}
				n = i;
				m = best[i]->len - 1;
				ft_printf("%d\n", i);
			}
			n = count_paths(best) - 1;
			m = best[n]->len - 1;
			min_lines = get_lines_n(best, g->ants_n);
		}
		else if (m > 1)
		{
			if (closed_links)
				graph_link_add(g, dqueue_pop(&closed_links), dqueue_pop(&closed_links), 2);
			m--;
		}
		else if (n > 0)
		{
			ft_printf("lols");
			while (closed_links)
			{
				from = dqueue_pop(&closed_links);
				to = dqueue_pop(&closed_links);
				if (from >= 0 && to >= 0)
					graph_link_add(g, from, to, 2);
			}
			n--;
			m = best[n]->len - 1;
		}
		else
		{
			break;
		}
	}
	ft_printf("\n___________\n");
	ft_printf("%d\n", get_lines_n(best, g->ants_n));
	paths_print(best);
	paths_del(&shortest);
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
	solve_inner2(g, cfg);
	// solve_inner(g, cfg, paths, paths_n);
	paths_del(&paths);
	return (1);
}
