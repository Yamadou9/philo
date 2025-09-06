/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:17:11 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/06 17:27:53 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_init(&philo->philo_mutex, NULL);
		pthread_mutex_init(&philo->mutex_meal_count, NULL);
		pthread_mutex_init(&philo->mutex_meal_time, NULL);
		assign_fork(philo, table->fork, i);
		i++;
	}
}

void	data_init(t_table *table, char **av)
{
	int	i;

	i = 0;
	table->end = false;
	table->ready = false;
	table->philo = my_malloc(sizeof(t_philo) * table->nb_philo);
	table->fork = my_malloc(sizeof(t_fork) * table->nb_philo);
	table->threads_runnig = 0;
	pthread_mutex_init(&table->mutex, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->fork[i].fork, NULL);
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
		if (pthread_create(&table->philo->thread_id, NULL,
				dinner, &table->philo[i]))
			exit(EXIT_FAILURE);
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
