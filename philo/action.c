/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:49:39 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/20 13:46:28 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data *data, char *str)
{
	pthread_mutex_lock(&data->philo->lock);
	print_time(data);
	pthread_mutex_unlock(&data->philo->runtime);
	printf("%d %s\n", data->id + 1, str);
	pthread_mutex_unlock(&data->philo->lock);
}

void	print_death(t_data *data, char *str, int id)
{
	pthread_mutex_lock(&data->philo->lock);
	print_time(data);
	pthread_mutex_unlock(&data->philo->runtime);
	printf("%d %s\n", id, str);
	pthread_mutex_unlock(&data->philo->lock);
}

int	ft_check_state(t_data *data)
{
	pthread_mutex_lock(&data->philo->state);
	return (data->state.id[data->id]);
}
