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

static int	ft_atoi(const char *nptr)
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

int	store(char **argv, int type, t_input *input)
{
	int	error;

	error = 0;
	input->philos = ft_atoi(argv[1]);
	input->t_die = ft_atoi(argv[2]);
	input->t_eat = ft_atoi(argv[3]);
	input->t_sleep = ft_atoi(argv[4]);
	if (input->philos == 0 || input->t_die == 0)
		error = 1;
	if (input->t_eat == 0 || input->t_sleep == 0)
		error = 1;
	if (type == 6)
	{
		input->min_eat = ft_atoi(argv[5]);
		if (input->min_eat == 0)
			error = 1;
	}
	else
		input->min_eat = 0;
	if (error > 0)
		return (0);
	return (1);
}

static int	check_pos_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i ++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i ++;
	}
	return (1);
}

int	parse(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!check_pos_num(argv[i]))
		{
			print_message("Values should be positive integers.", 2);
			return (0);
		}
		i ++;
	}
	return (1);
}
