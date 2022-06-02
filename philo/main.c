/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:48:51 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/02 13:56:43 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verif_death(t_philosopher *philo, int nb_philo, int time_actual)
{
	int	i;
	int	j;
	//long time_actual;

	//time_actual = get_time();
	i = 0;
	j = -1;
	while (i < nb_philo)
	{
		pthread_mutex_lock(&philo->data.dead);
		if ((time_actual - philo->last_eat) > philo->data.time_to_die)
		{
			while (++j < nb_philo)
				philo[j].is_die = IS_DEAD;
		//	printf("philo[%d] is_dead\n" , philo[i].id_philo);
			break;
		}
	//	pthread_mutex_unlock(&philo->data.dead);
		i++;
	}
	pthread_mutex_unlock(&philo->data.dead);
	return (i);
}

void	eat(t_philosopher *philo)
{
	t_data *data;
	long	time;

	data = &philo->data;
	philo->data.nb_meal = 0;
	time = get_time() - philo->data.time_start;
	verif_death(philo, data->nb_philo, time);
	if (philo->data.nb_meal != philo->data.meal_max && philo->is_die != IS_DEAD)
	{
		pthread_mutex_lock(&data->fork[philo->right]);
		printf("%ld %d has take fork \n", get_time() - philo->data.time_start, philo->id_philo);
		pthread_mutex_lock(&data->fork[philo->left]);
		printf("%ld %d has take fork\n", get_time() - philo->data.time_start, philo->id_philo);
		pthread_mutex_lock(&philo->data.eat);
		printf("%ld %d eat\n", get_time() - philo->data.time_start, philo->id_philo);
		philo->data.nb_meal = philo->data.nb_meal + 1;
		time = get_time() - philo->data.time_start;
		pthread_mutex_unlock(&philo->data.eat);
		usleep(philo->data.time_to_eat * 1000);
		philo->last_eat = get_time() - philo->data.time_start;
		pthread_mutex_unlock(&data->fork[philo->right]);
		pthread_mutex_unlock(&data->fork[philo->left]);
	}
	verif_death(philo, data->nb_philo, time);
}

void	he_sleep(t_philosopher *philo)
{
	long time;

	time = get_time() - philo->data.time_start;
	verif_death(philo, philo->data.nb_philo, time);
	//printf("die = %d\n", philo[1].is_die);
	if(philo->is_die != IS_DEAD)
	{
		printf("%ld %d is sleeping\n", get_time() - philo->data.time_start, philo->id_philo);
		usleep(philo->data.time_to_sleep * 1000);
		printf("%ld %d is thinking\n", get_time() - philo->data.time_start, philo->id_philo);
	}
}

void	*func1(void *arg)
{
	t_philosopher *philo;

	philo = (t_philosopher *)arg;
	while(philo->data.nb_meal != philo->data.meal_max && philo->is_die != IS_DEAD)
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
	
	i = -1;
	init_philo(philo, nb_philo, av, ac);
	while (++i < nb_philo)
	{
		if(i %2 == 0)
			ret = pthread_create(&philo[i].thread, NULL, func1, &philo[i]);
		usleep(philo->data.time_to_eat / 10);
	}
	usleep(800);
	i = -1;
	while (++i < nb_philo)
	{
		if(i %2 == 1)
			ret = pthread_create(&philo[i].thread, NULL, func1, &philo[i]);
		usleep(philo->data.time_to_eat / 10);
	}
	join_thread(philo);
}

int	main(int ac, char **av)
{
	if ((parsing(ac, av) == ERROR) || (ac < 5 || ac > 6))
		return(ERROR);
	else
		start_process(ft_atoi(av[1]), ac, av);
	return(0);
}
