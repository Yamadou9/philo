
#include "philo.h"

int	is_int(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
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

