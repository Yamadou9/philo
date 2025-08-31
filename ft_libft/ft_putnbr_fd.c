/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:24:54 by ydembele          #+#    #+#             */
/*   Updated: 2025/05/12 15:18:51 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	d;	

	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	if (n < 10)
	{
		d = n + 48;
		write(fd, &d, 1);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		d = n % 10 + 48;
		write(fd, &d, 1);
	}
}

/*int	main(int ac, char **av)
{
	int	fd;
	int	n;

	fd = open(av[2], O_WRONLY);
	printf("%d", fd);
	n = atoi(av[1]);	
	ft_putnbr_fd(n, fd);
}*/
