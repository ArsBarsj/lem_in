/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:34:34 by artemiy           #+#    #+#             */
/*   Updated: 2019/02/25 03:54:20 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <datatypes.h>
#include <libft/libft.h>

t_tree	*tree_new(t_node *room, char key)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->key = key;
	tree->room = room;
	tree->peer = NULL;
	tree->children = NULL;
	return (tree);
}

void	tree_add(t_tree **r, t_node *room, char *name)
{
	t_tree	*prev;
	t_tree	*root;
	int		i;
	int		name_len;
	int		set_peer;

	i = 0;
	root = (*r);
	name_len = ft_strlen(name);
	// ft_printf("%s %d \n", name, room->id);
	set_peer = 1;
	while (i < name_len)
	{
		// ft_printf("%c",name[i]);
		while (root && root->key != name[i]) // find char in current level
		{
			prev = root;
			root = root->peer;
		}

		// if (root && !name[i + 1])
		// {
		// 	ft_printf("SET %d to tree\n", room->id);
		// 	root->room = room;
		// }
		if (!root && set_peer)
		{
			// ft_printf("PEER %c[%d] to tree\n",name[i], room->id);
			prev->peer = tree_new(NULL, name[i]);
			root = prev->peer;
			set_peer = 1;
		}
		else if (root && root->children && name[i + 1]) // go deeper in tree
		{
			// ft_printf("GO DEEPER [%d]\n", room->id);
			root = root->children;
			i++;
		}
		else if (root && !root->children && name[i + 1]) // create new level
		{
			// ft_printf("CREATE CHILDREN %c->%c[%d]\n",root->key, name[i+1], room->id);
			i++;
			root->children = tree_new(NULL, name[i]);
			root = root->children;
		}
		else if (root && !name[i + 1])
		{
			// ft_printf("SET [%d]\n", room->id);
			root->room = room;
			i++;
		}
		// else if (!root)
		// {
		// 	ft_printf("CHILDREN %c[%d] to tree\n",name[i], room->id);
		// 	prev->children = tree_new(room, name[i]);
		// 	root = prev->children;
		// 	prev = root;
		// }
	}
	// if (!name[i] && root)
	// {
		// root->room = room;
		// ft_printf("LEAF[%c] node %d to tree\n",root->key, root->room->id);
	// }
	// ft_printf("\n");
}

t_tree	*tree_get(t_tree *root, char *name)
{
	int		name_len;
	int		i;

	i = -1;
	name_len = ft_strlen(name);
	while (++i < name_len)
	{
		// ft_printf("%c",name[i]);
		while (root && root->key != name[i]) // find char in current level
		{
			root = root->peer;
		}
		if (!root) // no needed char in current level - search failed
			return (NULL);
		// else if (root && !name[i + 1]) // found needed name - return it
		// {
			// ft_printf("tree_get: %d\n", root->room == NULL);
			// return (root);
		// }
		else if (root && i + 1 == name_len)
		{
			// ft_printf("tree_get: %d\n", root->room == NULL);
			return (root);
		}
		else if (root && root->children) // go deeper in tree
		{
			// ft_printf("Go deeper [i]=%c\n", name[i]);
			root = root->children;
		}
		else if (root && !name[i + 1])
		{
			// ft_printf("tree_get: %d\n", root->room == NULL);
			return (root);
		}
	}
	if (!name[i] && root)
		return (root);
	ft_printf("NOT FOUND\n");
	return (NULL);
}
