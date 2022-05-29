/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:07:04 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/28 15:43:11 by alukongo         ###   ########.fr       */
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
	data->nb_meal = 0;
	if (ac == 6)
		data->meal_max = ft_atoi(av[5]);
	else
		data->meal_max = -1;
}

void	init_philo(t_philosopher philo[], int nb_philo, char **av, int ac)
{
	int i;
	pthread_mutex_t fork[nb_philo];

	i = 0;
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
	pthread_mutex_init(&data.eat, NULL);
	return (1);
}
