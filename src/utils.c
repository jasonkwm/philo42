/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:51:16 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/04 18:09:14 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// help increase accuracy of usleep function
void	usleep_ext(useconds_t time)
{
	useconds_t	i;

	time *= 1000;
	i = 0;
	while (i < time)
	{
		usleep(20);
		i += 20;
	}
}

// Output order should look like "time" "name" "message" 
// Messages include
// "has taken a fork", "is eating", "is sleeping", "is thinking", "died"
void	printf_ext(t_philo *philo, char *msg, char *color)
{
	printf("%s%ld %i %s%s\n", color, get_time(), philo->name, msg, NC);
}
