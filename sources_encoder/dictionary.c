/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:42:02 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/13 17:10:10 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "labs.h"

char	**init_dict(int	height)
{
	char	**dict;
	int		i;

	dict = calloc(128, sizeof(char *));
	if (!dict)
		return (NULL);
	i = 0;
	while(i < 128)
	{
		dict[i] = calloc(height, sizeof(char));
		i++;
	}
	return (dict);
}

void	create_dict(char **dict, t_node *root, char *direction, int height) 
{
	char	left[height];
	char	right[height];
	
	if(root->left == NULL && root->right == NULL)
		strcpy(dict[(int)(root->c)], direction);
	else
	{
		strcpy(left, direction);
		strcpy(right, direction);
		strcat(left, "0");
		strcat(right, "1");
		create_dict(dict, root->left, left, height);
		create_dict(dict, root->right, right, height);
	}
}

void	clear_dict(char **ptrs)
{
	int	i;

	if (ptrs != NULL)
	{
		i = 0;
		while (i < 128)
		{
			if (ptrs[i] != NULL)
				free(ptrs[i]);
			i++;
		}
		free(ptrs);
		ptrs = NULL;
	}
}

void	print_dict(char **dict)
{
	int	i;

	i = 0;
	printf("\n\t-------Dicionário -------\n");
	while(i < 128)
	{
		if (strlen(dict[i]) > 0)
			printf("\t%d: %s\n", i, dict[i]);
		i++;
	}
}