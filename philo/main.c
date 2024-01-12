/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:55:33 by sde-silv          #+#    #+#             */
/*   Updated: 2024/01/09 11:55:35 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int	main(int argc, char **argv)
{
	t_input	input;

	if (argc == 5 || argc == 6)
	{
		if (!parse(argv))
			return (1);
		if (!store(argv, argc, &input))
		{
			print_message("Values should be larger than 0.", 2);
			return (1);
		}
		init(&input);
		//print_details(input);
	}
	else
		write(1, "Usage: #philo t_die t_eat t_sleep [min_eat_times]\n", 50);
	return (0);
}
