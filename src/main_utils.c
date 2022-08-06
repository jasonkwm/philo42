/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:25:11 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/06 11:04:30 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Need a function to check if fork is available or not
void    check_fork(t_philo *philo)
{
    time_t  cur;
    int     fork;

    cur = get_time();
    if (philo->name % 2 == 1)
        fork = philo->right;
    else
        fork = philo->left;
    pthread_mutex_lock(&(philo->base->base_lock));
	philo->to_check = philo->base->forks[fork];
	pthread_mutex_unlock(&(philo->base->base_lock));
    while (philo->to_check == 1)
    {
        usleep_ext(10);
        cur = get_time();
        pthread_mutex_lock(&(philo->base->base_lock));
        if (cur > philo->death_timer)
        {
            philo->base->shinda = 1;
		    philo->to_check = philo->base->forks[fork];
			pthread_mutex_unlock(&(philo->base->base_lock));
            // printf_ext(philo, "is dead", RED);
            break;
        }
		philo->to_check = philo->base->forks[fork];
		pthread_mutex_unlock(&(philo->base->base_lock));
    }
}

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
        usleep_ext(10);
        cur = get_time();
    }
}

// need a mini function or if statement to check if philo should die or not

