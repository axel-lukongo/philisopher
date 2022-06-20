/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 01:50:26 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/20 13:30:50 by alukongo         ###   ########.fr       */
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

int	parsing(int ac, char **av)
{
	long long	ret;

	if (ft_digit(ac, av) == ERROR)
		return (ERROR);
	ac -= 1;
	while (--ac > 0)
	{
		ret = ft_atoi(av[ac]);
		if (ret > 2147483647 || ret < 1)
			return (ERROR);
	}
	return (0);
}
