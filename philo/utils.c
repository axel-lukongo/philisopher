/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:48:13 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/11 23:37:09 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *str)
{
	long			i;
	int				signe;
	long long int	nbr;

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

long	get_time(int flag)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	if (flag == 1)
		printf("[%d] ", current.tv_usec);
	if (flag == 2)
		return (current.tv_sec);
	return (current.tv_usec);
}

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->philo->lock);
	pthread_mutex_destroy(&data->philo->state);
	pthread_mutex_destroy(&data->philo->runtime);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->philo->fork[i], NULL);
		i++;
	}
}