#ifndef LEMIN_H
# define LEMIN_H
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "datatypes.h"

int			ft_check_ant(char *count);
int			ft_check_room(char *room);
int			ft_is_room(char *line);
int			ft_is_comm(char *line);
int			ft_is_cmd(char *line);
int			ft_is_start(char *line);
int			ft_is_link(char *line);

int         ft_read_map(int fd, t_config **config);
int			ft_read_ants(char **line, t_config **config, int fd);
int			ft_read_rooms(char **line, t_config **config, int fd, int flag[2]);
int			ft_read_links(char **line, int fd, t_config **config, t_tree *root);
char	    *read_links_file(int fd, char *buf, int buf_siz);
int		    ft_manage_cmd(t_config **config, int flag, int id, int flags[2]);

void		links_cleanup(char *line, char **tab);
int			count_lines(char *str);
int			str_remalloc(char **str, char *new_s, int size, int used);
void		ft_clean_str_arr(char **arr);
int			ft_all_digit(char *str);


void		print_matrix(int **m, int size);
int			ft_str_arr_len(char **arr);
#endif