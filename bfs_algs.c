/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_algs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 23:42:47 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/07 00:10:55 by artemiy          ###   ########.fr       */
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

int		count_children(t_graph *g, int room, t_config *cfg)
{
	int	i;
	int	children;

	i = 0;
	children = 0;
	while (i < g->verts_n)
	{
		if (g->matrix_copy[room][i] &&
		g->nodes[i]->distance == g->nodes[room]->distance + 1)
			children++;
		else if (g->matrix_copy[room][i] && cfg->end_id == i)
			children++;
		i++;
	}
	return (children);
}

int		find_child_with_min_children(t_graph *g ,int from, t_config *cfg)
{
	int	i;
	int best_i;
	int	min;

	i = 0;
	min = 100000000;
	best_i = -1;
	while (i < g->verts_n)
	{
		if (g->matrix_copy[from][i] && from != i &&
			g->nodes[i]->distance == g->nodes[from]->distance + 1)
		{
			// ft_printf("%d(%s)\n", i, g->nodes[i]->name);
			// ft_printf("%d(%s)\n", i, g->nodes[i]->name);
			if (count_children(g, i, cfg) <= min && count_children(g, i, cfg) > 0)
			{
				min = count_children(g, i, cfg);
				best_i = g->nodes[i]->id;
			}
		}
		else if (i == cfg->end_id && g->matrix_copy[from][i])
			return (cfg->end_id);
		i++;
	}
	return (best_i);
}

int		dfs(int start, t_config *cfg, t_graph *g, int min_c)
{
	int	delta;
	int	i;

	if (start == cfg->end_id || !min_c)
		return (min_c);
	i = -1;
	// ft_printf("EEEEEEEE start = %s (%d)\n",g->nodes[start]->name, start);
	// ft_printf("Best child = %d\n", find_child_with_min_children(g, start, cfg));
	//ft_printf("%d\n", g->nodes[3]->distance);
	while (++i < g->verts_n)
	{
		if (i != start && g->matrix_copy[start][i] &&
			g->nodes[i]->is_free &&
			g->nodes[i]->distance == g->nodes[start]->distance + 1 &&
			i == find_child_with_min_children(g, start, cfg))
		{
			delta = dfs(i, cfg, g, min_c > g->nodes[i]->is_free ? g->nodes[i]->is_free : min_c);
			if (delta)
			{
				g->nodes[start]->is_free = 0;
				// graph_link_del(&g, start, i, 1);
				if (start != cfg->start_id)
					graph_close_node(g, start);
				ft_printf("->(%d | %s)", start, g->nodes[start]->name);
				return (delta);
			}
		}
		else if (g->matrix_copy[start][i] && i == cfg->end_id)
		{
			delta = dfs(i, cfg, g, min_c > g->nodes[i]->is_free ? g->nodes[i]->is_free : min_c);
			if (delta)
			{
				g->nodes[start]->is_free = 0;
				// graph_link_del(&g, start, i, 1);
				if (start != cfg->start_id)
					graph_close_node(g, start);
				ft_printf("->(%d | %s)", start, g->nodes[start]->name);
				return (delta);
			}
		}
		// ft_printf("%d\n", i);
		// i++;
	}
	return (0);
}

int	find_max_flow(t_graph *g, t_config *cfg)
{
	int		max_flow;
	int		flow;

	max_flow = 0;
	flow  = 0;
	bfs(cfg->start_id, cfg->end_id, g);
	ft_printf("Best child %d\n", find_child_with_min_children(g, 9, cfg));
	// return (0);
	while (bfs(cfg->start_id, cfg->end_id, g))
	{
		flow = dfs(cfg->start_id, cfg, g, 1); // dfs
		while (flow != 0)
		{
			max_flow += flow;
			flow = dfs(cfg->start_id, cfg, g, 1); //dfs
		}
		ft_printf("TOTAL FLOW %d\n", max_flow);
	}
	// flow = dfs(cfg->start_id, cfg, g, 1000000);
	// max_flow  += flow;
	// ft_printf("\n");
	// flow = dfs(cfg->start_id, cfg, g, 1000000);
	// max_flow  += flow;
	// ft_printf("\n");
	// flow = dfs(cfg->start_id, cfg, g, 1000000);
	// max_flow  += flow;
	// ft_printf("\n");
	// flow = dfs(cfg->start_id, cfg, g, 1000000);
	// max_flow  += flow;
	// ft_printf("\n");
	// flow = dfs(cfg->start_id, cfg, g, 1000000);
	// max_flow  += flow;
	// ft_printf("\n");
	// flow = dfs(cfg->start_id, cfg, g, 1000000);
	// max_flow  += flow;
	// ft_printf("\n");
	// flow = dfs(cfg->start_id, cfg, g, 1000000);
	// max_flow  += flow;
	// ft_printf("\n");
	// flow = dfs(cfg->start_id, cfg, g, 1000000);
	// max_flow  += flow;
	// ft_printf("\n");
	// flow = dfs(cfg->start_id, cfg, g, 1000000);
	// max_flow  += flow;
	// ft_printf("\n");
	ft_printf("TOTAL FLOW %d\n", max_flow);
	return (0);
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
	// solve_inner2(g, cfg);
	// solve_inner(g, cfg, paths, paths_n);
	ft_printf("Max_flow = %d\n", find_max_flow(g, cfg));
	paths_del(&paths);
	return (1);
}
