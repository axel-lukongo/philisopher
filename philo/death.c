/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:49:29 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/11 22:23:01 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_terminate(t_data *data)
{
	pthread_mutex_lock(&data->philo->state);
	return (data->philo->terminate);
}

int	check_terminate(t_data *data)
{
	if (ft_check_terminate(data) == data->nb_philo)
	{
		pthread_mutex_unlock(&data->philo->state);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->philo->state);
	return (0);
}

int	death(t_data *data, int count, int i)
{
	i = 0;
	while (i < count)
	{
		if ((update_runtime(data) - data[i].last_eat > data->time_to.die)
			&& data->state.id[i] != DEAD)
		{
			pthread_mutex_unlock(&data->philo->runtime);
			pthread_mutex_lock(&data->philo->state);
			data->state.id[i] = DEAD;
			data->philo->dead = DEAD;
			pthread_mutex_unlock(&data->philo->state);
			data->death++;
			if (data->death == data->nb_philo)
				return (1);
		}
		else
		{
			pthread_mutex_unlock(&data->philo->runtime);
			i++;
		}
		if (check_terminate(data) == 1)
			return (1);
	}
	return (0);
}

void	*check_death(void	*arg)
{
	t_data	*data;
	int		count;
	int		i;

	i = 0;
	data = arg;
	count = data->nb_philo;
	while (1)
	{
		if (death(data, count, i) == 1)
			return (NULL);
	}
	return (NULL);
}
