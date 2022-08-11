/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:51:16 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/11 16:08:09 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (time_t)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
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
		if (check_death(philo))
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

// Output order should look like "time" "name" "message" 
// Messages include
// "has taken a fork", "is eating", "is sleeping", "is thinking", "died"
void	printf_ext(t_philo *philo, char *msg, char *color)
{
	if (check_death(philo) == 0)
	{
		pthread_mutex_lock(&(philo->base->print_lock));
		printf("%s%ld %i %s%s\n", color, get_time(), philo->name, msg, NC);
		pthread_mutex_unlock(&(philo->base->print_lock));
	}
	// if (check_death(philo) == 0)
	// 	pthread_mutex_lock(&(philo->base->print_lock));
	// 		printf("%s%ld %i %s%s\n", color, get_time(), philo->name, msg, NC);
	// 	pthread_mutex_unlock(&(philo->base->print_lock));
}

void	print_death(t_philo *philo, char *msg, char *color)
{
	pthread_mutex_lock(&(philo->base->print_lock));
	if (count_death(philo) == 1)
		printf("%s%ld %i %s%s\n", color, get_time(), philo->name, msg, NC);
	pthread_mutex_unlock(&(philo->base->print_lock));
}