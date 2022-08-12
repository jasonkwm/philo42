/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:25:11 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/12 16:54:02 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// get and conver time to microseconds
time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((time_t)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

// help increase accuracy of usleep function
int	usleep_ext(t_philo *philo, time_t time)
{
	time_t	cur;
	time_t	cmp;

	cmp = get_time() + time;
	while (1)
	{
		cur = get_time();
		if (cmp - cur <= 0)
			return (1);
		if (count_death(philo))
			return (1);
		if (philo->death_timer <= cur)
		{
			change_states(philo, DIE);
			print_death(philo, "died", RED);
			return (2);
		}
		usleep(50);
	}
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

// // loop through each philo state and check if any is dead
// // if philo dead return 1
// // return 0 if no philo die
// // replaced with count death since it gives more info
// // int	check_death(t_philo *philo)
// {
// 	int	i;

// 	pthread_mutex_lock(&(philo->base->state_lock));
// 	i = -1;
// 	while (++i < philo->base->nop)
// 	{
// 		if (philo->base->states[i] == DIE)
// 		{
// 			pthread_mutex_unlock(&(philo->base->state_lock));
// 			return (1);
// 		}
// 	}
// 	pthread_mutex_unlock(&(philo->base->state_lock));
// 	return (0);
// }
