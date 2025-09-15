/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:08:00 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/15 12:15:33 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	my_mutex_destroy(&table->mutex, table->mtx_bool);
	my_mutex_destroy(&table->mutex_ready, table->mtx_rdy_bool);
	my_mutex_destroy(&table->write_lock, table->write_bool);
	while (i < table->nb_philo)
	{
		my_mutex_destroy(&table->philo[i].philo_mutex,
			table->philo[i].phil_bool);
		my_mutex_destroy(&table->fork[i].fork, table->fork[i].fork_init);
		i++;
	}
	free(table->philo);
	free(table->fork);
}

void	philo_print(t_mtx *mtx, t_philo *phil, int action)
{
	time_t	time;

	if (phil->full)
		return ;
	if (simulation_finish(phil->table_info))
		return ;
	my_mutex_lock(mtx);
	if (get_bool(&phil->table_info->mutex, &phil->table_info->end))
	{
		my_mutex_unlock(mtx);
		return ;
	}
	time = now_time_ms() - phil->table_info->time;
	if (action == TAKE_FORK)
		printf("%ld      %d has taken a fork\n", time, phil->index);
	else if (action == EAT)
		printf("%ld      %d is eating\n", time, phil->index);
	else if (action == SLEEP)
		printf("%ld      %d is sleeping\n", time, phil->index);
	else if (action == THINK)
		printf("%ld      %d is thinking\n", time, phil->index);
	else if (action == DEAD)
		printf("%ld      %d died\n", time, phil->index);
	my_mutex_unlock(mtx);
}

void	*dinner(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	wait_is_ready(&philo->table_info->mutex_ready, &philo->table_info->ready);
	set_long(&philo->philo_mutex, &philo->no_eat, gettime(MILLISECOND));
	incremente_long(&philo->table_info->mutex,
		&philo->table_info->threads_runnig);
	desincronyse(philo);
	while (!simulation_finish(philo->table_info))
	{
		if (philo->full)
			break ;
		eat(philo);
		philo_print(&philo->table_info->write_lock, philo, SLEEP);
		precise_usleep(philo->table_info->time_sleep, philo->table_info);
		thinking(philo);
	}
	return (NULL);
}

void	start(t_table *table)
{
	int	i;

	i = 0;
	if (table->nb_limit_eat == 0)
		return ;
	my_mutex_init(&table->mutex_ready, table);
	table->mtx_rdy_bool = true;
	my_mutex_lock(&table->mutex_ready);
	create_thread(table);
	table->time = now_time_ms();
	table->ready = true;
	my_mutex_unlock(&table->mutex_ready);
	while (i < table->nb_philo)
	{
		my_pthread_join(table->philo[i].thread_id, NULL, table);
		i++;
	}
	my_pthread_join(table->monitor, NULL, table);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (0);
	parse_input(&table, av, ac);
	data_init(&table);
	start(&table);
	free_all(&table);
	return (0);
}
