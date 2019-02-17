/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 02:30:13 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/17 23:22:28 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_H
# define DATATYPES_H

typedef struct		s_node
{
	char			*name;
	int				id;
	int				distance;
}					t_node;


typedef struct		s_graph
{
	int				verts_n;
	int				**matrix;
	t_node			**nodes;
}					t_graph;

typedef struct		s_dqueue
{
	int				node_id;
	struct s_dqueue	*next;
}					t_dqueue;

void				init_arr(int *arr, int size, int value);

t_graph				*graph_new(int verts_n);
void				graph_del(t_graph **g);
void				graph_link_add(t_graph *g, int from, int to);
void				graph_link_del(t_graph *g, int from, int to);

t_dqueue			*dqueue_new(int id);
void				dqueue_push(t_dqueue **head, t_dqueue *elem);
void				dqueue_push_front(t_dqueue **head, t_dqueue *elem);
int					dqueue_pop(t_dqueue **head);
void				dqueue_del(t_dqueue **head);

t_node				*node_new(int id, char *name);
void				node_del(t_node **n);

int		bfs(int start_id, int end_id, t_graph *graph);
int		*bfs_path(int start, int end, t_graph *g);
#endif