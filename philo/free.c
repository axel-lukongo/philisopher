/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:49:10 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/12 00:11:06 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data *data)
{
	if (data)
	{
		if (data->state.id)
			free(data->state.id);
		if (data->time)
			free(data->time);
		if (data->philo->fork)
			free(data->philo->fork);
		if (data->philo)
			free(data->philo);
		free(data);
	}
}

void	ft_free2(t_data *data, t_state *state)
{
	if (state)
	{
		if (state->id)
			free(state->id);
		free(state);
	}
	ft_free(data);
	write(2, "Allocation failed\n", 18);
}

void	ft_free3(t_data *data, t_state *state, t_thread *philo)
{
	if (philo)
		free(philo);
	ft_free2(data, state);
}

void	ft_unlock_all(t_data *data)
{
	pthread_mutex_unlock(&data->philo->state);
	pthread_mutex_unlock(&data->philo->fork[data->id]);
	pthread_mutex_unlock(&data->philo->fork[data->left]);
}

