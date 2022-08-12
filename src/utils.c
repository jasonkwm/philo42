/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:51:16 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/12 16:52:47 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Output order should look like "time" "name" "message" 
// Messages include
// "has taken a fork", "is eating", "is sleeping", "is thinking", "died"
// only print if there is no dead philo
void	printf_ext(t_philo *philo, char *msg, char *color)
{
	if (count_death(philo) == 0)
	{
		pthread_mutex_lock(&(philo->base->print_lock));
		printf("%s%ld %i %s%s\n", color, get_time(), philo->name, msg, NC);
		pthread_mutex_unlock(&(philo->base->print_lock));
	}
}

// print only 1 death incase if there is multiple philo dying simultaneously
void	print_death(t_philo *philo, char *msg, char *color)
{
	pthread_mutex_lock(&(philo->base->print_lock));
	if (count_death(philo) == 1)
		printf("%s%ld %i %s%s\n", color, get_time(), philo->name, msg, NC);
	pthread_mutex_unlock(&(philo->base->print_lock));
}

// destroy all mutexes & free malloc stuff
void	destructively_free(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->base->nop)
		pthread_mutex_destroy(&(philo->base->forks[i]));
	pthread_mutex_destroy(&(philo->base->fork_lock));
	pthread_mutex_destroy(&(philo->base->print_lock));
	pthread_mutex_destroy(&(philo->base->state_lock));
	free(philo->base->forks);
	free(philo->base->fork_status);
	free(philo->base->states);
	free(philo);
}
