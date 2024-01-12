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
	t_env				env;
	t_philo 			philos[PHILO_MAX];
	pthread_mutex_t 	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
	{
		print_error("Usage: #philo t_die t_eat t_sleep [min_eat_times]");
		return (1);
	}
	if (bad_input(argv))
		return (1);
	env.ph = philos;
	env.forks = forks;
	init_struct(&env, argc, argv);
	if (init_mtx(&env) != 0)
		return (2);
	if (init_dining(&env) != 0)
		return (3);
	//print_details(input);
	return (0);
}
