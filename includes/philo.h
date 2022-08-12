/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:34 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/12 16:53:51 by jakoh            ###   ########.fr       */
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

# define THINK 0
# define EAT 1
# define SLEEP 2
# define DIE 3

struct s_philo;

typedef struct s_base
{
	int				nop;
	time_t			to_die;
	time_t			to_eat;
	time_t			to_sleep;
	int				must_eat;
	int				*states;
	int				*fork_status;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	fork_lock;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	print_lock;
}	t_base;

typedef struct s_philo
{
	pthread_t 		th;
	int				name;
	int				left;
	int				right;
	time_t			death_timer;
	int				eaten;
	t_base			*base;
}	t_philo;

// init.c
void	ft_init(char **av, t_philo **philo, t_base *base);
void	ft_init_base(char **av, t_base *base);
void	ft_init_philos(t_philo **philos, t_base *base);

// ft_atoi.c
int		ft_atoi(const char *str);
int		ft_isnum(char *str);
int		ft_check_input(int ac, char **av);

// utils.c

void	destructively_free(t_philo *philo);

void	printf_ext(t_philo *philo, char *msg, char *color);
void	print_death(t_philo *philo, char *msg, char *color);

// main_utils.c
time_t	get_time();
int		usleep_ext(t_philo *philo, time_t time);
int		change_states(t_philo *philo, int state);
int		count_death(t_philo *philo);

// fork.c
void	unlock_forks(t_philo *philo);
void	pick_fork(t_philo *philo, int fork);
int		check_fork(t_philo *philo, int fork);
int		fork_assist(t_philo *philo, int fork_1, int fork_2);

// cycle.c
int		if_cycle(t_philo *philo);
int		thinking(t_philo *philo);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);
#endif