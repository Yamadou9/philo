/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:17:11 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/08 16:42:09 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	null_fonction(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	table->mutex = NULL;
// 	table->mutex_ready);
// 	table->write_lock);
// 	while (i < table->nb_philo)
// 	{
// 		table->philo[i].philo_mutex);
// 		table->fork[i].fork);
// 		i++;
// 	}
// }

void	init_philos(t_table *table)
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
		philo->phil_bool = false;
		pthread_mutex_init(&philo->philo_mutex, NULL);
		philo->phil_bool = true;
		assign_fork(philo, table->fork, i);
		i++;
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end = false;
	table->ready = false;
	table->philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philo)
		exit(EXIT_FAILURE);
	table->fork = my_malloc(sizeof(t_fork) * table->nb_philo);
	if (!table->fork)
	{
		free(table->philo);
		exit(EXIT_FAILURE);
	}
	table->threads_runnig = 0;
	table->mtx_bool = false;
	table->write_bool = false;
	while (i++ < table->nb_philo)
		table->fork[i].fork_init = false;
	my_mutex_init(&table->mutex, &table);
	my_mutex_init(&table->write_lock, &table);
	while (i < table->nb_philo)
	{
		my_mutex_init(&table->fork[i].fork, &table);
		table->fork[i].fork_id = i;
		i++;
	}
	init_philos(table);
}

void	create_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		my_pthread_create(&table->philo[i].thread_id, dinner, &table->philo[i]);
		i++;
	}
}

void	assign_fork(t_philo *philo, t_fork *fork, int i)
{
	int	nb_philo;

	nb_philo = philo->table_info->nb_philo;
	if (philo->index % 2)
	{
		philo->f_fork = &fork[i];
		philo->s_fork = &fork[(i + 1) % nb_philo];
	}
	else
	{
		philo->s_fork = &fork[i];
		philo->f_fork = &fork[(i + 1) % nb_philo];
	}
}

void	parse_input(t_table *table, char **av, int ac)
{
	if (!checks(av))
		exit(1);
	table->time_eat = ft_atoi(av[3]) * 1e3;
	table->time_sleep = ft_atoi(av[4]) * 1e3;
	table->time_die = ft_atoi(av[2]) * 1e3;
	table->nb_philo = ft_atoi(av[1]);
	if (ac == 6)
		table->nb_limit_eat = ft_atoi(av[5]);
	else
		table->nb_limit_eat = -1;
}

void	wait_is_ready(t_mtx *mtx, bool *ready)
{
	while (get_bool(mtx, ready) == false)
		;
}
