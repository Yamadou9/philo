/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:17:11 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/26 11:36:46 by ydembele         ###   ########.fr       */
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
		if (my_mutex_init(&philo->philo_mutex, table))
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
	table->philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philo)
		return (1);
	table->fork = malloc(sizeof(t_fork) * table->nb_philo);
	if (!table->fork)
		return (free(table->philo), 1);
	while (i < table->nb_philo)
	{
		table->fork[i].fork_init = false;
		table->philo[i++].phil_bool = false;
	}
	if (my_mutex_init(&table->mutex, table))
		return (free_all(table), 1);
	table->mtx_bool = true;
	if (my_mutex_init(&table->write_lock, table))
		return (free_all(table), 1);
	table->write_bool = true;
	i = 0;
	while (i < table->nb_philo)
	{
		if (my_mutex_init(&table->fork[i].fork, table))
			return (free_all(table), 1);
		table->fork[i].fork_id = i;
		table->fork[i++].fork_init = true;
	}
	return (0);
}

int	create_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (my_pthread_create(&table->philo[i].thread_id,
				dinner, &table->philo[i]))
		{
			while (--i >= 0)
				my_pthread_join(table->philo[i].thread_id, NULL, table);
			my_mutex_unlock(&table->mutex_ready);
			free_all(table);
			return (1);
		}
		i++;
	}
	if (my_pthread_create(&table->monitor, check_monitor, table))
	{
		while (--i >= 0)
			my_pthread_join(table->philo[i].thread_id, NULL, table);
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
	if (table->time_eat == -1 || table->time_sleep == -1
		|| table->time_die == -1 || table->nb_philo == -1
		|| (table->nb_limit_eat == -1 && ac == 6))
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
