/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:48:51 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/26 22:28:31 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philosopher *philo, t_data *data)
{
	int left;
	int right;
//	t_data data;


	(void) data;
	left = philo->left;
	right = philo->right;
	pthread_mutex_lock(&philo->data.fork[right]);
	printf("%ld %d has take fork\n", get_time() - philo->data.time_start, philo->id_philo);
	pthread_mutex_lock(&philo->data.fork[left]);
	printf("%ld %d has take fork\n", get_time() - philo->data.time_start, philo->id_philo);
	pthread_mutex_lock(&philo->data.eat);
	printf("%ld %d eat\n", get_time() - philo->data.time_start, philo->id_philo);
	pthread_mutex_unlock(&philo->data.eat);
	usleep(500000);
//	usleep(philo->data.time_to_eat * 1000);
	//printf("time = %ld id_philo = %d \n", get_time() -  philo->data.time_start, philo->id_philo);
	pthread_mutex_unlock(&philo->data.fork[right]);
	pthread_mutex_unlock(&philo->data.fork[left]);
}

/*the problem come frome the last argument 
the seconde thread take it for start his seconde turn*/
void	he_sleep(t_philosopher *philo)
{
	printf("%ld %d is sleeping\n", get_time() - philo->data.time_start, philo->id_philo);
	usleep(100000);
	//usleep(philo->data.time_to_sleep * 1000);
	printf("%ld %d is thinking\n", get_time() - philo->data.time_start, philo->id_philo);
}

void	*func1(void *arg)
{
	t_philosopher *philo;
	t_data	*data;

	philo = (t_philosopher *)arg;
	data = &philo->data;
	while(1)
	{
		eat(philo, data);
		he_sleep(philo);
	}
	return (NULL);
}

void	start_process(int nb_philo, int ac, char **av)
{
	t_philosopher philo[nb_philo];
	int i;
	int ret;
	i = 0;
	init_philo(philo, nb_philo, av, ac);
	printf("");
	while (i < nb_philo)
	{
		ret = pthread_create(&philo[i].thread, NULL, func1, &philo[i]);
		usleep(philo->data.time_to_sleep * 1000);
		//ret = pthread_create(&philo[1].thread, NULL, func1, &philo[i]);
		if (ret)
			printf("Error\n");
		i++;
		//i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int main(int ac, char **av)
{
	if ((parsing(ac, av) == ERROR) || (ac < 5 || ac > 6))
		return(ERROR);
	else
		start_process(ft_atoi(av[1]), ac, av);
	return(0);
}
