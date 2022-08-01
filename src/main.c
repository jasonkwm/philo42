/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/01 10:18:49 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_create(void *arg);
void	ft_thinking(t_philo *philo);
void	ft_eating(t_philo *philo);
void	ft_uneating(t_philo *philo);
void	ft_try_eat(t_philo *philo, int phil);

// 0 = thinking, 1 = eating, 2 = sleeping
int main(int ac, char **av)
{
	t_philo	*philos;
	t_base	base;

	if (ac < 5 || ac > 6)
		return (1 | printf("Wrong number of arguments\n"));
	ft_init(av, &philos, &base);
	int i = -1;
	while (++i < 10)
		pthread_mutex_init(&(base.locks[i]), NULL);
	i = -1;
	while (++i < base.nop)
		pthread_create(&(philos[i].th), NULL, &ft_create, (void *)&(philos[i]));
	i = -1;
	while (++i < base.nop)
		pthread_join(philos[i].th, NULL);
	while (++i < 10)
		pthread_mutex_destroy(&(base.locks[i]));
}

void	*ft_create(void *arg)
{
	t_philo	philo;
	philo = *(t_philo *)arg;
	int	i = -1;
	sleep(1);
	while (++i < 5)
	{
		ft_thinking(&philo);
		
		ft_eating(&philo);
		
		ft_uneating(&philo);
	}
	return (arg);
}

void	ft_thinking(t_philo *philo)
{
	usleep(philo->base->think);
	pthread_mutex_lock(&(philo->base->locks[0]));
	philo->base->states[philo->name] = 0;
	printf("%ld philo %i is thinking.\n", get_time(),philo->name);
	pthread_mutex_unlock(&(philo->base->locks[0]));
}

void	ft_eating(t_philo *philo)
{
	// something was inside here but i removed it
	// stop judging my function calling function 
	// bish!!
	ft_try_eat(philo, philo->name);
}

void	ft_try_eat(t_philo *philo, int phnum)
{
	pthread_mutex_lock(&(philo->base->locks[1]));
	if (philo->base->states[phnum] == 0 &&
		philo->base->states[phnum] != 1 &&
		philo->base->states[((phnum + 1) % (philo->base->nop))] != 1)
	{
		pthread_mutex_lock(&(philo->base->locks[3]));
		philo->base->states[phnum] = 1;
		printf("%ld philo %i is eating.\n", get_time(), phnum);
		pthread_mutex_unlock(&(philo->base->locks[3]));
		usleep(philo->base->eat);
	}
	pthread_mutex_unlock(&(philo->base->locks[1]));
}

void	ft_uneating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->base->locks[2]));
	if (philo->base->states[philo->name] == 1)
	{
		pthread_mutex_lock(&(philo->base->locks[4]));
		philo->base->states[philo->name] = 2;
		printf("%ld philo %i is sleeping.\n", get_time(), philo->name);
		pthread_mutex_unlock(&(philo->base->locks[4]));
		usleep(philo->base->sleep);
	}
	pthread_mutex_unlock(&(philo->base->locks[2]));
	
}
