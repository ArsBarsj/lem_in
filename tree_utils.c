/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:34:34 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/01 13:15:16 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <datatypes.h>
#include <libft/libft.h>

void	tree_create_child(t_tree **root, char key, int *i)
{
	(*i)++;
	(*root)->children = tree_new(NULL, key);
	(*root) = (*root)->children;
}

void	tree_create_peer(t_tree **root, char key, t_tree **prev, int *set_peer)
{
	(*prev)->peer = tree_new(NULL, key);
	(*root) = (*prev)->peer;
	*set_peer = 1;
}

void	tree_go_deeper(t_tree **root, int *i)
{
	(*root) = (*root)->children;
	(*i)++;
}

void	tree_set_room(t_tree **root, t_node *room, int *i)
{
	(*root)->room = room;
	(*i)++;
}

void	tree_del(t_tree *root)
{
	if (root->children)
		tree_del(root->children);
	if (root->peer)
		tree_del(root->peer);
	free(root);
}
