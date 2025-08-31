/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:42:18 by ydembele          #+#    #+#             */
/*   Updated: 2025/05/12 15:20:31 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*s;
	const unsigned char	*d;
	size_t				i;

	s = (unsigned char *)s1;
	d = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s[i] == d[i] && s[i] && d[i])
		i++;
	return (s[i] - d[i]);
}
/*int	ft_atoi(const char *nptr);
int		main(int ac, char **av)
{
	printf("%d\n", ft_strncmp(av[1], av[2], ft_atoi(av[3])));
	printf("%d\n", strncmp(av[1], av[2], ft_atoi(av[3])));
}*/