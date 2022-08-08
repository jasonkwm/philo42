/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:25:11 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/08 19:55:34 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// need a mini function or if statement to check if philo should die or not

void	change_states(t_philo *philo, int state)
{
    if (philo->status != DIE)
	{
		pthread_mutex_lock(&(philo->base->base_lock));
		philo->base->states[philo->name] = state;
		pthread_mutex_unlock(&(philo->base->base_lock));	
	}
}

int	check_death(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->base->nop)
	{
        pthread_mutex_lock(&(philo->base->base_lock));
		if(philo->base->states[i] == DIE)
        {
            pthread_mutex_unlock(&(philo->base->base_lock));
			return (1);
        }
        pthread_mutex_unlock(&(philo->base->base_lock));
	}
	return (0);
}


// Need a function to track eating and sleeping time
// void    check_death_tmp(t_philo *philo, int temp)
// {
//     time_t  cur;
//     time_t  comp;

//     cur = get_time();
//     comp = get_time() + temp;
//     while (cur < comp)
//     {
//         pthread_mutex_lock(&(philo->base->base_lock));
//         if (philo->base->shinda == 1)
//         {
//         	pthread_mutex_unlock(&(philo->base->base_lock));
//             break;
//         }
//         pthread_mutex_unlock(&(philo->base->base_lock));
//         usleep_ext(philo, 10);
//         cur = get_time();
//     }
//     if (cur > philo->death_timer)
//     {
// 		pthread_mutex_lock(&(philo->base->base_lock));
// 		philo->base->shinda = 1;
// 		pthread_mutex_unlock(&(philo->base->base_lock));
//     }
// }
