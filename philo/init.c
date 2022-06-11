/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:49:02 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/11 23:26:06 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_alloc(t_data	**data, t_state *state, t_thread **philo, int nb_philo)
{
	state->id = (int *)malloc(sizeof(int) * nb_philo);
	if (!state->id)
	{
		ft_free2(*data, state);
		return (ERROR);
	}
	*philo = (t_thread *)malloc(sizeof(t_thread));
	if (!*philo)
	{
		ft_free3(*data, state, *philo);
		return (ERROR);
	}
	(*philo)->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* nb_philo);
	if (!(*philo)->fork)
	{
		ft_free3(*data, state, *philo);
		return (ERROR);
	}
	return (0);
}

int	init_philo(t_time_to time_to, t_data *data, int nb_philo)
{
	t_state		state;
	t_thread	*philo;
	int			i;

	i = 0;
	if (ft_alloc(&data, &state, &philo, nb_philo) == 1)
		return (1);
	while (i < nb_philo)
	{
		state.id[i] = ID_STATE;
		data[i].id = i;
		data[i].nb_meal = 0;
		data[i].nb_philo = nb_philo;
		data[i].right = i;
		data[i].left = (i + 1) % nb_philo;
		data[i].last_eat = 0;
		data[i].philo = philo;
		data[i].time_to = time_to;
		data[i].state = state;
		i++;
	}
	return (0);
}

int	check_number(long nb_philo, t_time_to time_to)
{
	if (nb_philo == 2147483648 || time_to.sleep == 2147483648
		|| time_to.eat == 2147483648 || time_to.die == 2147483648
		|| time_to.nbr_eat == 2147483648 || nb_philo == 0
		|| time_to.eat == 1 || time_to.sleep == 1 || time_to.eat == 0
		|| time_to.sleep == 0 || time_to.die == 0)
	{
		return (1);
	}
	return (0);
}

int	init_data(t_data **data, int ac, char **av)
{
	t_time_to		time_to;
	long		nb_philo;

	nb_philo = ft_atoi(av[1]);
	time_to.sleep = ft_atoi(av[4]);
	time_to.eat = ft_atoi(av[3]);
	time_to.die = ft_atoi(av[2]);
	time_to.nbr_eat = -1;
	if (ac == 6)
		time_to.nbr_eat = ft_atoi(av[5]);
	//if (check_number(nb_philo, time_to) == 1)
	//	return (1);
	*data = (t_data *)malloc(sizeof(t_data) * nb_philo);
	if (!*data)
	{
		ft_free(*data);
		write(2, "ERROR ALLOC\n", 11);
		return (ERROR);
	}
	if (init_philo(time_to, *data, nb_philo) == 1)
		return (ERROR);
	return (0);
}
