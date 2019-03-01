/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:34:34 by artemiy           #+#    #+#             */
/*   Updated: 2019/03/01 13:17:33 by artemiy          ###   ########.fr       */
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

void	tree_add(t_tree *root, t_node *room, char *name)
{
	t_tree	*prev;
	int		i;
	int		name_len;
	int		set_peer;

	i = 0;
	name_len = ft_strlen(name);
	set_peer = 1;
	while (i < name_len)
	{
		while (root && root->key != name[i])
		{
			prev = root;
			root = root->peer;
		}
		if (!root && set_peer)
			tree_create_peer(&root, name[i], &prev, &set_peer);
		else if (root && root->children && name[i + 1])
			tree_go_deeper(&root, &i);
		else if (root && !root->children && name[i + 1])
			tree_create_child(&root, name[i], &i);
		else if (root && !name[i + 1])
			tree_set_room(&root, room, &i);
	}
}

t_tree	*tree_get(t_tree *root, char *name)
{
	int		name_len;
	int		i;

	i = -1;
	name_len = ft_strlen(name);
	while (++i < name_len)
	{
		while (root && root->key != name[i])
			root = root->peer;
		if (!root)
			return (NULL);
		else if (root && i + 1 == name_len)
			return (root);
		else if (root && root->children)
			root = root->children;
		else if (root && !name[i + 1])
			return (root);
	}
	if (!name[i] && root)
		return (root);
	return (NULL);
}

t_tree	*tree_create(t_config **config)
{
	t_tree	*root;
	t_node	*start;
	int		n;

	start = (*config)->head;
	n = 0;
	root = tree_new(NULL, '\0');
	while ((*config)->head)
	{
		n++;
		tree_add(root, (*config)->head, (*config)->head->name);
		(*config)->head = (*config)->head->next;
	}
	(*config)->rooms_n = n;
	(*config)->head = start;
	return (root);
}
