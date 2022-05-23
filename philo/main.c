/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:48:51 by alukongo          #+#    #+#             */
/*   Updated: 2022/05/23 18:33:22 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philosopher *philo)
{
	int left;
	int right;

	left = philo->left;
	right = philo->right;
//	printf("left = %d, right = %d\n", left, right);
	//printf("philo_id = %d\n",philo->id_philo);
	//printf("mutex = %p\n", (void *)philo->data.fork[right]);
	pthread_mutex_lock(&philo->data.fork[right]);
	printf("philo[%d] take right fork\n", philo->id_philo);
	pthread_mutex_lock(&philo->data.fork[left]);
	printf("philo[%d] take left fork\n", philo->id_philo);
	pthread_mutex_lock(&philo->data.eat);
	printf("philo[%d] eat\n", philo->id_philo);
	pthread_mutex_unlock(&philo->data.eat);
	usleep(1000000);
	printf("time_sleep = %d\n", philo[0].data.time_to_sleep);
	pthread_mutex_unlock(&philo->data.fork[right]);
	pthread_mutex_unlock(&philo->data.fork[left]);
}

void	he_sleep(t_philosopher *philo)
{
	printf("philo [%d] sleep\n", philo->id_philo);
	usleep(1000000);
	printf("philo [%d] thinking\n", philo->id_philo);
}

void	*func1(void *arg)
{
	t_philosopher *philo;
	//t_data data;

	philo = (t_philosopher *)arg;
	while(1)
	{
		eat(philo);
		he_sleep(philo);
	}
	return (NULL);
}

void	start_process(int nb_philo, int ac, char **av)
{
	t_philosopher philo[nb_philo];
	int i;

	i = 0;
	init_philo(philo, nb_philo, av, ac);
	//printf("mutex[0] = %p\n", &mutex[0]);
	//init_mutex(mutex, philo);
	//philo->data.fork = &mutex[0];
	//printf("mutex[0] = %p\n", &mutex[0]);
	//printf("philo[0].mutex[0] = %p\n", &philo[1].data.fork[0]);
	while (i < nb_philo)
	{
		pthread_create(&philo[1].thread, NULL, func1, &philo[i]);
		i++;
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
