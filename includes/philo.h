/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:34 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/05 14:30:33 by jakoh            ###   ########.fr       */
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

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"
# define NC "\033[0m"

enum e_states{thinking, eating, sleeping};

typedef struct s_base
{
	int				nop;
	time_t			to_die;
	time_t			to_eat;
	time_t			to_sleep;
	int				must_eat;
	int				shinda;
	int				*forks;
	pthread_mutex_t	*locks;
	pthread_mutex_t	base_lock;
	pthread_mutex_t	print_lock;
}	t_base;

typedef struct s_philo
{
	pthread_t 		th;
	int				name;
	int				left;
	int				right;
	enum e_states	state;
	useconds_t		death_timer;
	int				eaten;
	int				to_check;
	t_base			*base;
}	t_philo;

// init.c
void	ft_init(char **av, t_philo **philo, t_base *base);
void	ft_init_base(char **av, t_base *base);
void	ft_init_philos(t_philo **philos, t_base *base);

// ft_atoi.c
int		ft_atoi(const char *str);

// utils.c
time_t	get_time();
void	usleep_ext(useconds_t time);
void	printf_ext(t_philo *philo, char *msg, char *color);

// main_utils.c
void    check_fork(t_philo *philo);
void    check_death(t_philo *philo, int temp);

#endif