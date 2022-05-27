/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:58:18 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/24 00:29:11 by alukongo         ###   ########.fr       */
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
			if ((c < '0' || c > '9') && (c != '-' && c != ' '))
				return (ERROR);
		}
	}
	return (0);
}

int parsing(int ac, char **av)
{
	if (ft_digit(ac, av) == ERROR)
		return(ERROR);
	return(0);
}
