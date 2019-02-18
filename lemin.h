#ifndef LEMIN_H
# define LEMIN_H
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>

int			ft_check_ant(char *count);
int			ft_check_room(char *room);
int			ft_is_room(char *line);
int			ft_is_comm(char *line);
int			ft_is_cmd(char *line);
int			ft_is_start(char *line);

t_config	*ft_read_map(int fd, t_config **config);
int			ft_read_ants(char **line, t_config **config, int fd);
int			ft_read_rooms(char **line, t_config **config, int fd);

void		ft_clean_str_arr(char **arr);
int			ft_all_digit(char *str);
#endif