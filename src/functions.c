/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:14:46 by jakoh             #+#    #+#             */
/*   Updated: 2022/07/26 13:20:09 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// av takes at least 4 args number 5 is optional
// (nop) number_of_philosophers
// (ttd) time_to_die (in milliseconds)
// (tte) time_to_eat (in milliseconds)
// (tts) time_to_sleep (in milliseconds)
// (me) number_of_times_each_philosopher_must_eat "OPTIONAL"

// int usleep(useconds_t usec); functions accepts time in microseconds