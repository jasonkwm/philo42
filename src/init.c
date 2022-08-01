/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:28:44 by jakoh             #+#    #+#             */
/*   Updated: 2022/07/28 11:01:01 by jakoh            ###   ########.fr       */
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
	base->think = (useconds_t)(ft_atoi(av[2]) * 1000);
	base->eat = (useconds_t)(ft_atoi(av[3]) * 1000);
	base->sleep = (useconds_t)(ft_atoi(av[4]) * 1000);
	if (av[5])
		base->must_eat = ft_atoi(av[5]);
	base->forks = malloc(sizeof(int) * base->nop);
	base->states = malloc(sizeof(int) * base->nop);
	i = -1;
	while (++i < base->nop)
	{
		(base->forks)[i] = 0;
		(base->states)[i] = 0;
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
		(*philos)[i].base = base;
		if (i == base->nop - 1)
			(*philos)[i].right = 0;
		else
			(*philos)[i].right = i + 1;
	}
}