/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:12:27 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/25 13:13:51 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	links_cleanup(char *line, char **tab)
{
	if (line)
		free(line);
	if (tab)
		ft_clean_str_arr(tab);
}
