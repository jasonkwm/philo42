/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:28:44 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/04 16:22:27 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(char **av, t_philo **philos, t_base *base)
{
	// ft_check_input(ac, av);
	ft_init_base(av, base);
	ft_init_philos(philos, base);
}

// void	ft_check_input(int ac, char **av)
// {
// 	//do something
// }

// av takes at least 4 args number 5 is optional
// (nop) number_of_philosophers
// (ttd) time_to_die (in milliseconds)
// (tte) time_to_eat (in milliseconds)
// (tts) time_to_sleep (in milliseconds)
// (me) number_of_times_each_philosopher_must_eat "OPTIONAL"
void	ft_init_base(char **av, t_base *base)
{
	int	i;

	base->nop = ft_atoi(av[1]);
	base->to_die = (useconds_t)(ft_atoi(av[2]));
	base->to_eat = (useconds_t)(ft_atoi(av[3]));
	base->to_sleep = (useconds_t)(ft_atoi(av[4]));
	base->shinda = 0;
	if (av[5])
		base->must_eat = ft_atoi(av[5]);
	base->forks = malloc(sizeof(int) * base->nop);
	base->locks = malloc(sizeof(pthread_mutex_t) * base->nop);
	i = -1;
	while (++i < base->nop)
	{
		(base->forks)[i] = 0;
		pthread_mutex_init(&(base->locks[i]), NULL);
		if (i < 10)
			pthread_mutex_init(&(base->temp_locks[i]), NULL);
	}
}

void	ft_init_philos(t_philo **philos, t_base *base)
{
	int	i;

	i = -1;
	*philos = malloc(sizeof(t_philo) * base->nop);
	while (++i < base->nop)
	{
		(*philos)[i].name = i;
		(*philos)[i].left = i;
		(*philos)[i].right = ((i + 1) % (base->nop));
		(*philos)[i].base = base;
	}
}