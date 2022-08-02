/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/02 11:03:48 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_create(void *arg);
void	ft_thinking(t_philo *philo);
void	ft_eating(t_philo *philo);
void	ft_uneating(t_philo *philo);
void	ft_try_eat(t_philo *philo, int phil);
void	ft_sleep(t_philo *philo);
void	change_state(t_philo *philo,  int phnum, int state);

// 0 = thinking, 1 = eating, 2 = sleeping
int main(int ac, char **av)
{
	t_philo	*philos;
	t_base	base;
	int		i;

	if (ac < 5 || ac > 6)
		return (1 | printf("Wrong number of arguments\n"));
	ft_init(av, &philos, &base);
	i = -1;
	while (++i < base.nop)
		pthread_create(&(philos[i].th), NULL, &ft_create, (void *)&(philos[i]));
	i = -1;
	while (++i < base.nop)
	{
		pthread_join(philos[i].th, NULL);
		pthread_mutex_destroy(&(base.locks[i]));
	}
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
		
		ft_sleep(&philo);
	}
	return (arg);
}

void	ft_thinking(t_philo *philo)
{
	change_state(philo, philo->name, 0);
	printf("%s%ld philo %i is thinking.%s\n", GREEN, get_time(), philo->name, NC);
	// usleep(philo->base->think);
}

void	ft_eating(t_philo *philo)
{
	if (philo->name % 2 == 1 && philo->base->states[philo->left] != 1)
	{
			pthread_mutex_lock(&(philo->base->locks[philo->right]));
			change_state(philo, philo->right, 1);
	}
	else if (philo->name % 2 == 0 && philo->base->states[philo->right] != 1)
	{
			pthread_mutex_lock(&(philo->base->locks[philo->left]));
			change_state(philo, philo->left, 1);
	}
	if (philo->name % 2 == 1)
	{
		pthread_mutex_lock(&(philo->base->locks[philo->left]));
		change_state(philo, philo->left, 1);
		printf("%s%ld philo %i is eating.%s\n", RED, get_time(), philo->name, NC);
		usleep(philo->base->eat);
		pthread_mutex_unlock(&(philo->base->locks[philo->right]));
		pthread_mutex_unlock(&(philo->base->locks[philo->left]));
	}
	else
	{
		pthread_mutex_lock(&(philo->base->locks[philo->right]));
		change_state(philo, philo->right, 1);
		printf("%s%ld philo %i is eating.%s\n", RED, get_time(), philo->name, NC);
		usleep(philo->base->eat);
		pthread_mutex_unlock(&(philo->base->locks[philo->left]));
		pthread_mutex_unlock(&(philo->base->locks[philo->right]));
	}
}

void	ft_sleep(t_philo *philo)
{
	change_state(philo, philo->name, 2);
	printf("%s%ld philo %i is sleeping.%s\n", BLUE, get_time(), philo->name, NC);
	usleep(philo->base->sleep);
}

void	change_state(t_philo *philo,  int phnum, int state)
{
	pthread_mutex_lock(&(philo->base->big_lock));
	philo->base->states[phnum] = state;
	pthread_mutex_unlock(&(philo->base->big_lock));
}
