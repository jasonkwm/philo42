/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:35:58 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/10 13:37:55 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_thinking(t_philo *philo)
{
	if (philo->death_timer == 0)
		philo->death_timer = get_time() + philo->base->to_die;
	change_states(philo, THINK);
	printf_ext(philo, "is thinking", PURPLE);
	if (philo->name % 2 == 0)
	{
		limbo(philo, philo->right);
		if (check_death(philo))
			return ;
		limbo(philo, philo->left);
		if (check_death(philo))
			return ;
	}
	else
	{
		limbo(philo, philo->left);
		if (check_death(philo))
			return ;
		limbo(philo, philo->right);
		if (check_death(philo))
			return ;
	}
	// usleep_ext(philo, philo->base->to_die);
}


// if even philo take right fork first
// if odd philo take left fork first
void	ft_eating(t_philo *philo)
{
	if (philo->name % 2 == 0)
	{
		printf_ext(philo, "is eating", GREEN);
		change_states(philo, EAT);
		philo->death_timer = get_time() + philo->base->to_die;
		usleep_ext(philo, philo->base->to_eat);
		philo->eaten += 1;
		pthread_mutex_unlock(&(philo->base->forks[philo->left]));
		pthread_mutex_unlock(&(philo->base->forks[philo->right]));
	}
	else
	{
		printf_ext(philo, "is eating", GREEN);
		change_states(philo, EAT);
		philo->death_timer = get_time() + philo->base->to_die;
		usleep_ext(philo, philo->base->to_eat);
		philo->eaten += 1;
		pthread_mutex_unlock(&(philo->base->forks[philo->right]));
		pthread_mutex_unlock(&(philo->base->forks[philo->left]));
	}
}

void	ft_sleep(t_philo *philo)
{
	change_states(philo, SLEEP);
	printf_ext(philo, "is sleeping", BLUE);
	usleep_ext(philo, philo->base->to_sleep);
}

void	pick_fork(t_philo *philo, int name)
{
	pthread_mutex_lock(&(philo->base->forks[name]));
	printf_ext(philo, "has taken a fork", YELLOW);
}

void	limbo(t_philo *philo ,int side)
{
	time_t	cur;

	// printf("philo: %i, eaten: %i, left: %i, right: %i\n")
	while (1)
	{
		cur = get_time();
		if (philo->death_timer <= cur)
		{
			pthread_mutex_unlock(&(philo->base->forks[philo->right]));
			pthread_mutex_unlock(&(philo->base->forks[philo->left]));
			change_states(philo, DIE);
			print_death(philo, "died", RED);
			break ;
		}
		if (philo->base->states[side] != EAT)
		{
			pick_fork(philo, side);
			break ;
		}
		if (check_death(philo))
			break ;
		usleep(50);
	}	
}


void	change_states(t_philo *philo, int state)
{
	int		i;

    pthread_mutex_lock(&(philo->base->base_lock));
	i = -1;
	while (++i < philo->base->nop)
	{
		if(philo->base->states[i] == DIE)
        {
            pthread_mutex_unlock(&(philo->base->base_lock));
			return ;
        }
	}
	philo->base->states[philo->name] = state;
    pthread_mutex_unlock(&(philo->base->base_lock));
}

int	check_death(t_philo *philo)
{
	int		i;

	i = -1;
    pthread_mutex_lock(&(philo->base->base_lock));
	while (++i < philo->base->nop)
	{
		if(philo->base->states[i] == DIE)
        {
            pthread_mutex_unlock(&(philo->base->base_lock));
			return (1);
        }
	}
    pthread_mutex_unlock(&(philo->base->base_lock));
	return (0);
}

int count_death(t_philo *philo)
{
	int		i;
	int		c;

	c = 0;
	i = -1;
    pthread_mutex_lock(&(philo->base->base_lock));
	while (++i < philo->base->nop)
	{
		if(philo->base->states[i] == DIE)
            c++;
	}
    pthread_mutex_unlock(&(philo->base->base_lock));
	return (c);
}
