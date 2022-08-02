/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:42:15 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/02 10:42:29 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_try_eat(t_philo *philo, int phnum)
{
	pthread_mutex_lock(&(philo->base->locks[1]));
	if (philo->base->states[phnum] == 0 &&
		philo->base->states[phnum] != 1 &&
		philo->base->states[((phnum + 1) % (philo->base->nop))] != 1)
	{
		pthread_mutex_lock(&(philo->base->locks[3]));
		philo->base->states[phnum] = 1;
		printf("%s%ld philo %i is eating.%s\n", RED, get_time(), phnum, NC);
		pthread_mutex_unlock(&(philo->base->locks[3]));
	}
	pthread_mutex_unlock(&(philo->base->locks[1]));
	if (philo->base->states[phnum] == 1)
		usleep(philo->base->eat);
}

void	ft_uneating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->base->locks[2]));
	if (philo->base->states[philo->name] == 1)
	{
		pthread_mutex_lock(&(philo->base->locks[4]));
		philo->base->states[philo->name] = 2;
		printf("%s%ld philo %i is sleeping.%s\n", BLUE, get_time(), philo->name, NC);
		pthread_mutex_unlock(&(philo->base->locks[4]));
	}
	pthread_mutex_unlock(&(philo->base->locks[2]));
	if (philo->base->states[philo->name] == 1)
		usleep(philo->base->sleep);
}