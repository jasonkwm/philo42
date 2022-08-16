/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/16 13:20:50 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_create(void *arg);

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_base	base;
	int		i;

	if (ft_check_input(ac, av))
		return (1 | printf("Error.\n"));
	ft_init(av, &philos, &base);
	i = -1;
	while (++i < base.nop)
		pthread_create(&(philos[i].th), NULL, &ft_create, (void *)&(philos[i]));
	i = -1;
	while (++i < base.nop)
		pthread_join(philos[i].th, NULL);
	destructively_free(philos);
}

// if must eat is not set then run a infinite while loop
// else run while loop "must_eat" number of times
void	*ft_create(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	if (philo->base->must_eat == 0)
	{
		while (1)
			if (if_cycle(philo))
				return (arg);
	}
	else
	{
		i = -1;
		while (++i < philo->base->must_eat)
			if (if_cycle(philo))
				return (arg);
	}
	return (arg);
}
