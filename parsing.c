/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:08:45 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/06 17:26:35 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_int(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] < '0' && c[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	checks(char **data)
{
	int	i;

	i = 1;
	while (data[i])
	{
		if (!is_int(data[i]))
			return (0);
		i++;
	}
	return (1);
}

void	*my_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (res == NULL)
		exit(1);
	return (res);
}

bool	simulation_finish(t_table *table)
{
	return (get_bool(&table->mutex, &table->end));
}
