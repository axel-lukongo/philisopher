/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 01:50:26 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/11 23:54:13 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_digit(int ac, char **av)
{
	int		i;
	char	c;

	while (--ac)
	{
		i = -1;
		while (av[ac][++i])
		{
			c = av[ac][i];
			if (c < '0' || c > '9')
				return (ERROR);
		}
	}
	return (0);
}

/*
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
*/

int parsing(int ac, char **av)
{
	long long ret;
	if (ft_digit(ac, av) == ERROR)
		return(ERROR);
	ac -= 1;
	while (--ac > 0)
	{
		ret = ft_atoi(av[ac]);
		if (ret > 2147483647 || ret <= 1)
			return(ERROR);
	}
	return(0);
}