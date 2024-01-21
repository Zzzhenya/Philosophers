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

int clean_allocs(t_env *env, int l)
{
	free (env->ph);
	env->ph = NULL;
	if (l == 2)
		return (2);
	free (env->forks);
	env->forks = NULL;
	if (l == 3)
		return (3);
	free (env->mtx_forks);
	env->mtx_forks = NULL;
	if (l == 4)
		return (4);
	free (env->status);
	env->status = NULL;
	return (0);
}

int	allocate_memory(t_env *env)
{
	env->ph = malloc (sizeof(t_philo) * env->ph_num);
	if (!env->ph)
		return (1);
	env->forks = malloc (sizeof(int) * env->ph_num);
	if (!env->forks)
		return(clean_allocs(env, 2));
	env->mtx_forks = malloc (sizeof(pthread_mutex_t) * env->ph_num);
	if (!env->mtx_forks)
		return (clean_allocs(en`v, 3));
	env->status = malloc(sizeof(int) * env->ph_num);
	if (!status)
		return (clean_allocs(env, 4));
	return (0);
}

int	main(int argc, char **argv)
{
	t_env				env;

	if (argc != 5 && argc != 6)
	{
		print_error("Usage(ms): #philo die eat sleep [eat_count]");
		return (1);
	}
	if (bad_input(argv))
		return (1);
	setup_env(env, argc, argv);
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
