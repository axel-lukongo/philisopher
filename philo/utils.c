/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:24:12 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/10 14:28:44 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	i;
	int		signe;
	int		nbr;

	nbr = 0;
	signe = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '+')
			signe = signe * 1;
		if (str[i] == '-')
			signe = signe * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - 48;
		i++;
	}
	nbr = nbr * signe;
	return (nbr);
}


long	get_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (0);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void ft_usleep(t_philosopher *philo, int time_to)
{
	long var;
	long test;

	
	var = get_time();
	while (1)
	{
		test = get_time() - var;
		pthread_mutex_lock(&philo->data.dead);
		if (test > time_to || *philo->is_die == IS_DEAD)
			break;
		pthread_mutex_unlock(&philo->data.dead);
		test = time_to - test;
		if(test < 1000)
			usleep(test / 10);
		else
			usleep(100);
	}
}
int	clear_mutex(t_philosopher *philo)
{
	int	ret;
	int	i;

	i = -1;
	while (++i < philo->data.nb_philo)
	{
		ret = pthread_mutex_destroy(&philo->data.fork[i]);
	}
	ret = pthread_mutex_destroy(&philo->data.eat);
	ret = pthread_mutex_destroy(&philo->data.dead);
	ret = pthread_mutex_destroy(&philo->data.sleeper);
	return (ret);
}

void join_thread(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->data.nb_philo && *philo->is_die != IS_DEAD)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	if (*philo->is_die != IS_DEAD)
		printf("eat enough\n");
	clear_mutex(philo);
}
