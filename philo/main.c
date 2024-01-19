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

void clean_allocs(t_env *env)
{
	free (env->ph);
	env->ph = NULL;
	free (env->forks);
	env->forks = NULL;
	free (env->mtx_forks);
	env->mtx_forks = NULL;
}

int	allocate_memory(t_env *env)
{
	env->ph = malloc (sizeof(t_philo) * env->ph_num);
	if (!env->ph)
		return (1);
	env->forks = malloc (sizeof(int) * env->ph_num);
	if (!env->forks)
	{
		free (env->ph);
		return (2);
	}
	env->mtx_forks = malloc (sizeof(pthread_mutex_t) * env->ph_num);
	if (!env->mtx_forks)
	{
		free (env->ph);
		free (env->forks);
		return (3);
	}
}

int	main(int argc, char **argv)
{
	t_env				env;

	if (argc != 5 && argc != 6)
	{
		print_error("Usage: #philo t_die t_eat t_sleep [min_eat_times]");
		return (1);
	}
	if (bad_input(argv))
		return (1);
	if (allocate_memory(&env) != 0)
	{
		print_error("malloc failed.");
		return (2);
	}
	init_struct(&env, argc, argv);
	if (init_mtx(&env) != 0)
		return (3);
	if (init_dining(&env) != 0)
		return (4);
	//print_details(input);
	clean_allocs(&env);
	return (0);
}
