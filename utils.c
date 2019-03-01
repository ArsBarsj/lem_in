/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 02:19:46 by arseny            #+#    #+#             */
/*   Updated: 2019/02/25 09:00:35 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "datatypes.h"

void	error(void)
{
	ft_printf("ERROR\n");
	exit(0);
}

void	ft_clean_str_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int		ft_all_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void		config_del(t_config *config)
{
	if (config->head)
		node_list_del(&config->head);
	if (config->links)
		del_tab(config->links, config->rooms_n);
	free(config);
}
