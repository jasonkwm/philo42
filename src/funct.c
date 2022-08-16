/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:01:31 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/16 13:04:24 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// converts ascii to integer
// from libft
// skips spaces
// check for 1 + or -
// then loop through the rest till there is no digit found
int	ft_atoi(const char *str)
{
	int	i;
	int	ans;
	int	neg;

	neg = 1;
	ans = 0;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		++i;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			neg = -1;
	while (str[i] >= '0' && str[i] <= '9')
		ans = (ans * 10) + (str[i++] - '0');
	return (ans * neg);
}

// return 1 if found non digit in string
// return 0 if only digit in string
int	ft_isnum(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

// check for input errors
// - number of arguments
// - if number of philo is more than 200
// - input contains only number
// returns 1 if error found
// returns 0 if no error
int	ft_check_input(int ac, char **av)
{
	int	i;

	i = 0;
	if ((ac < 5 || ac > 6) || ft_atoi(av[1]) > 200)
		return (1);
	while (++i < ac)
		if (ft_isnum(av[i]))
			return (1);
	return (0);
}
