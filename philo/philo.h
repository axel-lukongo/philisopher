/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:36:58 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/12 16:26:08 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO
# define ERROR 1
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_philosopher
{
	pthread_t	philo;
} t_philosopher;

typedef struct s_data
{
	int	nb_philo;
	int time_to_die;
	int nb_meal;
	int time_to_eat;
	int time_to_sleep;
	int time_eat_each;
} t_data;

int	parsing(int ac, char **av);
int	ft_atoi(const char *str);
void	*func1(void * arg);
void	init_data(t_data *data, char **av, int ac);
#endif // !PHILO