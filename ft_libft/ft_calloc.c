/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:57:22 by ydembele          #+#    #+#             */
/*   Updated: 2025/05/12 15:17:35 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;
	size_t	t;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (0);
	t = nmemb * size;
	s = malloc(size * nmemb);
	if (s == NULL)
		return (NULL);
	ft_memset(s, 0, t);
	return (s);
}
