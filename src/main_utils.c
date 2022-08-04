/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:25:11 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/04 18:36:24 by jakoh            ###   ########.fr       */
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
    while (philo->base->forks[fork] == 1)
    {
        usleep_ext(10);
        cur = get_time();
        if (cur >= philo->death_timer)
        {
            pthread_mutex_lock(&(philo->base->temp_locks[0]));
            philo->base->shinda = 1;
            pthread_mutex_unlock(&(philo->base->temp_locks[0]));
            printf_ext(philo, "is dead", RED);
            break;
        }
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
        if (philo->base->shinda == 1)
        {
            pthread_mutex_lock(&(philo->base->temp_locks[0]));
            philo->base->shinda = 1;
            pthread_mutex_unlock(&(philo->base->temp_locks[0]));
            printf_ext(philo, "is dead", RED);
            break;
        }
        usleep_ext(10);
        cur = get_time();
    }
}

// need a mini function or if statement to check if philo should die or not

