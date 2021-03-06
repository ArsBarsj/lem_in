/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreutel <ttreutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 02:30:13 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/19 19:51:13 by ttreutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_H
# define DATATYPES_H

typedef struct		s_node
{
	char			*name;
	int				id;
	int				distance;
	int				x;
	int				y;
	struct s_node	*next;
	int				is_free;
}					t_node;

typedef struct		s_config
{
	int				ants;
	int				start_id;
	int				end_id;
	t_node			*head;
	int				rooms_n;
	int				**links;
}					t_config;

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
	int				ants_n;
}					t_path;

typedef struct		s_tree
{
	t_node			*room;
	struct s_tree	*children;
	struct s_tree	*peer;
	char			key;
}					t_tree;

t_tree				*tree_new(t_node *room, char key);
t_tree				*tree_create(t_config **config);
void				tree_create_child(t_tree **root, char key, int *i);
void				tree_create_peer(t_tree **r, char k, t_tree **p, int *sp);
void				tree_go_deeper(t_tree **root, int *i);
void				tree_set_room(t_tree **root, t_node *room, int *i);
t_tree				*tree_get(t_tree *root, char *name);
void				tree_add(t_tree *root, t_node *room, char *name);
void				tree_del(t_tree *root);

void				error(void);
void				init_arr(int *arr, int size, int value);
void				del_tab(int **tab, int size);
void				ants_del(t_ant ***ants);
t_ant				**ant_new_list(int n);

void				get_lines_init_paths(t_path **p, int *ants, int n);
void				get_lines_divide_ants(t_path **p, int *ants, int n);
void				get_lines_inner(t_path **p, int ants, int n);
void				get_lines_init_counters(int *total, int *curr, int *used);
int					get_lines_max(t_path **p, int used);
void				get_lines_reset_paths(t_path **p);

t_graph				*graph_create(t_config *cfg);
t_graph				*graph_new(int verts_n, int ants_n);
void				graph_del(t_graph **g);
void				graph_link_add(t_graph *g, int from, int to, int copy);
void				graph_link_del(t_graph **g, int from, int to, int copy);
int					graph_links_num(t_graph *g, int node);
void				graph_close_node(t_graph *g, int node);
void				graph_close_node2(t_graph *g, int node);
void				graph_close_path(t_graph *g,\
										t_path *path, int start, int end);
void				paths_resote_links(t_path **paths, t_graph *g);
void				graph_restore_copy(t_graph *g);
int					**adjmatrix_new(int verts);
void				adj_matrix_init(int **m, int size);
t_node				*ft_add_node(char *line, int id, t_node *prev);

t_dqueue			*dqueue_new(int id);
void				dqueue_push(t_dqueue **head, t_dqueue *elem);
void				dqueue_push_front(t_dqueue **head, t_dqueue *elem);
int					dqueue_pop(t_dqueue **head);
int					dqueue_peak(t_dqueue *head);
void				dqueue_del(t_dqueue **head);

t_node				*node_new(int id, char *name, int x, int y);
void				node_list_del(t_node **n);
void				node_del(t_node **n);

int					bfs(int start_id, int end_id, t_graph *graph);
t_node				**bfs_path(int start, int end, t_graph *g);
void				bfs_setup(t_dqueue **q, int start, int *v, t_graph *g);
void				bfs_update_state(t_dqueue **q, int i, int *v, t_graph *g);
void				bfs_mod_update(int i, int curr, int *v, int *p);
t_path				**bfs_ways2(int start, int end, t_graph *g);

t_path				*path_new(t_node **path);
void				path_del(t_path **p);
void				paths_del(t_path ***p);
int					count_paths(t_path **p);
int					path_len_innr(int *pred, int n);
t_path				**path_join(t_path **dst, t_path **src, int n);
void				paths_print(t_path **paths);
void				path_restore_links(t_path *path, t_graph *g);
int					get_lines_n(t_path **paths, int ants);
t_path				**paths_sort(t_path **p);
void				path_close_all(t_graph *g, t_path **p, int start, int end);
void				path_restore_links(t_path *path, t_graph *g);

int					solve(t_graph *g, t_config *cfg);
int					ant_move(t_ant **a, t_graph *g, t_path *p, int end);
int					reset_best(t_path ***best, int *nm, t_path ***tmp,
								t_path **alt);
void				go_next(t_graph *g, t_path **b, t_config *cfg, int *nm);
void				skip_nodes(t_graph *g, t_path **b, int *nm);
t_path				**solve_inner2(t_graph *g, t_config *cfg, t_path **best,
									int min_l);
t_path				**find_new_path(t_graph *g, t_path **b, t_config *cfg,
									int *nm);
void				init_search(t_graph *g, t_path **b, t_config *cfg, int *nm);
int					update_state2(t_graph *g, t_path **ways, t_config *cfg,
									int *n);
void				update_state(t_graph *g, t_path **ways, t_config *cfg,
									int n);
void				free_alt_restore(t_path **alt, t_path **tmp, t_graph *g);
void				free_tmp_restore(t_path **tmp, t_graph *g);
void				adj_matrix_init(int **m, int size);
int					graph_links_num(t_graph *g, int node);

void				print_matrix(int **m, int size);
#endif
