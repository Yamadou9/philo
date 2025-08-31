/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:49:43 by ydembele          #+#    #+#             */
/*   Updated: 2025/05/12 15:20:57 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);

int	ft_lens(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (start < ft_strlen(s) && i < len)
	{
		start++;
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char) * (ft_lens(s, start, len) + 1));
	if (res == NULL)
		return (NULL);
	while (start < ft_strlen(s) && i < len)
	{
		res[i] = s[start];
		start++;
		i++;
	}
	res[i] = 0;
	return (res);
}

/*int	main(int ac, char **av)
{
	printf("%s",ft_substr(av[1], atoi(av[2]), atoi(av[3])));
}*/
