/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:08:45 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/26 11:20:09 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	if (table->mtx_bool == true)
		my_mutex_destroy(&table->mutex, table->mtx_bool);
	if (table->mtx_rdy_bool == true)
		my_mutex_destroy(&table->mutex_ready, table->mtx_rdy_bool);
	if (table->write_bool == true)
		my_mutex_destroy(&table->write_lock, table->write_bool);
	while (i < table->nb_philo)
	{
		if (table->philo[i].phil_bool)
			my_mutex_destroy(&table->philo[i].philo_mutex,
				table->philo[i].phil_bool);
		if (table->fork[i].fork_init)
			my_mutex_destroy(&table->fork[i].fork,
				table->fork[i].fork_init);
		i++;
	}
	free(table->philo);
	free(table->fork);
}

int	is_int(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] < '0' && c[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	checks(char **data)
{
	int	i;

	i = 1;
	while (data[i])
	{
		if (!is_int(data[i]))
			return (0);
		i++;
	}
	return (1);
}

bool	simulation_finish(t_table *table)
{
	return (get_bool(&table->mutex, &table->end));
}
