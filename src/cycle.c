/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:38 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/12 16:49:09 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Runs thinking, eating and sleeping process..
int	if_cycle(t_philo *philo)
{
	if (thinking(philo))
		return (1);
	if (eating(philo))
		return (1);
	if (sleeping(philo))
		return (1);
	return (0);
}

// if its the first round i would set death_timer.
// else print thinking & check if fork is available 
// if even number of philo check right fork first then left
// if odd number check opposite. 
int	thinking(t_philo *philo)
{
	if (philo->death_timer == 0)
		philo->death_timer = get_time() + philo->base->to_die;
	change_states(philo, THINK);
	printf_ext(philo, "is thinking", PURPLE);
	if (philo->name % 2 == 0)
		fork_assist(philo, philo->right, philo->left);
	else
		fork_assist(philo, philo->left, philo->right);
	if (count_death(philo))
		return (1);
	return (0);
}

// this function runs after both forks have been picked up by philo
int	eating(t_philo *philo)
{
	change_states(philo, EAT);
	printf_ext(philo, "is eating", GREEN);
	philo->death_timer = get_time() + philo->base->to_die;
	if (usleep_ext(philo, philo->base->to_eat) == 2 || count_death(philo))
	{
		unlock_forks(philo);
		return (1);
	}
	philo->eaten += 1;
	unlock_forks(philo);
	return (0);
}

// sleep after eat
int	sleeping(t_philo *philo)
{
	change_states(philo, SLEEP);
	printf_ext(philo, "is sleeping", BLUE);
	if (usleep_ext(philo, philo->base->to_sleep) == 2 || count_death(philo))
		return (1);
	return (0);
}
