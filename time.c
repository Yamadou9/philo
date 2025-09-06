/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:21:26 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/06 17:27:36 by ydembele         ###   ########.fr       */
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

long	gettime(int code)
{
	struct timeval	tv;

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
