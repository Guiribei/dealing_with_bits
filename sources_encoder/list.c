/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:43:54 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/13 17:09:49 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "labs.h"

t_list	*create_list(void)
{
	t_list	*list;
	
	list = (t_list *)calloc(1, sizeof(t_list));
	list->start = NULL;
	list->size = 0;
	return (list);
}

void	sorted_insert(t_list *list, t_node *node)
{
	t_node *tmp;
	
	if(list->start == NULL)
		list->start = node;
	else if (node->freq < list->start->freq)
	{
		node->next = list->start;
		list->start = node;
	}
	else
	{
		tmp = list->start;
		while(tmp->next && tmp->next->freq <= node->freq)
			tmp = tmp->next;
		node->next = tmp->next;
		tmp->next = node;
	}
	list->size++;
}

t_node	*create_node(int *freq_table, int *i)
{
	t_node	*new_node;
	
	new_node = calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->c = *i;
	new_node->freq = freq_table[*i];
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_node	*remove_node(t_list *list)
{
	t_node	*tmp;

	tmp = NULL;
	if(list->start)
	{
		tmp = list->start;
		list->start = tmp->next;
		tmp->next = NULL;
		list->size--;
	}
	return (tmp);
}

void	fill_list(int *freq_table, t_list *list)
{
	int		i;
	t_node	*new_node;

	i = 0;
	while (i < 128)
	{
		if (freq_table[i] > 0)
		{
			new_node = create_node(freq_table, &i);
			if (!new_node)
				return ;
			sorted_insert(list, new_node);
		}
		i++;
	}
}

void	print_list(t_list *list)
{
	t_node	*tmp;

	tmp = list->start;
	printf("----------- Lista Ordenada -----------\n Tamanho: %d\n", list->size);
	while(tmp)
	{
		printf("O caractere %c aparece %d vezes\n", tmp->c, tmp->freq);
		tmp = tmp->next;
	}
}