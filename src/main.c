/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/05 15:07:18 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_create(void *arg);
int		ft_thinking(t_philo *philo);
int		ft_eating(t_philo *philo);
int		ft_sleep(t_philo *philo);
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
	printf("Shitda!\n");
}

void	*ft_create(void *arg)
{
	t_philo	*philo;
	int		i;
	philo = (t_philo *)arg;
	i = -1;
	while (++i < 3)
	{
		ft_thinking(philo);
		ft_eating(philo);
		ft_sleep(philo);
	}
	return (arg);
}

int	ft_thinking(t_philo *philo)
{
	if (philo->eaten == 0)
		philo->death_timer = get_time() + philo->base->to_die;
	printf_ext(philo, "is thinking", YELLOW);
	return 0;
}

int	ft_eating(t_philo *philo)
{
	check_fork(philo);
	// if odd philo take right fork first
	// if even philo take left fork first
	if (philo->name % 2 == 1)
	{
		pthread_mutex_lock(&(philo->base->locks[philo->right]));
		// need to new mutex to modify forks
		pthread_mutex_lock(&(philo->base->base_lock));
		philo->base->forks[philo->right] = 1;
		pthread_mutex_unlock(&(philo->base->base_lock));
		printf_ext(philo, "has taken a fork", GREEN);
	}
	else
	{
		pthread_mutex_lock(&(philo->base->locks[philo->left]));
		// need to new mutex to modify forks
		pthread_mutex_lock(&(philo->base->base_lock));
		philo->base->forks[philo->left] = 1;
		pthread_mutex_unlock(&(philo->base->base_lock));
		printf_ext(philo, "has taken a fork", GREEN);
	}

	if (philo->name % 2 == 1)
	{
		pthread_mutex_lock(&(philo->base->locks[philo->left]));
		pthread_mutex_lock(&(philo->base->base_lock));
		philo->base->forks[philo->left] = 1;
		pthread_mutex_unlock(&(philo->base->base_lock));
		printf_ext(philo, "has taken a fork", GREEN);
		printf_ext(philo, "is eating", GREEN);
		philo->death_timer = get_time() + philo->base->to_die;
		check_death(philo, philo->death_timer);
		pthread_mutex_lock(&(philo->base->base_lock));
		philo->base->forks[philo->left] = 0;
		philo->base->forks[philo->right] = 0;
		pthread_mutex_unlock(&(philo->base->base_lock));
		philo->eaten += 1;
		pthread_mutex_unlock(&(philo->base->locks[philo->left]));
		pthread_mutex_unlock(&(philo->base->locks[philo->right]));
	}
	else
	{
		pthread_mutex_lock(&(philo->base->locks[philo->right]));
		pthread_mutex_lock(&(philo->base->base_lock));
		philo->base->forks[philo->right] = 1;
		pthread_mutex_unlock(&(philo->base->base_lock));
		printf_ext(philo, "has taken a fork", GREEN);
		printf_ext(philo, "is eating", GREEN);
		philo->death_timer = get_time() + philo->base->to_die;
		check_death(philo, philo->death_timer);
		pthread_mutex_lock(&(philo->base->base_lock));
		philo->base->forks[philo->left] = 0;
		philo->base->forks[philo->right] = 0;
		pthread_mutex_unlock(&(philo->base->base_lock));
		philo->eaten += 1;
		pthread_mutex_unlock(&(philo->base->locks[philo->right]));
		pthread_mutex_unlock(&(philo->base->locks[philo->left]));
	}
	return 0;
}

int	ft_sleep(t_philo *philo)
{
	printf_ext(philo, "is sleeping", BLUE);
	check_death(philo, philo->base->to_sleep);
	return 0;
}
