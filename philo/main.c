/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:48:51 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/08 18:54:07 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int death(t_philosopher *philo)
{
	long time_actual;
	int i;

	i = 0;
	while (i < philo->data.nb_philo)
	{
		time_actual = get_time() - philo->data.time_start;
		pthread_mutex_lock(&philo->data.dead);
		if(philo->data.nb_meal == philo->data.meal_max)
			return (WIN);
		else if (philo->last_eat > 0)
		{
			if ((time_actual - philo->last_eat) >= philo->data.time_to_die)
			{
				*philo->is_die = IS_DEAD;
				//printf("time_actual = %ld philo[%d] last_eat = %d\n", time_actual - philo->last_eat, philo->id_philo,philo->last_eat);
				printf("%ld %d is_dead\n" , get_time() - philo->data.time_start, philo[i].id_philo);
				pthread_mutex_unlock(&philo->data.dead);
				return(IS_DEAD);
			}
		}
		pthread_mutex_unlock(&philo->data.dead);
		i++;
		pthread_mutex_unlock(&philo[i - 1].data.dead);
	}
	return (0);
}

void	eat(t_philosopher *philo)
{
	t_data *data;
	long	time;

	data = &philo->data;
	time = get_time() - philo->data.time_start;
	if (philo->data.nb_meal != philo->data.meal_max && *philo->is_die != IS_DEAD)
	{
		pthread_mutex_lock(&data->fork[philo->right]);
	//	ret = check_death(philo, data->nb_philo, get_time() - philo->data.time_start);
		if(*philo->is_die != IS_DEAD)
			printf("%ld %d has take fork \n", get_time() - philo->data.time_start, philo->id_philo);
		pthread_mutex_lock(&data->fork[philo->left]);
		if(*philo->is_die != IS_DEAD)
			printf("%ld %d has take fork \n", get_time() - philo->data.time_start, philo->id_philo);
		pthread_mutex_lock(&philo->data.eat);
		if(*philo->is_die != IS_DEAD)
			printf("%ld %d eat \n", get_time() - philo->data.time_start, philo->id_philo);
		philo->data.nb_meal += 1;
		philo->last_eat = get_time() - philo->data.time_start;
		ft_usleep(philo, philo->data.time_to_eat);
		philo->last_eat = get_time() - philo->data.time_start;
		pthread_mutex_unlock(&philo->data.eat);
		pthread_mutex_unlock(&data->fork[philo->right]);
		pthread_mutex_unlock(&data->fork[philo->left]);
	}
}

void	he_sleep(t_philosopher *philo)
{
	long	time;
	//int		ret;
	time = get_time() - philo->data.time_start;
	if(*philo->is_die != IS_DEAD)
	{
		if(*philo->is_die != IS_DEAD)
			printf("%ld %d is sleeping\n", get_time() - philo->data.time_start, philo->id_philo);
		ft_usleep(philo, philo->data.time_to_sleep);
		if(*philo->is_die != IS_DEAD)
			printf("%ld %d is thinking\n", get_time() - philo->data.time_start, philo->id_philo);
	}
}

void	*func1(void *arg)
{
	t_philosopher *philo;

	philo = (t_philosopher *)arg;
	while(philo->data.nb_meal != philo->data.meal_max && *philo->is_die != IS_DEAD)
	{
		eat(philo);
		he_sleep(philo);
	}
	return (NULL);
}
/**
 * @brief here i will initialize my philo, creat a thread for every 
 * 
 * @param nb_philo 
 * @param ac 
 * @param av 
 */
void	start_process(int nb_philo, int ac, char **av)
{
	t_philosopher philo[nb_philo];
	int i;
	int ret;
	t_philosopher test[nb_philo];
	
	i = -1;
	init_philo(test, nb_philo, av, ac);
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
	while (1)
	{
		ret = death(philo);
		if (ret == IS_DEAD || ret == WIN)
			break;
		usleep(100);
	}	
	join_thread(philo);
}

int	main(int ac, char **av)
{
	if ((parsing(ac, av) == ERROR) || (ac < 5 || ac > 6))
		return(ERROR);
	else
	{
		start_process(ft_atoi(av[1]), ac, av);
		
	}
	return(0);
}
