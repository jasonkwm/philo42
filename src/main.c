/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:32:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/08 17:43:09 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_create(void *arg);
void	ft_thinking(t_philo *philo);
void	ft_eating(t_philo *philo);
void	ft_sleep(t_philo *philo);
// 0 = thinking, 1 = eating, 2 = sleeping
int main(int ac, char **av)
{
	t_philo	*philos;
	t_base	base;
	int		i;

	if (ac < 5 || ac > 6)
		return (1 | printf("Wrong number of arguments\n"));
	ft_init(av, &philos, &base);
	i = -1;
	while (++i < base.nop)
		pthread_create(&(philos[i].th), NULL, &ft_create, (void *)&(philos[i]));
	i = -1;
	while (++i < base.nop)
	{
		pthread_join(philos[i].th, NULL);
		pthread_mutex_destroy(&(base.forks[i]));
	}
	printf("End.\n");
}

void	*ft_create(void *arg)
{
	t_philo	*philo;
	int		i;
	philo = (t_philo *)arg;
	i = -1;
	while (1)
	{
		ft_thinking(philo);
		ft_eating(philo);
		if (check_death(philo))
			return (arg);
		ft_sleep(philo);
		if (check_death(philo))
			return (arg);
	}
	return (arg);
}

void	ft_thinking(t_philo *philo)
{
	if (philo->death_timer == 0)
		philo->death_timer = get_time() + philo->base->to_die;
	change_states(philo, THINK);
	printf_ext(philo, "is thinking", PURPLE);
	// usleep_ext(philo, philo->base->to_die);
}


// if even philo take right fork first
// if odd philo take left fork first
void	ft_eating(t_philo *philo)
{
	// change_states(philo, THINK);
	// printf_ext(philo, "is thinking", PURPLE);
	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(&(philo->base->forks[philo->right]));
		printf_ext(philo, "has taken a fork", YELLOW);
		
		pthread_mutex_lock(&(philo->base->forks[philo->left]));
		printf_ext(philo, "has taken a fork", YELLOW);
		printf_ext(philo, "is eating", GREEN);
		change_states(philo, EAT);

		philo->death_timer = get_time() + philo->base->to_die;
		
		usleep_ext(philo, philo->base->to_eat);

		pthread_mutex_unlock(&(philo->base->forks[philo->left]));
		pthread_mutex_unlock(&(philo->base->forks[philo->right]));
		philo->eaten += 1;
	}
	else
	{
		pthread_mutex_lock(&(philo->base->forks[philo->left]));
		printf_ext(philo, "has taken a fork", YELLOW);
		
		pthread_mutex_lock(&(philo->base->forks[philo->right]));
		printf_ext(philo, "has taken a fork", YELLOW);
		printf_ext(philo, "is eating", GREEN);
		change_states(philo, EAT);
		
		philo->death_timer = get_time() + philo->base->to_die;

		usleep_ext(philo, philo->base->to_eat);

		pthread_mutex_unlock(&(philo->base->forks[philo->right]));
		pthread_mutex_unlock(&(philo->base->forks[philo->left]));
		philo->eaten += 1;
	}
}

void	ft_sleep(t_philo *philo)
{
	change_states(philo, SLEEP);
	printf_ext(philo, "is sleeping", BLUE);
	usleep_ext(philo, philo->base->to_sleep);
}
