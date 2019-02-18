/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arseny <arseny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 02:30:13 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/18 23:16:52 by arseny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_H
# define DATATYPES_H

typedef struct 		s_config
{
	int				ants;
	int				start_id;
	int				end_id;
	t_node			*head;
}					t_config;


typedef struct		s_node
{
	char			*name;
	int				id;
	int				distance;
	int				x;
	int				y;
	t_node			*next;
}					t_node;


typedef struct		s_graph
{
	int				verts_n;
	int				**matrix;
	t_node			**nodes;
}					t_graph;

typedef struct		s_queue
{
	int				node_id;
	struct s_queue	*next;
}					t_queue;

void				init_arr(int *arr, int size);

t_graph				*graph_new(int verts_n);
void				graph_del(t_graph **g);
t_queue				*queue_new(int id);
void				queue_push(t_queue **head, t_queue *elem);
int					queue_pop(t_queue **head);
void				queue_del(t_queue **head);
t_node				*node_new(int id, char *name, int x, int y);
t_node				*ft_add_node(char *line, int id, t_node *prev);
void				node_del(t_node **n);

int		bfs(int start_id, int end_id, t_graph *graph);
#endif