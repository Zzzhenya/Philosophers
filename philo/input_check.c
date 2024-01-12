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

int less_than_one(char *str)
{
	int ret;

	ret = ft_atoi(str);
	if (ret <= 0)
		return (1);
	else
		return (0);
}

int	bad_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (not_int(argv[i]))
		{
			print_error("Values should be positive integers.");
			return (1);
		}
		if (less_than_one(argv[i]))
		{
			print_error("Philos and times should be larger than 0.");
			return (1);
		}
		if (i == 0)
		{
			if (ft_atoi(argv[i]) > 200)
			{
				print_error("Maximum number of 200 Philosophers.");
				return (1);
			}
		}
		i ++;
	}
	return (0);
}
