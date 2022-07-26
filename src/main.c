/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/07/26 13:57:34 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_phil(int ac, char **av, t_philo *philly);
void	ft_err(int i);

int main(int ac, char **av)
{
	t_philo philly;
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (1);
	}
	ft_init_phil(ac, av, &philly);
	printf("nop: %d, think: %u, eat: %u, sleep: %u, must_eat: %d\n",
			philly.nop, philly.think, philly.eat, philly.sleep, philly.must_eat);
}

// av takes at least 4 args number 5 is optional
// (nop) number_of_philosophers
// (ttd) time_to_die (in milliseconds)
// (tte) time_to_eat (in milliseconds)
// (tts) time_to_sleep (in milliseconds)
// (me) number_of_times_each_philosopher_must_eat "OPTIONAL"
void	ft_init_phil(int ac, char **av, t_philo *philly)
{
	philly->nop = ft_atoi(av[1]);
	philly->state = ft_calloc(philly->nop, sizeof(int));
	philly->think = (useconds_t)ft_atoi(av[2]);
	philly->eat = (useconds_t)ft_atoi(av[3]);
	philly->sleep = (useconds_t)ft_atoi(av[4]);
	if (ac == 6)
		philly->must_eat = ft_atoi(av[5]);
}