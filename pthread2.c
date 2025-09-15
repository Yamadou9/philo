/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:33:39 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/15 12:34:18 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_pthread_join(pthread_t t, void **null, t_table *table)
{
	int	rc;

	rc = pthread_join(t, null);
	if (rc != 0)
	{
		if (rc == 22)
			put_error("Error: Thread not joinable or already joined\n");
		else if (rc == 3)
			put_error("Error: No such thread\n");
		else if (rc == 35)
			put_error("Error: Deadlock (joining self)\n");
		else
			put_error("Error: pthread_join failed\n");
		free_all(table);
		exit(EXIT_FAILURE);
	}
}

int	my_pthread_create(pthread_t *t, void *(*f)(void *), void *arg)
{
	int	rc;

	rc = pthread_create(t, NULL, f, arg);
	if (rc != 0)
	{
		if (rc == 11)
			put_error("Error: Not enough resources to create thread\n");
		else if (rc == 22)
			put_error("Error: Invalid thread attributes\n");
		else
			put_error("Error: pthread_create failed\n");
		return (1);
	}
	return (0);
}
