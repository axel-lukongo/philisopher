/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:48:51 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/11 01:30:56 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int death(t_philosopher	*philo)
{
	long time_actual;
	int i;
	int t;

	pthread_mutex_lock(&philo->data.dead);
	t = philo->data.nb_meal;
	pthread_mutex_unlock(&philo->data.dead); //2 lock
	i = 0;
	while (i < philo->data.nb_philo)
	{
		time_actual = get_time() - philo->data.time_start;
		if(t == philo->data.meal_max) //1 nolock
			return (WIN);
		else if (philo->last_eat > 0) //2lock 1 nolock
		{
			if ((time_actual - philo->last_eat) >= philo->data.time_to_die) //2 lock
			{
				*philo->is_die = IS_DEAD; //1 nolock
				printf("%ld %d is_dead\n" , get_time() - philo->data.time_start, philo[i].id_philo);
				pthread_mutex_unlock(&philo->data.dead); //2 lock
				return(IS_DEAD);
			}
		}
		i++;
	}
		pthread_mutex_unlock(&philo->data.dead);
	return (0);
}

void *check_death(void *arg)
{
	int ret;
	t_philosopher *philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		ret = death(&philo[0]);
		if (ret == IS_DEAD || ret == WIN)
			break;
		usleep(100);
	}	
	return(NULL);
}

//je vais essayer de locker avec le lock eat
void	eat(t_philosopher *philo)
{
	t_data *data;
	long	time;

	data = &philo->data;
	time = get_time() - philo->data.time_start;
	pthread_mutex_lock(&data->sleeper);
	if (philo->data.nb_meal != philo->data.meal_max && *philo->is_die != IS_DEAD)
	{
		pthread_mutex_unlock(&data->sleeper);
		pthread_mutex_lock(&data->fork[philo->right]);
		if(*philo->is_die != IS_DEAD)
			printf("%ld %d \033[3;34mhas take fork\033[0m \n", get_time() - philo->data.time_start, philo->id_philo);
		pthread_mutex_lock(&data->fork[philo->left]);
		if(*philo->is_die != IS_DEAD)
			printf("%ld %d \033[3;34mhas take fork\033[0m \n", get_time() - philo->data.time_start, philo->id_philo);
		pthread_mutex_lock(&philo->data.eat);
		if(*philo->is_die != IS_DEAD)
			printf("%ld %d \033[3;35meat\033[0m \n", get_time() - philo->data.time_start, philo->id_philo);
		pthread_mutex_lock(&philo->data.dead);
		philo->last_eat = get_time() - philo->data.time_start;
		pthread_mutex_unlock(&philo->data.dead);
		pthread_mutex_lock(&philo->data.dead);
		philo->data.nb_meal += 1;
		pthread_mutex_unlock(&philo->data.dead);
		ft_usleep(philo, philo->data.time_to_eat);
		philo->last_eat = get_time() - philo->data.time_start;
		pthread_mutex_unlock(&philo->data.eat);
		pthread_mutex_unlock(&data->fork[philo->right]);
		pthread_mutex_unlock(&data->fork[philo->left]);
	}
	pthread_mutex_unlock(&data->sleeper);
}

void	he_sleep(t_philosopher *philo)
{
	if(*philo->is_die != IS_DEAD)
	{
		if(*philo->is_die != IS_DEAD)
			printf("%ld %d \033[3;33mis sleeping\033[0m \n", get_time() - philo->data.time_start, philo->id_philo);
		ft_usleep(philo, philo->data.time_to_sleep);
		if(*philo->is_die != IS_DEAD)
			printf("%ld %d \033[3;32mis thinking\033[0m\n", get_time() - philo->data.time_start, philo->id_philo);
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
	join_thread(philo);
}

int	main(int ac, char **av)
{
	if ((parsing(ac, av) == ERROR) || (ac < 5 || ac > 6))
	{
		printf("\033[3;31mError of arguments\033[0m \n");
		printf("\033[3;31m exec :[nb_philo][time to die]");
		printf("[time to eat][time to sleep](nb_meal) \n");
		return(ERROR);
	}
	else
		start_process(ft_atoi(av[1]), ac, av);
	return(0);
}
