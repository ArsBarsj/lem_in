/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 02:30:13 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/19 03:20:07 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_H
# define DATATYPES_H

typedef struct		s_node
{
	char			*name;
	int				id;
	int				distance;
	int				is_free;
}					t_node;

typedef struct		s_ant
{
	int				id;
	int				path_id;
	int				step;
	t_node			*node;
}					t_ant;

typedef struct		s_graph
{
	int				ants_n;
	t_ant			**ants;
	int				verts_n;
	int				**matrix;
	int				**matrix_copy;
	t_node			**nodes;
}					t_graph;

typedef struct		s_dqueue
{
	int				node_id;
	struct s_dqueue	*next;
}					t_dqueue;

typedef struct		s_path
{
	t_node			**path;
	int				len;
}					t_path;


void				init_arr(int *arr, int size, int value);
void		ants_del(t_ant ***ants);

t_graph				*graph_new(int verts_n, int ants_n);
void				graph_del(t_graph **g);
void				graph_link_add(t_graph *g, int from, int to, int copy);
void				graph_link_del(t_graph *g, int from, int to, int copy);
void				graph_close_node(t_graph *g , int node);
void				graph_close_path(t_graph *g, t_path *path, int start, int end);
void				graph_restore_copy(t_graph *g);

t_dqueue			*dqueue_new(int id);
void				dqueue_push(t_dqueue **head, t_dqueue *elem);
void				dqueue_push_front(t_dqueue **head, t_dqueue *elem);
int					dqueue_pop(t_dqueue **head);
int					dqueue_peak(t_dqueue *head);
void				dqueue_del(t_dqueue **head);

t_node				*node_new(int id, char *name);
void				node_del(t_node **n);

int					bfs(int start_id, int end_id, t_graph *graph);
t_node				**bfs_path(int start, int end, t_graph *g);

t_path				*path_new(t_node **path);
void				path_del(t_path **p);

int	find_paths_number(t_graph *g, int start, int end);
t_path	**get_paths(t_graph *g, int start, int end);
int		solve(t_graph *g, int start, int end);

int	ant_move(t_ant **a, t_graph *g, t_path *p, int end);
#endif