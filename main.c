/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:19:16 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/19 23:59:16 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft/libft.h"
#include "datatypes.h"

void	print_matrix(int **m, int size);
void	init_nodes(t_graph **g);

int		main(int argc, char *argv[])
{
	(void)argc;
	t_graph	*graph;
	int		distance;
	int		verts;
	int		i = 0;
	int		j = 0;
	int		start;
	int		end;

	if (!strcmp(argv[1], "-i"))
	{
		printf("Введи кол-во комнат: ");
		scanf("%d", &verts);
		graph = graph_new(verts);
		init_nodes(&graph);
		while (i < verts)
		{
			j = 0;
			while (j < verts)
			{
				printf("Связь [%d][%d]: ", i, j);
				scanf("%d", &graph->matrix[i][j]);
				j++;
			}
			i++;
		}
		printf("Введи номер старта: ");
		scanf("%d", &start);
		printf("Введи номер финиша: ");
		scanf("%d", &end);
	}
	else
	{
		graph = graph_new(10);
		init_nodes(&graph);
		graph->matrix[0][1] = 1;
		graph->matrix[1][0] = 1;

		graph->matrix[0][2] = 1;
		graph->matrix[2][0] = 1;

		graph->matrix[1][2] = 1;
		graph->matrix[2][1] = 1;

		graph->matrix[2][3] = 1;
		graph->matrix[3][2] = 1;

		graph->matrix[1][4] = 1;
		graph->matrix[4][1] = 1;

		graph->matrix[3][4] = 1;
		graph->matrix[4][3] = 1;

		graph->matrix[3][5] = 1;
		graph->matrix[5][3] = 1;

		graph->matrix[5][6] = 1;
		graph->matrix[6][5] = 1;

		graph->matrix[4][6] = 1;
		graph->matrix[6][4] = 1;

		start = 0;
		end = 6;
	}
	print_matrix(graph->matrix, graph->verts_n);
	distance = bfs(start, end, graph);
	printf("\nDistance  =  %d\n", distance);
	graph_del(&graph);
	return (0);
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

void	init_nodes(t_graph **g)
{
	int	i;

	i = 0;
	while (i < (*g)->verts_n)
	{
		(*g)->nodes[i] = node_new(i, ft_itoa(i));
		i++;
	}
}
