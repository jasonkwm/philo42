/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:25:11 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/08 13:45:30 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Need a function to track eating and sleeping time
void    check_death(t_philo *philo, int temp)
{
    time_t  cur;
    time_t  comp;

    cur = get_time();
    comp = get_time() + temp;
    while (cur < comp)
    {
        pthread_mutex_lock(&(philo->base->base_lock));
        if (philo->base->shinda == 1)
        {
        	pthread_mutex_unlock(&(philo->base->base_lock));
            printf_ext(philo, "is dead", RED);
            break;
        }
        pthread_mutex_unlock(&(philo->base->base_lock));
        usleep_ext(philo, 10);
        cur = get_time();
    }
    if (cur > philo->death_timer)
    {
     pthread_mutex_lock(&(philo->base->base_lock));
     philo->base->shinda = 1;
	 pthread_mutex_unlock(&(philo->base->base_lock));
    }
}

// need a mini function or if statement to check if philo should die or not

