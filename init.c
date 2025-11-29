/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:17:11 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/29 17:56:11 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->nb_philo)
	{
		philo = table->philo + i;
		philo->index = i + 1;
		philo->c_eat = 0;
		philo->table_info = table;
		philo->full = false;
		philo->thread_created = false;
		philo->phil_bool = false;
		if (my_mutex_init(&philo->philo_mutex))
			return (free_all(table), 1);
		philo->phil_bool = true;
		assign_fork(philo, table->fork, i);
		i++;
	}
	return (0);
}

int	data_init(t_table *table)
{
	int	i;

	i = 0;
	if (malloc_fork_philo(table))
		return (1);
	while (i < table->nb_philo)
	{
		table->fork[i].fork_init = false;
		table->philo[i++].phil_bool = false;
	}
	if (my_mutex_init(&table->mutex))
		return (free_all(table), 1);
	table->mtx_bool = true;
	if (my_mutex_init(&table->write_lock))
		return (free_all(table), 1);
	table->write_bool = true;
	i = 0;
	while (i < table->nb_philo)
	{
		if (my_mutex_init(&table->fork[i].fork))
			return (free_all(table), 1);
		table->fork[i].fork_id = i;
		table->fork[i++].fork_init = true;
	}
	return (0);
}

static int	create_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (my_pthread_create(&table->philo[i].thread_id,
				dinner, &table->philo[i]))
		{
			table->end = true;
			my_mutex_unlock(&table->mutex_ready);
			while (--i >= 0)
				my_pthread_join(table->philo[i].thread_id, NULL);
			return (1);
		}
		table->philo[i].thread_created = true;
		i++;
	}
	return (0);
}

int	create_thread(t_table *table)
{
	int	i;

	if (create_philo_threads(table))
		return (1);
	if (my_pthread_create(&table->monitor, check_monitor, table))
	{
		i = table->nb_philo;
		while (--i >= 0)
			my_pthread_join(table->philo[i].thread_id, NULL);
		my_mutex_unlock(&table->mutex_ready);
		free_all(table);
		return (1);
	}
	return (0);
}

void	assign_fork(t_philo *philo, t_fork *fork, int i)
{
	int	nb_philo;

	nb_philo = philo->table_info->nb_philo;
	if (philo->index % 2)
	{
		philo->f_fork = &fork[i];
		if (nb_philo != 1)
			philo->s_fork = &fork[(i + 1) % nb_philo];
	}
	else
	{
		if (nb_philo != 1)
			philo->s_fork = &fork[i];
		philo->f_fork = &fork[(i + 1) % nb_philo];
	}
}
