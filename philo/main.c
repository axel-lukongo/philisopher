/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:49:20 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/21 14:07:04 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief in the routine i make a loop who gone take fork while all the philos
 * ain't eat enought or are not dead
 * 
 * @param arg 
 * @return void* 
 */
void	*routine(void *arg)
{
	t_data	*data;

	data = arg;
	data->launch = 0;
	while (ft_check_state(data) != DEAD && data->philo->dead != DEAD
		&& data->nb_meal != data->time_to.nbr_eat)
	{
		pthread_mutex_unlock(&data->philo->state);
		get_fork_eat(data);
	}
	if ((data->nb_meal != data->time_to.nbr_eat || data->philo->dead == DEAD)
		&& data->philo->terminate == 0)
		print_death(data, "\033[1;31mis died\033[0m", data->id_philo_dead);
	else if (data->philo->dead != DEAD)
		print_action(data, "\033[1;33meat enought\033[0m");
	data->philo->terminate++;
	pthread_mutex_unlock(&data->philo->state);
	return (NULL);
}

/**
 * @brief in this function i creat the process i throw the even first
 * and the odd just later
 * 
 * @param data the data of my program and this is where i declare my thread
 * @param nb_philo the number of philo
 */
void	creat_process(t_data *data, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&data->philo->thread[i], NULL, routine,
				&data[i]) == -1)
			write(2, "Cannot create the thread\n", 25);
		i++;
		i++;
	}
	i = 1;
	usleep(800);
	while (i < nb_philo)
	{
		if (pthread_create(&data->philo->thread[i], NULL, routine,
				&data[i]) == -1)
			write(2, "Cannot create the thread\n", 25);
		i++;
		i++;
	}
}

/**
 * @brief here i init every thing what i need and i throw a process
 * who should be the monitor, it will check if one of the philo are dead
 * 
 * @param ac 
 * @param av 
 * @return int 
 */
int	start_process(int ac, char **av)
{
	t_data		*data;
	int			i;

	i = -1;
	data = NULL;
	if (init_data(&data, ac, av) == ERROR)
		return (ERROR);
	if (init_time(&data) == ERROR)
		return (ERROR);
	init_mutex(data);
	creat_process(data, ft_atoi(av[1]));
	pthread_create(&data->philo->death, NULL, check_death, data);
	while (++i < ft_atoi(av[1]))
		pthread_join(data->philo->thread[i], NULL);
	pthread_join(data->philo->death, NULL);
	destroy_mutex(data);
	ft_free(data);
	return (0);
}

int	main(int ac, char **av)
{
	if ((parsing(ac, av) == ERROR) || (ac < 5 || ac > 6))
	{
		printf("\033[1;31mError of arguments\033[0m \n");
		printf("\033[1;31mexec :[nb_philo][time to die]");
		printf("[time to eat][time to sleep](nb_meal) \n");
		return (ERROR);
	}
	return (start_process(ac, av));
}
