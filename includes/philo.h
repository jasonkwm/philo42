/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:34 by jakoh             #+#    #+#             */
/*   Updated: 2022/07/28 11:01:12 by jakoh            ###   ########.fr       */
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

enum e_states{eating, thinking, sleeping};

typedef struct s_base
{
	int			nop;
	useconds_t	think;
	useconds_t	eat;
	useconds_t	sleep;
	int			must_eat;
	int			*forks;
}	t_base;

typedef struct s_philo
{
	pthread_t th;
	int		name;
	enum	e_states state;
	int		left;
	int		right;
	t_base	*base;
}	t_philo;

void	ft_init(char **av, t_philo **philo, t_base *base);
void	ft_init_base(char **av, t_base *base);
void	ft_init_philos(t_philo **philos, t_base *base);
int		ft_atoi(const char *str);

#endif