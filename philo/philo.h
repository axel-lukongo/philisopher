/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:36:58 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/28 13:25:47 by alukongo         ###   ########.fr       */
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

typedef struct s_data
{
	int	nb_philo;
	int time_to_die;
	int nb_meal;
	int time_to_eat;
	int time_to_sleep;
	int time_eat_each;
	pthread_mutex_t	*fork;
	pthread_mutex_t	sleeper;
	pthread_mutex_t	eat;
	long			time_start;
	long			time_ustart;
} t_data;

typedef struct s_philosopher
{
	int	left;
	int	right;
	int	id_philo;
	t_data	data;
	pthread_t	thread;
} t_philosopher;

t_data	g_data;

int		parsing(int ac, char **av);
int		ft_atoi(const char *str);
void	*func1(void * arg);
void	init_data(t_data *data, char **av, int ac);
void	init_philo(t_philosopher philo[], int nb_philo, char **av, int ac);
int		init_mutex(pthread_mutex_t mutex[], t_data data);
long	get_time(void);
#endif // !PHILO
