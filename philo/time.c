/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:48:24 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/11 23:34:24 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_time(t_data **data)
{
	int		i;
	t_time	*time;

	i = 0;
	time = (t_time *)malloc(sizeof(t_time));
	if (!time)
	{
		ft_free(*data);
		write(2, "ERROR ALLOC TIME\n", 18);
		return (ERROR);
	}
	time->r_start = get_time(2);
	time->r_ustart = get_time(0);
	time->runtime = 0;
	while (i < (*data)->nb_philo)
	{
		(*data)[i].time = time;
		i++;
	}
	return (0);
}

long	update_runtime(t_data *data)
{
	pthread_mutex_lock(&data->philo->runtime);
	data->time->runtime = (get_time(2) - data->time->r_start) * 1000
		+ ((get_time(0)) - (data->time->r_ustart)) / 1000;
	return (data->time->runtime);
}

void	print_time(t_data *data)
{
	update_runtime(data);
	printf("\033[1;32m%ld\033[0m ", data->time->runtime);
}

void	ft_usleep(t_data *data, long time_to)
{
	long	start_time;

	start_time = (get_time(2) - data->time->r_start) * 1000
		+ ((get_time(0)) - (data->time->r_ustart)) / 1000;
	while ((update_runtime(data) - start_time) < time_to)
	{
		pthread_mutex_unlock(&data->philo->runtime);
		if (ft_check_state(data) != DEAD && data->philo->dead != DEAD)
		{
			pthread_mutex_unlock(&data->philo->state);
			usleep(time_to / (time_to / 2));
		}
		else
		{
			pthread_mutex_unlock(&data->philo->state);
			return ;
		}
	}
	pthread_mutex_unlock(&data->philo->runtime);
}

void	ft_usleep2(t_data *data, long time_to)
{
	long	start_time;

	start_time = (get_time(2) - data->time->r_start) * 1000
		+ ((get_time(0)) - (data->time->r_ustart)) / 1000;
	while ((update_runtime(data) - start_time) < time_to)
	{
		pthread_mutex_unlock(&data->philo->runtime);
		usleep(time_to / (time_to / 2));
	}
	pthread_mutex_unlock(&data->philo->runtime);
}
