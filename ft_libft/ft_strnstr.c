/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:44 by ydembele          #+#    #+#             */
/*   Updated: 2025/05/12 15:20:37 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;

	i = 0;
	if (s2[i] == 0)
		return ((char *)s1);
	if (len == 0)
		return (0);
	while (s1[i] && i < (len - ft_strlen(s2) + 1))
	{
		if (ft_strncmp(s1 + i, s2, ft_strlen(s2)) == 0)
			return ((char *)s1 + i);
		i++;
	}
	return (0);
}
/*int	main(int ac, char **av)
{
	char haystack[30] = "aaabcabcd";
	printf("%s", ft_strnstr(haystack, "cd", 8));
}*/