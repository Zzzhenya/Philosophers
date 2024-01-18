/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_store.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:55:40 by sde-silv          #+#    #+#             */
/*   Updated: 2024/01/09 11:55:42 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		n;
	int		sign;

	i = 0;
	sign = 1;
	n = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i ++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + (nptr[i] - 48);
		i ++;
	}
	return (sign * n);
}

static int	not_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i ++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i ++;
	}
	return (0);
}

int not_in_range(char *str, int i)
{
	int ret;

	ret = ft_atoi(str);
	if (ret <= 0)
	{
		print_error("Philos and times should be larger than 0.");
		return (1);
	}
	else if ((i == 3 || i == 4)  && ret * 1000 > 1000000)
	{
		// Check whether max is 1000000 or unsigned int max in linux
		print_error("Eat or sleep might be of usleep range.");
		return (2);
	}
	else if (i == 1 && ret > 200)
	{
		print_error("Maximum number of 200 Philosophers.");
		return (3);
	}
	else
		return (0);
}

int	bad_input(char **argv)
{
	int	i;
	int val;

	i = 1;
	while (argv[i])
	{
		if (not_int(argv[i]))
		{
			print_error("Values should be positive integers.");
			return (1);
		}
		val = not_in_range(argv[i], i);
		if (val > 0)
			return (1);
		i ++;
	}
	return (0);
}
