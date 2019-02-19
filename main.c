/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:19:16 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/19 03:29:17 by artemiy          ###   ########.fr       */
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
	t_graph	*graph;
	// int		distance;
	int		verts;
	int		i = 0;
	int		j = 0;
	int		start;
	int		end;

	if (argc > 1 && !strcmp(argv[1], "-i"))
	{
		printf("Введи кол-во комнат: ");
		scanf("%d", &verts);
		graph = graph_new(verts, 3);
		init_nodes(&graph);
		printf("Введи пары связей (-1 -1 для завершения):\n");
		scanf("%d %d", &i, &j);
		while (i >= 0 && j >= 0)
		{
			graph_link_add(graph, i, j, 2);
			scanf("%d %d", &i, &j);
		}
		printf("Введи номер старта: ");
		scanf("%d", &start);
		printf("Введи номер финиша: ");
		scanf("%d", &end);
	}
	else
	{
		graph = graph_new(10, 20);
		//init_nodes(&graph);
		graph_link_add(graph, 0, 1, 2);
		graph_link_add(graph, 1, 3, 2);
		graph_link_add(graph, 3, 5, 2);
		graph_link_add(graph, 5, 6, 2);
		graph_link_add(graph, 5, 9, 2);
		graph_link_add(graph, 7, 8, 2);
		graph_link_add(graph, 8, 9, 2);
		graph_link_add(graph, 0, 2, 2);
		graph_link_add(graph, 2, 4, 2);
		graph_link_add(graph, 4, 6, 2);
		graph_link_add(graph, 6, 7, 2);
		graph_link_add(graph, 7, 9, 2);
		while (i < 10)
		{
			graph->nodes[i]->name = ft_itoa(i);
			i++;
		}
		i = 0;
		while (i < 20)
		{
			graph->ants[i]->node = graph->nodes[0];
			i++;
		}
		start = 0;
		end = 9;
	}
	print_matrix(graph->matrix, graph->verts_n);


	// distance = bfs(start, end, graph);
	// printf("\nDistance  =  %d\n", distance);
	// bfs_path(start, end, graph);
	// printf("Total ways: %d\n", find_paths_number(graph, start, end));
	// get_paths(graph, start, end);
	solve(graph, start, end);
	// print_matrix(graph->matrix, graph->verts_n);
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
