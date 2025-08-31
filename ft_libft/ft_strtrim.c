/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:38:55 by ydembele          #+#    #+#             */
/*   Updated: 2025/05/12 15:20:52 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strrlen(char const *s1)
{
	int	j;

	j = 0;
	while (s1[j])
		j++;
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		r;

	r = 0;
	j = 0;
	i = 0;
	if (!s1)
		return (NULL);
	while (is_set(s1[i], set) == 0)
		i++;
	j = ft_strrlen(s1) - 1;
	while (is_set(s1[j], set) == 0)
		j--;
	j = j + 1;
	if (j - i <= 0)
		return (ft_strdup("\0"));
	str = malloc(sizeof(char) * (j - i + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] && i < j)
		str[r++] = s1[i++];
	str[r] = 0;
	return (str);
}
/*int	main(int ac, char **av)
{
 	(void)ac;
 	printf("%s", ft_strtrim(av[1], av[2]));
}*/
