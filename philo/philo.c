/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:48:52 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/11 21:10:07 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_sleep(t_data *data)
{
	if (ft_check_state(data) != DEAD && data->philo->dead != DEAD)
	{
		data->state.id[data->id] = SLEEP;
		pthread_mutex_unlock(&data->philo->state);
		ft_print_action(data, "\033[1;36mis sleeping\033[0m");
		ft_usleep(data, data->time_to.sleep);
		if (ft_check_state(data) == DEAD || data->philo->dead == DEAD)
		{
			pthread_mutex_unlock(&data->philo->state);
			return ;
		}
		else
			pthread_mutex_unlock(&data->philo->state);
		ft_get_think(data);
	}
	else
		pthread_mutex_unlock(&data->philo->state);
}

void	ft_get_eat(t_data *data)
{
	if (ft_check_state(data) != DEAD && data->philo->dead != DEAD)
	{
		data->state.id[data->id] = EATING;
		pthread_mutex_unlock(&data->philo->state);
		data->nb_meal++;
		ft_print_action(data, "\033[3;33mis eating\033[0m");
		data->eat_last = update_runtime(data);
		pthread_mutex_unlock(&data->philo->runtime);
		ft_usleep(data, data->time_to.eat);
		pthread_mutex_unlock(&data->philo->fork[data->id]);
		pthread_mutex_unlock(&data->philo->fork[data->left]);
		if (ft_check_state(data) == DEAD || data->philo->dead == DEAD
			|| data->nb_meal == data->time_to.eat)
		{
			pthread_mutex_unlock(&data->philo->state);
			return ;
		}
		pthread_mutex_unlock(&data->philo->state);
		ft_get_sleep(data);
	}
	else
		ft_unlock_all(data);
}

void	ft_get_think(t_data *data)
{
	if (ft_check_state(data) != THINKING)
	{
		pthread_mutex_unlock(&data->philo->state);
		ft_print_action(data, "\033[3;36mis thinking\033[0m");
		if (ft_check_state(data) != DEAD && data->philo->dead != DEAD)
		{
			data->state.id[data->id] = THINKING;
			pthread_mutex_unlock(&data->philo->state);
		}
		else
		{
			pthread_mutex_unlock(&data->philo->state);
			return ;
		}
	}
	else
		pthread_mutex_unlock(&data->philo->state);
}

void	one_philo(t_data *data)
{
	ft_usleep(data, 100000);
	if (ft_check_state(data) == DEAD || data->philo->dead == DEAD)
	{
		pthread_mutex_unlock(&data->philo->state);
		pthread_mutex_unlock(&data->philo->fork[data->id]);
		return ;
	}
}

void	ft_get_fork(t_data *data)
{
	if (data->id % 2 == 1 && data->launch != 1)
	{
		data->launch = 1;
		ft_usleep2(data, 2);
	}
	if (data->philo->dead != DEAD)
	{
		if (data->nb_philo == 1)
		{
			one_philo(data);
			return ;
		}
		pthread_mutex_lock(&data->philo->fork[data->right]);
		if (data->philo->dead != DEAD)
			ft_print_action(data, "\033[3;35mhas taken a fork\033[0m");
		pthread_mutex_lock(&data->philo->fork[data->left]);
		if (data->philo->dead != DEAD)
			ft_print_action(data, "\033[3;35mhas taken a fork\033[0m");
		ft_get_eat(data);
	}
}
