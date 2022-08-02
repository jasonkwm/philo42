/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/02 15:54:37 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_create(void *arg);
int		ft_thinking(t_philo *philo);
void	ft_eating(t_philo *philo);
void	ft_sleep(t_philo *philo);
int		stop_thinking(t_philo *philo);
void	usleep_plus(useconds_t time);
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
		if (ft_thinking(&philo))
			return (arg);
		
		ft_eating(&philo);
		
		ft_sleep(&philo);
	}
	return (arg);
}

int	ft_thinking(t_philo *philo)
{
	change_state(philo, philo->name, 0);
	printf("%s%ld philo %i is hungry.%s\n", GREEN, get_time(), philo->name, NC);
	if (stop_thinking(philo))
		return (printf("%s%ld philo %i is dead.%s\n", PURPLE, get_time(), philo->name, NC));
	return (0);
}

int	stop_thinking(t_philo *philo)
{
	time_t cur = get_time() + philo->base->think;
	time_t loop = get_time();
	while ( loop < cur)
	{
		if (philo->name % 2 == 1 && philo->base->states[philo->right] != 1)
			return (0);
		else if (philo->name % 2 == 0 && philo->base->states[philo->left] != 1)
			return (0);
		usleep_plus(20);
		loop = get_time();
	}
	return (1);
}

void	ft_eating(t_philo *philo)
{
	if (philo->name % 2 == 1 )
	{
			pthread_mutex_lock(&(philo->base->locks[philo->right]));
			change_state(philo, philo->name, 1);
	}
	else if (philo->name % 2 == 0 )
	{
			pthread_mutex_lock(&(philo->base->locks[philo->left]));
			change_state(philo, philo->name, 1);
	}
	if (philo->name % 2 == 1)
	{
		pthread_mutex_lock(&(philo->base->locks[philo->left]));
		printf("%s%ld philo %i is eating.%s\n", RED, get_time(), philo->name, NC);
		usleep_plus(philo->base->eat);
		pthread_mutex_unlock(&(philo->base->locks[philo->right]));
		pthread_mutex_unlock(&(philo->base->locks[philo->left]));
	}
	else
	{
		pthread_mutex_lock(&(philo->base->locks[philo->right]));
		printf("%s%ld philo %i is eating.%s\n", RED, get_time(), philo->name, NC);
		usleep_plus(philo->base->eat);
		pthread_mutex_unlock(&(philo->base->locks[philo->left]));
		pthread_mutex_unlock(&(philo->base->locks[philo->right]));
	}
}

void	ft_sleep(t_philo *philo)
{
	change_state(philo, philo->name, 2);
	printf("%s%ld philo %i is sleeping.%s\n", BLUE, get_time(), philo->name, NC);
	usleep_plus(philo->base->sleep);
}

void	usleep_plus(useconds_t time)
{
	useconds_t	i;

	time *= 1000;
	i = 0;
	while (i < time)
	{
		usleep(50);
		i += 50;
	}
}