/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/07/28 15:14:30 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_create(void *arg);
int j = 0;
int main(int ac, char **av)
{
	t_philo	*philos;
	t_base	base;
	if (ac < 5 || ac > 6)
		return (1 | printf("Wrong number of arguments\n"));
	ft_init(av, &philos, &base);
	int i = -1;
	while (++i < base.nop)
		pthread_create(&(philos[i].th), NULL, &ft_create, (void *)&(philos[i]));
	i = -1;
	while (++i < base.nop)
		pthread_join(philos[i].th, NULL);
}

void	*ft_create(void *arg)
{
	t_philo philo;
	pthread_mutex_t mute;
	pthread_mutex_t main_mute;
	philo = *(t_philo *)arg;
	pthread_mutex_init(&main_mute, NULL);
	pthread_mutex_init(&mute, NULL);
	int	i = -1;
	while (++i < 5)
	{
		if (philo.state == thinking)
		{
			printf("%i is thinking.\n", philo.name);
			if (philo.base->forks[philo.left] == 1 && philo.base->forks[philo.right] == 1)
			{
				pthread_mutex_lock(&main_mute);
				philo.base->forks[philo.left] = 0;
				philo.base->forks[philo.right] = 0;
				printf("%i is eating.\n", philo.name);
				usleep(philo.base->eat);
				philo.state = eating;
				pthread_mutex_unlock(&main_mute);
				if (philo.state == eating)
				{
					pthread_mutex_lock(&mute);
					philo.base->forks[philo.left] = 1;
					philo.base->forks[philo.right] = 1;
					philo.state = sleeping;
					printf("%i is sleeping.\n", philo.name);
					usleep(philo.base->sleep);
					pthread_mutex_unlock(&mute);
				}
				philo.state = thinking;
				
			}
		}
	}
	return (arg);
}