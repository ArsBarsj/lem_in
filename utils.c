/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 02:19:46 by arseny            #+#    #+#             */
/*   Updated: 2019/02/21 19:54:57 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lemin.h"
#include "datatypes.h"

void	error(void)
{
	ft_printf("Error\n");
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

void	print_matrix(int **m, int size)
{
	int	i;
	int	j;
	int	first = 1;

	i = 0;
	if (m)
	{
		while (i < size)
		{
			j = 0;
			if (!first)
				printf("%d| ", i);		
			while (j < size)
			{
				if (first)
				{
					printf(" | ");
					while (j < size)
					{
						printf("%d ", j);
						j++;
					}
					printf("\n |--------------------\n");
					printf("%d| ", i);	
					j = 0;
					first = 0;
				}
				printf("%d ", m[i][j]);
				j++;
			}
			printf("\n");
			i++;
		}
	}
}
