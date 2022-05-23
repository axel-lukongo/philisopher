/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:07:04 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/23 18:03:58 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, char **av, int ac)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_meal = ft_atoi(av[5]);
}

void	init_philo(t_philosopher philo[], int nb_philo, char **av, int ac)
{
	int i;
	pthread_mutex_t mutex[nb_philo];

	i = 0;
	init_data(&philo->data, av, ac);
	init_mutex(mutex, philo);
	while (i < nb_philo)
	{
		memset(&philo[i], 0, sizeof(t_philosopher));
		philo[i].id_philo = i;
		philo[i].right = i;
		philo[i].left = (i + 1) % nb_philo; 
		philo[i].data.fork = &mutex[0];
		i++;
	}
}

int	init_mutex(pthread_mutex_t mutex[], t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->data.nb_philo)
	{
		pthread_mutex_init(&mutex[i], NULL);
		//printf("mutex init = %p\n", &mutex[i]);
		i++;
	}
	//printf("i = %d\n", i);
	pthread_mutex_init(&philo->data.eat, NULL);
	return (1);
}
