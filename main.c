/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:08:00 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/29 17:48:09 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_mtx *mtx, t_philo *phil, int action)
{
	long	time_ms;
	bool	full;
	bool	end;

	my_mutex_lock(mtx);
	full = get_bool(&phil->philo_mutex, &phil->full);
	end = get_bool(&phil->table_info->mutex, &phil->table_info->end);
	if (full || end)
	{
		my_mutex_unlock(mtx);
		return ;
	}
	time_ms = now_time_ms() - phil->table_info->time;
	if (action == TAKE_FORK)
		printf("%ld      %d has taken a fork\n", time_ms, phil->index);
	else if (action == EAT)
		printf("%ld      %d is eating\n", time_ms, phil->index);
	else if (action == SLEEP)
		printf("%ld      %d is sleeping\n", time_ms, phil->index);
	else if (action == THINK)
		printf("%ld      %d is thinking\n", time_ms, phil->index);
	else if (action == DEAD)
		printf("%ld      %d died\n", time_ms, phil->index);
	my_mutex_unlock(mtx);
}

void	*dinner(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	wait_is_ready(&philo->table_info->mutex_ready,
		&philo->table_info->ready, &philo->table_info->end);
	if (get_bool(&philo->table_info->mutex_ready,
			&philo->table_info->end) == true)
		return (NULL);
	set_long(&philo->philo_mutex, &philo->no_eat, gettime(MILLISECOND));
	incremente_long(&philo->table_info->mutex,
		&philo->table_info->threads_runnig);
	desincronyse(philo);
	while (!simulation_finish(philo->table_info))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		philo_print(&philo->table_info->write_lock, philo, SLEEP);
		precise_usleep(philo->table_info->time_sleep, philo->table_info);
		thinking(philo);
	}
	return (NULL);
}

void	*one_philo(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	philo->table_info->time = now_time_ms();
	my_mutex_lock(&philo->f_fork->fork);
	philo_print(&philo->table_info->write_lock, philo, TAKE_FORK);
	precise_usleep(philo->table_info->time_die, philo->table_info);
	my_mutex_unlock(&philo->f_fork->fork);
	philo_print(&philo->table_info->write_lock, philo, DEAD);
	return (NULL);
}

int	start(t_table *table)
{
	int	i;

	i = 0;
	if (table->nb_limit_eat == 0)
		return (0);
	if (table->nb_philo == 1)
	{
		if (my_pthread_create(&table->philo[0].thread_id,
				one_philo, &table->philo[i]))
			return (1);
		my_pthread_join(table->philo[0].thread_id, NULL);
		return (0);
	}
	if (my_mutex_init(&table->mutex_ready))
		return (free_all(table), 1);
	table->mtx_rdy_bool = true;
	my_mutex_lock(&table->mutex_ready);
	if (create_thread(table))
		return (1);
	table->time = now_time_ms();
	table->ready = true;
	my_mutex_unlock(&table->mutex_ready);
	while (i < table->nb_philo)
		my_pthread_join(table->philo[i++].thread_id, NULL);
	return (my_pthread_join(table->monitor, NULL), 0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (1);
	if (parse_input(&table, av, ac))
		return (1);
	if (data_init(&table))
		return (1);
	if (init_philos(&table))
		return (1);
	if (start(&table))
		return (free_all(&table), 1);
	free_all(&table);
	return (0);
}
