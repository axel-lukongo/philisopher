/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:48:13 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/11 02:09:23 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_error(int flag)
{
	if (flag == 1)
	{
		write(2, "Error: Invalid Argument\n", 24);
		write(2, "Negative Value\n", 15);
		return (2147483648);
	}
	if (flag == 2)
	{
		write(2, "Error: Invalid Argument\n", 24);
		write(2, "Two consecutive sign\n", 15);
		return (2147483648);
	}
	if (flag == 3)
	{
		write(2, "Error: Invalid Argument\n", 24);
		write(2, "More than int max\n", 18);
		return (2147483648);
	}
	if (flag == 4)
	{
		write(2, "Error: Invalid Argument\n", 24);
		write(2, "Only number are allowed\n", 24);
		return (2147483648);
	}
	return (0);
}


long	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	res;

	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (ft_error(1));
		i++;
		if (i > 1)
			return (ft_error(2));
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		if (res > 2147483647)
			return (ft_error(3));
		i++;
	}
	if (str[i] != '\0')
		return (ft_error(4));
	return (res);
}
*/

long long	ft_atoi(const char *str)
{
	long			i;
	int				signe;
	long long int	nbr;

	nbr = 0;
	signe = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '+')
			signe = signe * 1;
		if (str[i] == '-')
			signe = signe * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - 48;
		i++;
	}
	nbr = nbr * signe;
	return (nbr);
}
/*
long	ft_abs(long nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}
*/
long	get_time(int flag)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	if (flag == 1)
		printf("[%d] ", current.tv_usec);
	if (flag == 2)
		return (current.tv_sec);
	return (current.tv_usec);
}
