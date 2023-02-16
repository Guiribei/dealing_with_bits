/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shm_decoder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:41:13 by ridalgo-          #+#    #+#             */
/*   Updated: 2023/01/15 14:14:53 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

void	error_handler(void)
{
	perror("Shared memory");
	exit (1);
}

static void	shm_get_memory(t_shm *shm)
{
	shm->key1 = ftok(".shmkey1", SIZE);
	shm->key2 = ftok(".shmkey2", SIZE);
	shm->id1 = shmget(shm->key1, SIZE, IPC_CREAT | 0666);
	if (shm->id1 < 0)
		error_handler();
	shm->text = shmat(shm->id1, NULL, 0);
	if (shm->text == (char *) -1)
		error_handler();
	shm->id2 = shmget(shm->key2, SIZE, IPC_CREAT | 0666);
	if (shm->id2 < 0)
		error_handler();
	shm->numb = shmat(shm->id2, NULL, 0);
	if (shm->numb == (int *) -1)
		error_handler();
	return ;
}

static void	shm_receive_compress(t_shm *shm, t_compress *data)
{
	*(shm->text + 1) = '0';
	data->len += *shm->numb;
	*shm->text = '1';
	while (*(shm->text + 1) == '0')
	{
	}
	*(shm->numb + 1) = 0;
	data->compressed = strdup(shm->text);
	data->compressed[strlen(shm->text)] = 0;
	*shm->numb = 1;
	while (*(shm->numb + 1) == 0)
	{
	}
	return ;
}

static void	shm_receive_dictionary(t_shm *shm, t_compress *data)
{
	int	i;

	i = 0;
	while (i < 128)
	{
		*(shm->numb + 1) = 0;
		data->dictionary[i] = (char *)calloc(1000, sizeof(char));
		data->dictionary[i] = strcpy(data->dictionary[i], shm->text);
		*shm->numb = 1;
		while (*(shm->numb + 1) == 0)
		{
		}
		i++;
	}
	return ;
}

void	decoder_shm(t_compress *data)
{
	t_shm		*shm;

	shm = (t_shm *)calloc(1, sizeof(t_shm));
	shm_get_memory(shm);
	shm_receive_compress(shm, data);
	shm_receive_dictionary(shm, data);
	shmdt(shm->text);
	shmdt(shm->numb);
	free(shm);
}
