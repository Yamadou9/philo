/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:08:59 by ydembele          #+#    #+#             */
/*   Updated: 2025/04/28 17:26:24 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s, const void *d, size_t n)
{
	size_t		i;

	i = 0;
	if (n == 0)
		return (0);
	while (*(unsigned char *)(s + i) == *(unsigned char *)(d + i) && i < n - 1)
		i++;
	return (*(unsigned char *)(s + i) - *(unsigned char *)(d + i));
}

/*int main()
{
	char s2[] = {0, 0, 127, 0};
	char s3[] = {0, 0, 42, 0};
	printf("%d", ft_memcmp(s2, s3, 4));
}*/