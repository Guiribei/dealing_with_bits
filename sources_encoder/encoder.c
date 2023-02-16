/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:13:14 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/15 12:56:19 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

int	get_str_size(char **dict, char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		size = size + strlen(dict[(int)(str[i])]);
		i++;
	}
	return (size + 1);
}

char	*encode(char **dict, char *str)
{
	char	*code;
	int		i;
	int		size;

	i = 0;
	size = get_str_size(dict, str);
	code = calloc(size + 1, sizeof(char));
	while (str[i])
	{
		strcat(code, dict[(int)(str[i])]);
		i++;
	}
	return (code);
}

char	*compress(char *code)
{
	int		i;
	char	byte;
	char	aux;
	int		pos;
	char	*zip;
	char	c[2];
	int		res;

	i = 0;
	byte = 0;
	aux = 0;
	pos = 7;
	zip = calloc(strlen(code), sizeof(char));
	if (!zip)
		return (NULL);
	res = strlen(code) % 8;
	if (res == 0)
	{
		while (code[i])
		{
			aux = 1;
			if (code[i] == '1')
			{
				aux = aux << pos;
				byte = byte | aux;
			}
			pos--;
			if (pos < 0)
			{
				c[0] = byte;
				c[1] = '\0';
				zip = strcat(zip, c);
				byte = 0;
				pos = 7;
			}
			i++;
		}
	}
	else
	{
		while (i < ((int)(strlen(code)) - res) && code[i])
		{
			aux = 1;
			if (code[i] == '1')
			{
				aux = aux << pos;
				byte = byte | aux;
			}
			pos--;
			if (pos < 0)
			{
				c[0] = byte;
				c[1] = '\0';
				zip = strcat(zip, c);
				byte = 0;
				pos = 7;
			}
			i++;
		}
		while (code[i])
		{
			c[0] = code[i];
			c[1] = '\0';
			zip = strcat(zip, c);
			i++;
		}
	}
	return (zip);
}
