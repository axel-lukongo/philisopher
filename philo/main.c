/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:48:51 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/11 14:45:22 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *func1(void * arg)
{
	while (1)
	{
		sleep(1);
		printf("1\n");
	}
	return (NULL);
	//pthread_exit(NULL);
}

void *func2(void * arg)
{
	while (1)
	{
		sleep(1);
		printf("2\n");
	}
	return (NULL);
	//pthread_exit(NULL);
}


void *func4(void * arg)
{
	while (1)
	{
		sleep(1);
		printf("4\n");
	}
	return (NULL);
	//pthread_exit(NULL);
}

int main(int ac, char **av)
{
	pthread_t t1;
	pthread_t t2;

	if ((parsing(ac, av) == ERROR) || (ac < 4 || ac > 5))
		return(ERROR);
	pthread_create(&t1, NULL, func2, NULL);
	pthread_create(&t2, NULL, func2, NULL);
	func1(NULL);
//	pthread_join(t1, NULL);
	//pthread_join(t2, NULL);
	//for(int i = 0; i < 100000; i++)
	return(0);
}