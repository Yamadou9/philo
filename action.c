/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:14:42 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/15 12:16:04 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	my_mutex_lock(&philo->f_fork->fork);
	philo_print(&philo->table_info->write_lock, philo, TAKE_FORK);
	my_mutex_lock(&philo->s_fork->fork);
	philo_print(&philo->table_info->write_lock, philo, TAKE_FORK);
	set_long(&philo->philo_mutex, &philo->no_eat, gettime(MILLISECOND));
	philo->c_eat++;
	philo_print(&philo->table_info->write_lock, philo, EAT);
	precise_usleep(philo->table_info->time_eat, philo->table_info);
	if (philo->table_info->nb_limit_eat > 0
		&& philo->c_eat == philo->table_info->nb_limit_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	my_mutex_unlock(&philo->f_fork->fork);
	my_mutex_unlock(&philo->s_fork->fork);
}

void	thinking(t_philo *philo)
{
	time_t	think;

	think = philo->table_info->time_eat * 2 - philo->table_info->time_sleep;
	if (think < 0)
		think = 0;
	philo_print(&philo->table_info->write_lock, philo, THINK);
	precise_usleep(think * 0.42, philo->table_info);
}
