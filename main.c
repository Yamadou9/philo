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

void	init_philos(int ac, char **av, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		ft_lstnew(i);
	}
}


int	main(int ac, char **av)
{
	
}