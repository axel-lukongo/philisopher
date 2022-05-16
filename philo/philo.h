/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:36:58 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/16 14:29:35 by alukongo         ###   ########.fr       */
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
	int	number;
	pthread_t	thread;
} t_philosopher;

typedef struct s_data
{
	int	nb_philo;
	int time_to_die;
	int nb_meal;
	int time_to_eat;
	int time_to_sleep;
	int time_eat_each;
	pthread_mutex_t write;
	pthread_mutex_t lock;
} t_data;

int	parsing(int ac, char **av);
int	ft_atoi(const char *str);
void	*func1(void * arg);
void	init_data(t_data *data, char **av, int ac);
 void init_philo(t_philosopher philo[], int ac);
#endif // !PHILO
