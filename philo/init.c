/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:07:04 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/26 18:55:43 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, char **av, int ac)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->time_start = get_time();
	//printf("time_start = %ld\n", data->time_start);
	if (ac == 6)
		data->nb_meal = ft_atoi(av[5]);
}

void	init_philo(t_philosopher philo[], int nb_philo, char **av, int ac)
{
	int i;
	pthread_mutex_t fork[nb_philo];
	//t_data data;

	i = 0;
	//init_data(&data, av, ac);
	init_data(&philo->data, av, ac);
	init_mutex(fork, philo->data);
	while (i < nb_philo)
	{
		memset(&philo[i], 0, sizeof(t_philosopher));
		philo[i].id_philo = i + 1;
		philo[i].right = i;
		philo[i].left = (i + 1) % nb_philo; 
		philo[i].data.fork = &fork[0];
		init_data(&philo[i].data, av, ac);
		i++;
	}
	//printf("time_sleep = %d\n", philo[1].data.time_to_sleep);
}

int	init_mutex(pthread_mutex_t fork[], t_data data)
{
	int	i;
	int ret;
	i = 0;
	while (i < data.nb_philo)
	{
		ret = pthread_mutex_init(&fork[i], NULL);
		if (ret)
			printf("Error\n");
		i++;
	}
	//printf("i = %d\n", i);
	//pthread_mutex_init(&philo->data.eat, NULL);
	return (1);
}
