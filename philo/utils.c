/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:24:12 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/31 13:59:17 by alukongo         ###   ########.fr       */
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
/*
int	check_life(t_philosopher *philo)
{
	int i;
	int flag;
	long time_actual;

	time_actual = get_time();
	i = 0;
	while (i < philo->data.nb_philo)
	{
		if ((time_actual - philo->data.time_start) > philo[i].last_eat)
		{
			printf("%ld %d died\n", time_actual - philo->data.time_start, philo->id_philo);
			return (DIE);
		}
		i++;
	}
	i = 0;
	while (i < philo->data.nb_philo)
	{
		if (philo[i].data.nb_meal == philo->data.meal_max)
			flag = EAT_ANOUGHT;
		else
		{
			flag = 1;
			break;
		}
		i++;
	}
	return (flag);
}*/


/*
void *monitor_function(void *arg)
{
	t_philosopher *philo;

	philo = (t_philosopher *) arg;
	while (1)
	{
		
	}
}

void monitor(t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
	{
		ret = pthread_create(&philo[i].thread, NULL, monitor_function, &philo[i]);
		usleep(philo->data.time_to_eat / 10);
	}
	join_thread(philo);
}
*/
void join_thread(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->data.nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}