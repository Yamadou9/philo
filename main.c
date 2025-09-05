/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:08:00 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/04 16:47:44 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long	now_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

long	passed_ms(long start)
{
	return (now_time_ms() - start);
}

void	*print_hello(void	*arg)
{
	int	i;
	i = 0;
	while (i < 100)
	{
		printf("hello\n");
		i++;
		usleep(10000);
	}
	return (NULL);
}

void	*print_world(void	*arg)
{
	int	i;
	i = 0;
	while (i < 100)
	{
		printf("		world\n");
		i++;
		usleep(10000);
	}
	return (NULL);
}

// int	ex(int ac, char **av)
// {
// 	long long	start;
// 	pthread_t	t1;
// 	pthread_t	t2;

// 	// start = now_time_ms();
// 	// printf("%lld\n", start);
// 	// usleep(1500000);
// 	// printf("temps passe = %lld\n", passed_ms(start));
// 	if (pthread_create(&t1, NULL, print_hello, NULL))
// 		exit(EXIT_FAILURE);
// 	if (pthread_create(&t2, NULL, print_world, NULL))
// 		exit(EXIT_FAILURE);
// 	if (pthread_join(t1, NULL))
// 		exit(EXIT_FAILURE);
// 	if (pthread_join(t2, NULL))
// 		exit(EXIT_FAILURE);
// 	return (0);
// }

long	gettime(int code)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		exit(1);
	if (code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		exit(1);
	return (1337);

}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finish(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(usec / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	pthread_mutex_lock(mtx);
	ret = *value;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	pthread_mutex_lock(mtx);
	ret = *value;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	set_long(t_mtx *mtx, long *dest, long value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

bool	simulation_finish(t_table *table)
{
	return (get_bool(&table->mutex, &table->end));
}

t_philo	*ft_lstnew_philo(int i)
{
	t_philo	*s;

	s = malloc(sizeof(t_philo));
	if (s == NULL)
		return (NULL);
	s->index = i;
	s->no_eat = 0;
	s->next = NULL;
	return (s);
}

void	parse_input(t_table *table, char **av)
{
	if (!checks(av))
		exit(1);
	table->time_eat = ft_atoi(av[3]) * 1e3;
	table->time_sleep = ft_atoi(av[4]) * 1e3;
	table->time_die = ft_atoi(av[2]) * 1e3;
	table->nb_philo = ft_atoi(av[1]);
	if (av[5] != NULL)
		table->nb_limit_eat = ft_atoi(av[5]);
	else
		table->nb_limit_eat = -1;
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
	while (!simulation_finish(philo->table_info))
	{
		if (philo->full)
			break ;
		eat(philo);
		philo_print(&philo->table_info->write_lock, philo, SLEEP);
		precise_usleep(philo->table_info->time_sleep, philo->table_info);
	}
}
void	create_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->philo->thread_id, NULL, dinner, &table->philo[i]))
			exit(EXIT_FAILURE);
		i++;
	}
}

void	wait_is_ready(t_mtx *mtx, bool *ready)
{
	while (get_bool(mtx, ready) == false)
		;
}
void	check_monitor(t_table *table)
{
	wait_is_ready(&table->mutex_ready, &table->ready);
}

void	start(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->mutex_ready, NULL) == -1)
		exit(1);
	pthread_mutex_lock(&table->mutex_ready);
	create_thread(table);
	table->time = now_time_ms();
	table->ready = true;
	pthread_mutex_unlock(&table->mutex_ready);
	while (i < table->nb_philo)
	{
		pthread_join(table->philo[i].thread_id, NULL);
		i++;
	}
}
// void	ft_print_eat(t_philo *philo)
// {
// 	time_t	time;
// 	long	i;

// 	time = gettime(MILLISECOND) - philo->table_info->time;
// 	i = get_long(&philo->mutex_meal_count, &philo->c_eat);
// 	++i;
// 	printf("%ld      %d is eating\n", time, philo->index);
// 	set_long(&philo->mutex_meal_count, &philo->c_eat, i);
// 	if (philo->table_info->extra_args
// 		&& i == get_long(&philo->table_info->mutex_meal_count,
// 			&philo->table_info->nb_limit_eat))
// 		set_bool(&philo->mutex_meal_count, &philo->full, true);
// }



int	main(int ac, char **av)
{
	t_table	table;

	parse_input(&table, av);
	data_init(&table, av);
	start(&table);
	return (0);
}

