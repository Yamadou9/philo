/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:56:37 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/26 10:23:25 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *nptr)
{
	int	result;
	int	i;
	int	signe;

	signe = 1;
	result = 0;
	i = 0;
	while (nptr[i] == '-')
	{
		signe = signe * -1;
		i++;
	}
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	if (result > INT_MAX || result * signe < 0)
		return (-1);
	return (result * signe);
}
