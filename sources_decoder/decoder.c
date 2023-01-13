/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:49:08 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/10 17:08:27 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "labs.h"

char *receive_info(void)
{
	int     shmid;
	key_t   key;
	char    *shmp;
	char	*str;

	key = ftok(".shmfile", 65);
	shmid = shmget(key, 2, 0644|IPC_CREAT);
	if (shmid == -1)
	{
		perror("Shared memory");
		return (NULL);
	}
	shmp = shmat(shmid, NULL, 0);
	if (shmp == (void *) -1)
	{
		perror("Shared memot attach");
		return (NULL);
	}
	sleep(1);
	printf("--- String recebida --- %s\n", shmp);
	str = strdup(shmp);
	if (shmdt(shmp) == -1)
	{
		perror("shmdt");
		return (NULL);
	}
	return (str);
}

int main(void)
{
	char	*ptr;
	
	ptr = receive_info();
	printf("FOI, DEU CERTO: %s\n", ptr);
	return 0;
}