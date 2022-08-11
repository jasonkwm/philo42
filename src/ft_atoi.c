/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:01:31 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/11 19:09:43 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
