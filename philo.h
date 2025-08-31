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

typedef struct t_philo
{
	int		index;
	long	c_eat;
	time_t	no_eat;
	bool	mort;
	t_philo	*next;
	t_table	*table_info;
}	t_philo;

typedef struct t_table
{
	time_t	time_eat;
	time_t	time_sleep;
	time_t	time_die;
	time_t	time_think;
	int		nb_philo;
	t_philo	*philo;
	time_t	time;
}	t_table;

#endif
