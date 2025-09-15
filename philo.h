/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:30:30 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/15 12:37:00 by ydembele         ###   ########.fr       */
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


# define SECOND 1
# define MILLISECOND 2
# define MICROSECOND 3


# define TAKE_FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DEAD 5

typedef pthread_mutex_t	t_mtx;
typedef struct t_table t_table;


int		checks(char **data);

void	*my_malloc(size_t size);

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
	bool	fork_init;
}	t_fork;

typedef struct t_philo
{
	int				index;
	long			c_eat;
	time_t			no_eat;
	bool			mort;
	bool			full;
	t_fork			*f_fork;
	t_fork			*s_fork;
	struct t_philo	*next;
	t_table			*table_info;
	t_mtx			philo_mutex;
	bool			phil_bool;
	pthread_t		thread_id;
}	t_philo;

typedef struct t_table
{
	time_t		time_eat;
	time_t		time_sleep;
	time_t		time_die;
	time_t		time_think;
	int			nb_philo;
	long		nb_limit_eat;
	long		start_time;
	long		passed_time;
	long		threads_runnig;
	t_mtx		mutex_ready;
	bool		mtx_rdy_bool;
	t_mtx		mutex;
	bool		mtx_bool;
	t_mtx		write_lock;
	bool		write_bool;
	t_philo		*philo;
	time_t		time;
	bool		end;
	bool		ready;
	pthread_t	monitor;
	t_fork		*fork;
}	t_table;

bool	simulation_finish(t_table *table);
void	wait_is_ready(t_mtx *mtx, bool *ready);
long	ft_atoi(const char *nptr);
bool	get_bool(t_mtx *mtx, bool *value);
void	set_bool(t_mtx *mtx, bool *dest, bool value);
long	get_long(t_mtx *mtx, long *value);
void	set_long(t_mtx *mtx, long *dest, long value);
void	incremente_long(t_mtx *mtx, long *nb);
bool	died(t_philo *philo);
bool	all_full(t_table *table);
void	*check_monitor(void *tble);
void	init_philos(t_table *table);
void	create_thread(t_table *table);
void	*dinner(void *phil);
void	assign_fork(t_philo *philo, t_fork *fork, int i);
void	wait_is_ready(t_mtx *mtx, bool *ready);
bool	threads_run(t_mtx *mtx, long *nb_run, long nb);
long	now_time_ms(void);
long	passed_ms(long start);
long	gettime(int code);
void	parse_input(t_table *table, char **av, int ac);
void	data_init(t_table *table);
void	precise_usleep(long usec, t_table *table);
void	philo_print(t_mtx *mtx, t_philo *phil, int action);
int		is_int(char *c);
int		my_pthread_create(pthread_t *t, void *(*f)(void *), void *arg);
void	my_mutex_lock(t_mtx *mtx);
void	my_mutex_unlock(t_mtx *mtx);
void	my_mutex_destroy(t_mtx *m, bool b);
void	my_pthread_join(pthread_t t, void **null, t_table *table);
void	my_mutex_init(t_mtx *mtx, t_table *table);
void	free_all(t_table *table);
void	desincronyse(t_philo *philo);
void	eat(t_philo *philo);
void	thinking(t_philo *philo);
void	put_error(const char *msg);

#endif
