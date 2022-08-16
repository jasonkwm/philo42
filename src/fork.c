/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:09:49 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/16 14:12:16 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check if fork is available to be picked up
// this function is called during thinking stage
// if philo did not picked up both fork before death timer
// then philo die and return 2
// if there is a dead philo function returns 3
// if successful function returns 1
int	check_fork(t_philo *philo, int fork)
{
	time_t	cur;

	while (1)
	{
		cur = get_time();
		if (count_death(philo))
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
		usleep(100);
	}
	return (0);
}

// pick fork function
// mutex fork & print text to stdout
void	pick_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&(philo->base->forks[fork]));
	printf_ext(philo, "has taken a fork", YELLOW);
}

// unlocks all forks and change fork status
// used after philo has finish eating & philo did not die
void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->base->forks[philo->left]));
	pthread_mutex_unlock(&(philo->base->forks[philo->right]));
	pthread_mutex_lock(&(philo->base->fork_lock));
	philo->base->fork_status[philo->left] = 0;
	philo->base->fork_status[philo->right] = 0;
	pthread_mutex_unlock(&(philo->base->fork_lock));
}

// calls check_fork function and if fail to pick up fork
// unlock_forks function is called and function returns 1
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
