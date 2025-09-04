/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:30:30 by ydembele          #+#    #+#             */
/*   Updated: 2025/08/31 17:57:19 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "sys/time.h"
# include "stdio.h"
# include "stdlib.h"
# include <pthread.h>
# include "unistd.h"
# include <string.h>
# include <stdbool.h>
# include "limits.h"

typedef pthread_mutex_t	t_mtx;

int		checks(char **data);
long	ft_atoi(const char *nptr);
void	*my_malloc(size_t size);

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct t_philo
{
	int			index;
	long		c_eat;
	time_t		no_eat;
	bool		mort;
	t_fork		*f_fork;
	t_fork		*s_fork;
	t_philo		*next;
	t_table		*table_info;
	pthread_t	thread_id;
}	t_philo;

typedef struct t_tble
{
	time_t	time_eat;
	time_t	time_sleep;
	time_t	time_die;
	time_t	time_think;
	int		nb_philo;
	long	nb_limit_eat;
	t_philo	*philo;
	time_t	time;
	bool	end;
	t_fork	*fork;
}	t_table;

#endif
