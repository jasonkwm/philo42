/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:42:15 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/04 14:03:12 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_uneating(t_philo *philo);
void	ft_try_eat(t_philo *philo, int phil);

void	ft_try_eat(t_philo *philo, int phnum)
{
	pthread_mutex_lock(&(philo->base->locks[1]));
	if (philo->base->states[phnum] == 0 &&
		philo->base->states[phnum] != 1 &&
		philo->base->states[((phnum + 1) % (philo->base->nop))] != 1)
	{
		pthread_mutex_lock(&(philo->base->locks[3]));
		philo->base->states[phnum] = 1;
		printf("%s%ld philo %i is eating.%s\n", RED, get_time(), phnum, NC);
		pthread_mutex_unlock(&(philo->base->locks[3]));
	}
	pthread_mutex_unlock(&(philo->base->locks[1]));
	if (philo->base->states[phnum] == 1)
		usleep(philo->base->eat);
}

void	ft_uneating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->base->locks[2]));
	if (philo->base->states[philo->name] == 1)
	{
		pthread_mutex_lock(&(philo->base->locks[4]));
		philo->base->states[philo->name] = 2;
		printf("%s%ld philo %i is sleeping.%s\n", BLUE, get_time(), philo->name, NC);
		pthread_mutex_unlock(&(philo->base->locks[4]));
	}
	pthread_mutex_unlock(&(philo->base->locks[2]));
	if (philo->base->states[philo->name] == 1)
		usleep(philo->base->sleep);
}

void	ft_eating(t_philo *philo)
{
	
	if (philo->name % 2 == 1 )
	{
		check_fork(philo, philo->base->to_die, philo->right);
		change_state(philo, philo->right, 1);
		pthread_mutex_lock(&(philo->base->locks[philo->right]));
	}
	else if (philo->name % 2 == 0 )
	{
		check_fork(philo, philo->base->to_die, philo->left);
		change_state(philo, philo->left, 1);
		pthread_mutex_lock(&(philo->base->locks[philo->left]));
	}
	if (philo->name % 2 == 1)
	{
		check_fork(philo, philo->base->to_die, philo->left);
		pthread_mutex_lock(&(philo->base->locks[philo->left]));
		change_state(philo, philo->left, 1);
		printf_ext(philo, "is eating.", GREEN);
		try_die(philo, philo->base->to_eat);
		change_state(philo, philo->left, 0);
		change_state(philo, philo->right, 0);
		pthread_mutex_unlock(&(philo->base->locks[philo->left]));
		pthread_mutex_unlock(&(philo->base->locks[philo->right]));
	}
	else
	{
		check_fork(philo, philo->base->to_die, philo->right);
		pthread_mutex_lock(&(philo->base->locks[philo->right]));
		change_state(philo, philo->right, 1);
		printf_ext(philo, "is eating.", GREEN);
		try_die(philo, philo->base->to_eat);
		change_state(philo, philo->left, 0);
		change_state(philo, philo->right, 0);
		pthread_mutex_unlock(&(philo->base->locks[philo->right]));
		pthread_mutex_unlock(&(philo->base->locks[philo->left]));
	}
}


void	check_fork(t_philo *philo, time_t time, int state)
{
	time_t cur = get_time() + time;
	time_t loop = get_time();
	while ( loop < cur)
	{
		if (philo->base->states[state] != 1)
			break ;
		if (philo->base->shinda == 1)
			return ;
		usleep_ext(1);
		loop = get_time();
	}
	if (loop > cur)
		change_shinda(philo, 1);
	else
		change_shinda(philo, 0);
}

void	try_die(t_philo *philo, time_t time)
{
	time_t	comp;
	time_t	cur;

	cur = get_time();
	if (philo->base->to_die < time)
		comp = get_time() +  (philo->base->to_die);
	else
		comp = get_time() + (time);
	while (cur < comp)
	{
		if (philo->base->shinda == 1)
			return ;
		usleep_ext(1);
		cur = get_time();
	}
	if (philo->base->to_die < time)
		change_shinda(philo, 1);
	else
		change_shinda(philo, 0);
}
