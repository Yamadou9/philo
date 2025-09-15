/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:02:43 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/15 12:23:42 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_error(const char *msg)
{
	write(2, msg, strlen(msg));
}

void	my_mutex_init(t_mtx *mtx, t_table *table)
{
	int	err;

	err = pthread_mutex_init(mtx, NULL);
	if (err != 0)
	{
		put_error("Error: pthread_mutex_init failed\n");
		free_all(table);
		exit(EXIT_FAILURE);
	}
}

void	my_mutex_lock(t_mtx *mtx)
{
	int	err;

	err = pthread_mutex_lock(mtx);
	if (err != 0)
	{
		if (err == 35)
			put_error("Error: Deadlock detected\n");
		else if (err == 22)
			put_error("Error: Invalid mutex\n");
		else
			put_error("Error: pthread_mutex_lock failed\n");
		exit(EXIT_FAILURE);
	}
}

void	my_mutex_unlock(t_mtx *m)
{
	int	rc;

	rc = pthread_mutex_unlock(m);
	if (rc != 0)
	{
		if (rc == 1)
			put_error("Error: Unlocking a mutex not owned by this thread\n");
		else if (rc == 22)
			put_error("Error: Invalid mutex\n");
		else
			put_error("Error: pthread_mutex_unlock failed\n");
		exit(EXIT_FAILURE);
	}
}

void	my_mutex_destroy(t_mtx *m, bool b)
{
	int	rc;

	if (b == false)
		return ;
	rc = pthread_mutex_destroy(m);
	if (rc != 0)
	{
		put_error("Error: pthread_mutex_destroy failed\n");
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
