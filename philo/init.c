/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:07:04 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/16 17:46:37 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, char **av, int ac)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->nb_meal = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->time_eat_each = ft_atoi(av[5]);
}
 void init_philo(t_philosopher philo[], int ac)
 {
	int i;

	i = 0;
	while (i < ac)
	{
		memset(&philo[i], 0, sizeof(t_philosopher));
		philo[i].number = i;
		i++;
	}
	//printf("ici\n");
 }
 