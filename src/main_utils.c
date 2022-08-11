/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:25:11 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/11 19:07:50 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// loop through each philo state and check if any is dead
// if philo dead return 1
// return 0 if no philo die
int	check_death(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&(philo->base->state_lock));
	i = -1;
	while (++i < philo->base->nop)
	{
		if (philo->base->states[i] == DIE)
		{
			pthread_mutex_unlock(&(philo->base->state_lock));
			return (1);
		}
	}
	pthread_mutex_unlock(&(philo->base->state_lock));
	return (0);
}

// First the program will check if there is any dead philo
// if there is a dead philo it will not change state and just return 0
// returns 1 for successful state change
int	change_states(t_philo *philo, int state)
{
	if (count_death(philo) == 0)
	{
		pthread_mutex_lock(&(philo->base->state_lock));
		philo->base->states[philo->name] = state;
		pthread_mutex_unlock(&(philo->base->state_lock));
	}
	return (1);
}

// count number of dead philo
int	count_death(t_philo *philo)
{
	int	i;
	int	c;

	c = 0;
	i = -1;
	pthread_mutex_lock(&(philo->base->state_lock));
	while (++i < philo->base->nop)
	{
		if (philo->base->states[i] == DIE)
			c++;
	}
	pthread_mutex_unlock(&(philo->base->state_lock));
	return (c);
}
