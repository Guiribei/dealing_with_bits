/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:28:12 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/15 16:28:12 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

static void	clean_quit(t_compress *data)
{
	clear_dict(data->dictionary);
	free(data->text);
	free(data->binary);
	free(data->compressed);
	return ;
}

int	main(void)
{
	t_compress	*data;

	data = (t_compress *)calloc(1, sizeof(t_compress));
	data->dictionary = (char **)calloc(128, sizeof(char *));
	decoder_shm(data);
	decoder_decompress(data);
	clean_quit(data);
	free(data);
	return (0);
}
