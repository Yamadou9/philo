/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:08:00 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/06 17:27:05 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_mtx *mtx, t_philo *phil, int action)
{
	time_t	time;

	if (phil->full)
		return ;
	if (simulation_finish(phil->table_info))
		return ;
	pthread_mutex_lock(mtx);
	if (get_bool(&phil->table_info->mutex, &phil->table_info->end))
	{
		pthread_mutex_unlock(mtx);
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
		printf("%ld      %d is dead\n", time, phil->index);
	pthread_mutex_unlock(mtx);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->f_fork->fork);
	philo_print(&philo->table_info->write_lock, philo, TAKE_FORK);
	pthread_mutex_lock(&philo->s_fork->fork);
	philo_print(&philo->table_info->write_lock, philo, TAKE_FORK);
	set_long(&philo->philo_mutex, &philo->no_eat, gettime(MILLISECOND));
	philo->c_eat++;
	philo_print(&philo->table_info->write_lock, philo, EAT);
	precise_usleep(philo->table_info->time_eat, philo->table_info);
	if (philo->table_info->nb_limit_eat > 0
		&& philo->c_eat == philo->table_info->nb_limit_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->f_fork->fork);
	pthread_mutex_unlock(&philo->s_fork->fork);
}

void	*dinner(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	wait_is_ready(&philo->table_info->mutex_ready, &philo->table_info->ready);
	set_long(&philo->philo_mutex, &philo->no_eat, gettime(MILLISECOND));
	incremente_long(&philo->table_info->mutex,
		&philo->table_info->threads_runnig);
	while (!simulation_finish(philo->table_info))
	{
		if (philo->full)
			break ;
		eat(philo);
		philo_print(&philo->table_info->write_lock, philo, SLEEP);
		precise_usleep(philo->table_info->time_sleep, philo->table_info);
	}
	return (NULL);
}

void	start(t_table *table)
{
	int	i;

	i = 0;
	if (table->nb_limit_eat == 0)
		return ;
	if (pthread_mutex_init(&table->mutex_ready, NULL) == -1)
		exit(1);
	pthread_mutex_lock(&table->mutex_ready);
	create_thread(table);
	pthread_create(&table->monitor, NULL, check_monitor, table);
	table->time = now_time_ms();
	table->ready = true;
	pthread_mutex_unlock(&table->mutex_ready);
	while (i < table->nb_philo)
	{
		pthread_join(table->philo[i].thread_id, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 || ac != 6)
		return (0);
	parse_input(&table, av, ac);
	data_init(&table, av);
	start(&table);
	return (0);
}
