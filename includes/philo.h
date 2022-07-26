/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:34 by jakoh             #+#    #+#             */
/*   Updated: 2022/07/26 16:07:42 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include "libft.h"


enum e_states{eating, thinking, sleeping};

typedef struct s_philo
{
	int			nop;
	useconds_t	think;
	useconds_t	eat;
	useconds_t	sleep;
	int			must_eat;
}	t_philo;

typedef struct s_philly
{
	pthread_t td;
	enum	e_states state;
}	t_philly;
#endif