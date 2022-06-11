/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:36:58 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/11 01:02:09 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO
# define EAT_ANOUGHT 12
# define ALIVE 2
# define IS_DEAD -5
# define ERROR 1
# define WIN 3
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
	int meal_max;
	int time_to_eat;
	int time_to_sleep;
	int time_eat_each;
	pthread_mutex_t	*fork;
	pthread_mutex_t	sleeper;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
	long			time_start;
	long			time_ustart;
} t_data;

typedef struct s_philosopher
{
	int	left;
	int	right;
	int win;
	int	id_philo;
	int	last_eat;
	int *is_die;
	t_data	data;
	pthread_t	thread;
} t_philosopher;

t_data	g_data;

int		parsing(int ac, char **av);
long long	ft_atoi(const char *str);
void	*func1(void * arg);
void	init_data(t_data *data, char **av, int ac);
void	init_philo(t_philosopher philo[], int nb_philo, char **av, int ac);
int		init_mutex(pthread_mutex_t mutex[], t_data data);
long	get_time(void);
int		check_life(t_philosopher *philo);
void	join_thread(t_philosopher *philo);
void	ft_usleep(t_philosopher *philo, int time_to);
//int		verif_death(t_philosopher *philo, int nb_philo, int time_actual);
#endif // !PHILO
