/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:57:29 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/15 12:03:40 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

t_node	*build_tree(t_list *list)
{
	t_node	*n1;
	t_node	*n2;
	t_node	*new;

	while (list->size > 1)
	{
		n1 = remove_node(list);
		n2 = remove_node(list);
		new = calloc(sizeof(t_node), 1);
		if (!new)
			return (NULL);
		new->c = 2;
		new->freq = (n1->freq + n2->freq);
		new->left = n1;
		new->right = n2;
		new->next = NULL;
		sorted_insert(list, new);
	}
	return (list->start);
}

int	tree_height(t_node *root)
{
	int	left;
	int	right;

	if (root == NULL)
		return (-1);
	else
	{
		left = tree_height(root->left) + 1;
		right = tree_height(root->right) + 1;
		if (left > right)
			return (left);
		else
			return (right);
	}
}

void	print_tree(t_node *root, int size)
{
	if (root->left == NULL && root->right == NULL)
		printf("\tFolha: %c\tAltura: %d\n", root->c, size);
	else
	{
		print_tree(root->left, size + 1);
		print_tree(root->right, size + 1);
	}
}

void	free_tree(t_node *tree)
{
	if (tree)
	{
		if (tree->left)
			free_tree(tree->left);
		if (tree->right)
			free_tree(tree->right);
		free(tree);
	}
}
