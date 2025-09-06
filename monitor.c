/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:14:56 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/06 17:25:00 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	died(t_philo *philo)
{
	bool	ret;
	long	no_eat;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	ret = false;
	no_eat = gettime(MILLISECOND)
		- get_long(&philo->philo_mutex, &philo->no_eat);
	if (no_eat >= (philo->table_info->time_die / 1e3))
		ret = true;
	return (ret);
}

bool	all_full(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->nb_philo)
	{
		philo = table->philo + i;
		if (get_bool(&philo->philo_mutex, &philo->full) == false)
			return (false);
		i++;
	}
	return (true);
}

void	*check_monitor(void *tble)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)tble;
	while (!threads_run(&table->mutex, &table->threads_runnig, table->nb_philo))
		;
	while (!simulation_finish(table))
	{
		i = 0;
		if (all_full(table) == true)
			set_bool(&table->mutex, &table->end, true);
		while (i < table->nb_philo && !simulation_finish(table))
		{
			if (died(table->philo + i))
			{
				philo_print(&table->write_lock, table->philo + i, DEAD);
				set_bool(&table->mutex, &table->end, true);
			}
			i++;
		}
	}
	return (NULL);
}

bool	threads_run(t_mtx *mtx, long *nb_run, long nb)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mtx);
	if (*nb_run == nb)
		ret = true;
	pthread_mutex_unlock(mtx);
	return (ret);
}
