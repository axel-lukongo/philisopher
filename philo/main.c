/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:49:20 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/12 00:10:42 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			print_action(data, "\033[1;31mis died\033[0m");
	else if(data->philo->dead != DEAD)
		print_action(data, "\033[1;33meat enought\033[0m");
	data->philo->terminate++;
	pthread_mutex_unlock(&data->philo->state);
	return (NULL);
}

void creat_process(t_data *data ,int nb_philo)
{
	int i;
	
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
		return(ERROR);
	}
	return (start_process(ac, av));
}
