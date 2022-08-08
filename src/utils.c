/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:51:16 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/08 15:30:52 by jakoh            ###   ########.fr       */
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
void	usleep_ext(t_philo *philo, time_t time)
{
	time_t	cur;
	time_t	cmp;

	
	(void)philo;
	cmp = get_time() + time;
	while (philo->base->shinda != 1)
	{
		cur = get_time();
		if (cmp - cur <= 0)
			break ;
		usleep(50);
	}
}

// Output order should look like "time" "name" "message" 
// Messages include
// "has taken a fork", "is eating", "is sleeping", "is thinking", "died"
void	printf_ext(t_philo *philo, char *msg, char *color)
{
	pthread_mutex_lock(&(philo->base->print_lock));
	printf("%s%ld %i %s%s\n", color, get_time(), philo->name, msg, NC);
	pthread_mutex_unlock(&(philo->base->print_lock));
}
