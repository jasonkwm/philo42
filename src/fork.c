/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:09:49 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/11 19:02:31 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_fork(t_philo *philo, int fork)
{
	time_t	cur;

	while (1)
	{
		cur = get_time();
		if (check_death(philo))
			return (3);
		if (philo->death_timer <= cur)
		{
			change_states(philo, DIE);
			print_death(philo, "died", RED);
			return (2);
		}
		pthread_mutex_lock(&(philo->base->fork_lock));
		if (philo->base->fork_status[fork] == 0)
		{
			philo->base->fork_status[fork] = 1;
			pthread_mutex_unlock(&(philo->base->fork_lock));
			pick_fork(philo, fork);
			return (1);
		}
		pthread_mutex_unlock(&(philo->base->fork_lock));
		usleep(50);
	}
	return (0);
}

void	pick_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&(philo->base->forks[fork]));
	printf_ext(philo, "has taken a fork", YELLOW);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->base->forks[philo->left]));
	pthread_mutex_unlock(&(philo->base->forks[philo->right]));
	pthread_mutex_lock(&(philo->base->fork_lock));
	philo->base->fork_status[philo->left] = 0;
	philo->base->fork_status[philo->right] = 0;
	pthread_mutex_unlock(&(philo->base->fork_lock));
}

int	fork_assist(t_philo *philo, int fork_1, int fork_2)
{
	if (check_fork(philo, fork_1) != 1)
	{
		unlock_forks(philo);
		return (1);
	}
	if (check_fork(philo, fork_2) != 1)
	{
		unlock_forks(philo);
		return (1);
	}
	return (0);
}
