/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:48:42 by alukongo          #+#    #+#             */
/*   Updated: 2022/06/20 13:22:38 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# define ERROR -1
# define THINKING 0
# define EATING 2
# define SLEEP 3
# define NB_MAX_THREAD 1024
# define DEAD -2
# define ID_STATE 4

typedef struct s_time {
	long	r_start;
	long	r_ustart;
	long	runtime;
}				t_time;

typedef struct s_thread {
	int				terminate;
	int				dead;
	pthread_t		thread[NB_MAX_THREAD];
	pthread_t		death;
	pthread_mutex_t	lock;
	pthread_mutex_t	state;
	pthread_mutex_t	*fork;
	pthread_mutex_t	runtime;
}				t_thread;

typedef struct s_time_to {
	long			die;
	long			sleep;
	long			eat;
	long			nbr_eat;
}				t_time_to;

typedef struct s_state {
	int				*id;
}				t_state;

typedef struct s_data {
	int				id;
	int				id_philo_dead;
	int				launch;
	long			last_eat;
	int				nb_meal;
	int				nb_philo;
	int				left;
	int				right;
	int				death;
	t_time_to		time_to;
	t_time			*time;
	t_thread		*philo;
	t_state			state;
}				t_data;

int			ft_isdigit(int c);
long long	ft_atoi(const char *str);
long		get_time(int flag);
long		ft_abs(long nb);
int			parsing(int ac, char **av);

int			init_philo(t_time_to time_to, t_data *data, int nb_philo);

int			init_data(t_data **data, int ac, char **av);
void		init_mutex(t_data *data);
int			ft_alloc(t_data	**data, t_state *state, t_thread **philo,
				int nb_philo);
void		print_action(t_data *data, char *str);
void		ft_get_sleep(t_data *data);
void		ft_get_eat(t_data *data);
void		ft_get_think(t_data *data);
void		print_death(t_data *data, char *str, int id);

void		get_fork_eat(t_data *data);
void		*routine(void	*arg);
int			start_process(int ac, char **av);

//void	*ft_timer(void *arg);
int			init_time(t_data **data);
void		print_time(t_data *data);
void		*check_death(void	*arg);

void		ft_free(t_data *data);
void		ft_free2(t_data *data, t_state *state);
void		ft_free3(t_data *data, t_state *state, t_thread *philo);
void		destroy_mutex(t_data *data);
long		update_runtime(t_data *data);
void		ft_usleep(t_data *data, long time_in_ms);
void		ft_usleep2(t_data *data, long time_in_ms);
int			ft_check_state(t_data *data);
void		ft_unlock_all(t_data *data);

#endif
