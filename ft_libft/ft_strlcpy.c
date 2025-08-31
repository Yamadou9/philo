/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:35:20 by ydembele          #+#    #+#             */
/*   Updated: 2025/05/12 15:20:07 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t siz)
{
	size_t	j;
	int		i;
	int		size;

	size = (int)siz;
	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (size < 0)
		size = j + 1;
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
	{	
		dest[i] = 0;
		i++;
	}
	return (j);
}

// int main()
// {
//  	char src[] = "coucou";
//  	char *dest;
// 	dest = "bonjour" 
//  	printf("%d ", ft_strlcpy(dest, "", 15));
// }
