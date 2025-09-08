/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:12:24 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/08 16:51:08 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(t_mtx *mtx, bool *value, t_table *table)
{
	bool	ret;

	my_mutex_lock(mtx, &table);
	ret = *value;
	my_mutex_unlock(mtx, &table);
	return (ret);
}

void	set_bool(t_mtx *mtx, bool *dest, bool value, t_table *table)
{
	my_mutex_lock(mtx, &table);
	*dest = value;
	my_mutex_unlock(mtx, &table);
}

long	get_long(t_mtx *mtx, long *value, t_table *table)
{
	long	ret;

	my_mutex_lock(mtx, &table);
	ret = *value;
	my_mutex_unlock(mtx, &table);
	return (ret);
}

void	set_long(t_mtx *mtx, long *dest, long value, t_table *table)
{
	my_mutex_lock(mtx, &table);
	*dest = value;
	my_mutex_unlock(mtx, &table);
}

void	incremente_long(t_mtx *mtx, long *nb, t_table *table)
{
	my_mutex_lock(mtx, &table);
	(*nb)++;
	my_mutex_unlock(mtx, &table);
}
