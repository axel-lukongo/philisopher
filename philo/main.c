/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:48:51 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/13 17:58:39 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void	*func1(void * arg)
{
	t_data data;
	(void) arg;
	int i = 0;
	pthread_mutex_init(&data.write, NULL);
	pthread_mutex_lock(&data.write);
	while (i < 10)
	{
		usleep(100000);
		printf("i = %d\n", i++);
	}
	printf("next thread\n");
	pthread_mutex_unlock(&data.write);
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
	pthread_mutex_init(&data.write, NULL);
	i = 0;
	while (i < nb_philo)
	{
		pthread_create(&philo[i].philo, NULL, func1, NULL);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		pthread_join(philo[i].philo, NULL);
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
