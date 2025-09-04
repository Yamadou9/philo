/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:08:00 by ydembele          #+#    #+#             */
/*   Updated: 2025/08/31 17:58:21 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "../ft_libft/libft.h"

long long	now_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

long long	passed_ms(long long start)
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
		assign_fork(philo, table->fork, i);
	}
}

void	data_init(t_table *table, char **av)
{
	int	i;

	i = 0;
	table->end = false;
	table->philo = my_malloc(sizeof(t_philo) * table->nb_philo);
	table->fork = my_malloc(sizeof(t_fork) * table->nb_philo);
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->fork[i].fork, NULL);
		table->fork[i].fork_id = i;
	}
	init_philos(&table);
}
void	start(t_table *table)
{

}

int	main(int ac, char **av)
{
	t_table	table;

	parse_input(&table, av);
	data_init(&table, av);
	start(&table);
}

