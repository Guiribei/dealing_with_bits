/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:41:13 by ridalgo-          #+#    #+#             */
/*   Updated: 2023/01/15 14:14:47 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

char	*decode(char *str, char**dict)
{
	char	*new_str;
	int		j;
	char	c[2];

	j = 0;
	new_str = calloc(strlen(str), sizeof(char));
	while (*str)
	{
		if (strlen(dict[j]) > 0)
		{
			if (strncmp(dict[j], (str), strlen(dict[j])) == 0)
			{
				c[0] = j;
				c[1] = '\0';
				strncat(new_str, c, 1);
				str += strlen(dict[j]);
				j = -1;
			}
		}
		j++;
	}
	return (new_str);
}

int	is_one(char byte, int i)
{
	char	aux;

	aux = (1 << i);
	return (byte & aux);
}

char	*decompress(char *zip, int len)
{
	int		i;
	int		pos;
	char	*str;
	int		res;
	char	c[2];

	i = 0;
	pos = 7;
	str = calloc(len, sizeof(char));
	res = len % 8;
	if (res == 0)
	{
		while (zip[i])
		{
			while (pos >= 0)
			{
				if (is_one(zip[i], pos))
					strcat(str, "1");
				else
					strcat(str, "0");
				pos--;
			}
			pos = 7;
			i++;
		}
	}
	else
	{
		while ((strlen(str) < (unsigned long)(len - res)) && zip[i])
		{
			while (pos >= 0)
			{
				if (is_one(zip[i], pos))
					strcat(str, "1");
				else
					strcat(str, "0");
				pos--;
			}
			pos = 7;
			i++;
		}
		while (zip[i])
		{
			c[0] = zip[i];
			c[1] = '\0';
			strcat(str, c);
			i++;
		}
	}
	return (str);
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

void	decoder_decompress(t_compress *data)
{
	data->binary = decompress(data->compressed, data->len);
	data->text = decode(data->binary, data->dictionary);
	printf("%s\n", data->text);
	return ;
}
