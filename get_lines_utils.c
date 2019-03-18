/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 20:37:52 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/14 20:38:49 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"

void	get_lines_init_paths(t_path **p, int *ants, int n)
{
	int	i;

	i = 0;
	while (p[i] && *ants && i < n)
	{
		p[i]->ants_n = 1;
		(*ants)--;
		i++;
	}
}

void	get_lines_divide_ants(t_path **p, int *ants, int n)
{
	int	i;

	i = 0;
	while (*ants)
	{
		p[i]->ants_n++;
		(*ants)--;
		i = i + 1 < n ? i + 1 : 0;
	}
}

void	get_lines_inner(t_path **p, int ants, int n)
{
	int	i;
	int	prev_lines;
	int	curr_lines;

	get_lines_init_paths(p, &ants, n);
	prev_lines = p[n - 1]->len;
	i = 0;
	curr_lines = p[i]->len;
	while (ants && curr_lines != prev_lines && i < n)
	{
		while (curr_lines != prev_lines && ants && i < n)
		{
			p[i]->ants_n++;
			ants--;
			curr_lines = p[i]->len + p[i]->ants_n - 1;
		}
		i++;
		curr_lines = p[i]->len + p[i]->ants_n - 1;
	}
	get_lines_divide_ants(p, &ants, n);
}

void	get_lines_init_counters(int *total, int *curr, int *used)
{
	*total = 2147483647;
	*curr = 2147483646;
	*used = 1;
}

int		get_lines_max(t_path **p, int used)
{
	int	i;
	int	curr_lines;

	i = 0;
	curr_lines = p[0]->len + p[0]->ants_n - 1;
	while (p[i] && i < used - 1)
	{
		if (p[i]->len + p[i]->ants_n - 1 > curr_lines)
			curr_lines = p[i]->len + p[i]->ants_n - 1;
		i++;
	}
	return (curr_lines);
}
