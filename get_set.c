/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:12:24 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/08 18:12:49 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	my_mutex_lock(mtx);
	ret = *value;
	my_mutex_unlock(mtx);
	return (ret);
}

void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	my_mutex_lock(mtx);
	*dest = value;
	my_mutex_unlock(mtx);
}

long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	my_mutex_lock(mtx);
	ret = *value;
	my_mutex_unlock(mtx);
	return (ret);
}

void	set_long(t_mtx *mtx, long *dest, long value)
{
	my_mutex_lock(mtx);
	*dest = value;
	my_mutex_unlock(mtx);
}

void	incremente_long(t_mtx *mtx, long *nb)
{
	my_mutex_lock(mtx);
	(*nb)++;
	my_mutex_unlock(mtx);
}
