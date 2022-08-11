/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/10 18:41:25 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_create(void *arg);
int		thinking(t_philo *philo);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);

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
		if (i == 0)
		{
			pthread_mutex_destroy(&(base.base_lock));
			pthread_mutex_destroy(&(base.print_lock));
			pthread_mutex_destroy(&(base.state_lock));
		}
		pthread_mutex_destroy(&(base.forks[i]));
	}
	printf("End.\n");
}

void	*ft_create(void *arg)
{
	t_philo	*philo;
	int		i;
	philo = (t_philo *)arg;
	i = -1;
	while (1)
	{
		if (thinking(philo))
			return (arg);
		if (eating(philo))
			return (arg);
		if (sleeping(philo))
			return (arg);
	}
	return (arg);
}

int	thinking(t_philo *philo)
{
	if (philo->death_timer == 0)
		philo->death_timer = get_time() + philo->base->to_die;
	change_states(philo, THINK);
	// WAIT FOR FORKS TO BE AVAILABLE
	if (philo->name % 2 == 0)
	{
		if (check_fork(philo, philo->right) == 1)
			pick_fork(philo, philo->right);
		else if (check_fork(philo, philo->left) == 2 || check_fork(philo, philo->left) == 3)
		{
			unlock_forks(philo);
			return (1);
		}
		if (check_fork(philo, philo->left) == 1)
			pick_fork(philo, philo->left);
		else if (check_fork(philo, philo->left) == 2 || check_fork(philo, philo->left) == 3)
		{
			unlock_forks(philo);
			return (1);
		}
	}
	else
	{
		if (check_fork(philo, philo->left) == 1)
			pick_fork(philo, philo->left);
		else if (check_fork(philo, philo->left) == 2 || check_fork(philo, philo->left) == 3)
			return (1);
		if (check_fork(philo, philo->right) == 1)
			pick_fork(philo, philo->right);
		else if (check_fork(philo, philo->left) == 2 || check_fork(philo, philo->left) == 3)
			return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	change_states(philo, EAT);
	printf_ext(philo, "is eating", GREEN);
	philo->death_timer = get_time() + philo->base->to_die;
	if (usleep_ext(philo, philo->base->to_eat) == 2)
	{
		unlock_forks(philo);
		return (1);
	}
	philo->eaten += 1;
	unlock_forks(philo);
	return (0);
}

int	sleeping(t_philo *philo)
{
	change_states(philo, SLEEP);
	printf_ext(philo, "is sleeping", BLUE);
	if (usleep_ext(philo, philo->base->to_sleep) == 2)
		return (1);
	return (0);
}
