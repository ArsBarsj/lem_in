/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreutel <ttreutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 19:35:38 by fkuhn             #+#    #+#             */
/*   Updated: 2019/03/02 23:51:55 by ttreutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int		ft_new_line(char **s, char **line, int ret, int fd)
{
	char	*tmp;
	int		len;

	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
		len++;
	if ((*s)[len] == '\n')
	{
		*line = ft_strsub((*s), 0, len);
		tmp = ft_strdup((*s) + len + 1);
		free((*s));
		(*s) = tmp;
		if ((*s)[0] == '\0')
			ft_strdel(s);
	}
	else if ((*s)[len] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup((*s));
		ft_strdel(s);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*str;
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	int			ret;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!str)
			str = ft_strnew(1);
		tmp = ft_strjoin(str, buf);
		free(str);
		str = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (!str || str[0] == '\0'))
		return (0);
	return (ft_new_line(&str, line, ret, fd));
}
