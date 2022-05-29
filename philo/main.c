/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:48:51 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/29 05:49:13 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philosopher *philo)
{
	t_data *data;

	data = &philo->data;
	if (philo->data.nb_meal != philo->data.meal_max)
	{
		pthread_mutex_lock(&data->fork[philo->right]);
		printf("%ld %d has take fork \n", get_time() - philo->data.time_start, philo->id_philo);
		pthread_mutex_lock(&data->fork[philo->left]);
		printf("%ld %d has take fork\n", get_time() - philo->data.time_start, philo->id_philo);
		pthread_mutex_lock(&philo->data.eat);
		printf("%ld %d eat\n", get_time() - philo->data.time_start, philo->id_philo);
		philo->data.nb_meal = philo->data.nb_meal + 1;
		pthread_mutex_unlock(&philo->data.eat);
		usleep(philo->data.time_to_eat * 1000);
		pthread_mutex_unlock(&data->fork[philo->right]);
		pthread_mutex_unlock(&data->fork[philo->left]);
	}
}

void	he_sleep(t_philosopher *philo)
{
	printf("%ld %d is sleeping\n", get_time() - philo->data.time_start, philo->id_philo);
	usleep(philo->data.time_to_sleep * 1000);
	printf("%ld %d is thinking\n", get_time() - philo->data.time_start, philo->id_philo);
}

void	*func1(void *arg)
{
	t_philosopher *philo;

	philo = (t_philosopher *)arg;
	while(philo->data.nb_meal != philo->data.meal_max)
	{
		eat(philo);
		he_sleep(philo);
	}
	return (NULL);
}

void	start_process(int nb_philo, int ac, char **av)
{
	t_philosopher philo[nb_philo];
	int i;
	int ret;
	i = 0;
	init_philo(philo, nb_philo, av, ac);
	while (i < nb_philo)
	{
		if(i %2 == 0)
			ret = pthread_create(&philo[i].thread, NULL, func1, &philo[i]);
		usleep(philo->data.time_to_eat / 10);
		i++;
	}
	usleep(800);
	i = 0;
	while (i < nb_philo)
	{
		if(i %2 == 1)
			ret = pthread_create(&philo[i].thread, NULL, func1, &philo[i]);
		usleep(philo->data.time_to_eat / 10);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	if (philo[i-1].data.nb_meal == philo->data.meal_max)
		write(1, "every body eat anought\n", 24);
}

int	main(int ac, char **av)
{
	if ((parsing(ac, av) == ERROR) || (ac < 5 || ac > 6))
		return(ERROR);
	else
		start_process(ft_atoi(av[1]), ac, av);
	return(0);
}
