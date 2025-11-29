/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:56:37 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/29 18:01:20 by ydembele         ###   ########.fr       */
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
	if (result > INT_MAX)
		return (-1);
	return (result * signe);
}

int	parse_input(t_table *table, char **av, int ac)
{
	if (!checks(av))
		return (1);
	table->time_eat = ft_atoi(av[3]) * 1e3;
	table->time_sleep = ft_atoi(av[4]) * 1e3;
	table->time_die = ft_atoi(av[2]) * 1e3;
	table->nb_philo = ft_atoi(av[1]);
	if (ac == 6)
		table->nb_limit_eat = ft_atoi(av[5]);
	else
		table->nb_limit_eat = -1;
	if (table->time_eat < 0 || table->time_sleep < 0
		|| table->time_die < 0 || table->nb_philo < 0 || table->nb_philo > 200
		|| (table->nb_limit_eat < 0 && ac == 6))
		return (1);
	table->end = false;
	table->ready = false;
	table->threads_runnig = 0;
	table->mtx_rdy_bool = false;
	table->mtx_bool = false;
	table->write_bool = false;
	table->philo = NULL;
	return (0);
}
