/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:48:51 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/16 18:43:04 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*func1(void * arg)
{
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	(void) arg;
	int i = 0;
	pthread_mutex_lock(&mutex);
	while (i < 10)
	{
		usleep(1000);
		printf("i = %d\n", i++);
		//printf("ici2\n");
	}
	printf("next thread\n");
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

/*
void joint_thread(t_philosopher philo[])
{
	
}*/

void	set_philo(int nb_philo, int ac, char **av)
{
	t_philosopher philo[nb_philo];
	t_data data;
	int i;

	init_data(&data, av, ac);
//	t_data data;
	//pthread_mutex_init(&data.write, NULL);
	i = 0;
	init_philo(philo, ac);
	//printf("philo = %d\n", philo->number);
	while (i < nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, func1, NULL);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int main(int ac, char **av)
{
	if ((parsing(ac, av) == ERROR) || (ac < 5 || ac > 6))
		return(ERROR);
	else
		set_philo(ft_atoi(av[1]), ac, av);
	return(0);
}
