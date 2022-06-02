/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:24:12 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/02 18:19:41 by alukongo         ###   ########.fr       */
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

void ft_usleep(t_philosopher *philo)
{
	int i;
	int ret;

	i = 0;
	while (i < philo->data.time_to_sleep)
	{
		ret = check_death(philo, philo->data.nb_philo, get_time() - philo->data.time_start);
		if (ret == IS_DEAD)
			break;
		usleep(1000);
		i++;
	}
}

void join_thread(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->data.nb_philo && philo->is_die != IS_DEAD)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	if (philo->is_die != IS_DEAD)
		printf("eat anought\n");
}
