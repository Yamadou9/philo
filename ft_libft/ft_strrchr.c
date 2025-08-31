/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:32 by ydembele          #+#    #+#             */
/*   Updated: 2025/05/12 16:02:36 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(const char *s);

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	c = c % 256;
	i = ft_len(s);
	while (i >= 0 && s[i] != c)
		i--;
	if (i < 0)
		return (0);
	return ((char *)s + i);
}
