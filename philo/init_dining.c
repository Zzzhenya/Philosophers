/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dining.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:32:31 by sde-silv          #+#    #+#             */
/*   Updated: 2024/01/23 17:32:33 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int	make_threads(t_env *env, int i, int ret)
{
	long long	time;

	time = get_milli_time();
	while (i < env->ph_num)
	{
		env->ph[i].last_eat_time = get_milli_time();
		env->ph[i].start_time = time;
		if (pthread_create(&env->ph[i].thread, NULL, &routine, (void *)&env->ph[i]) != 0)
		{
			print_error("Pthread create error.");
			return (ret ++);
		}
		i ++;
	}
	if (pthread_create(&env->monitor, NULL, &checker, env) != 0)
	{
		print_error("Pthread create error for monitor.");
		return (ret ++);
	}
	return (ret);
}

int	join_threads(t_env *env, int i, int ret)
{
	while (i < env->ph_num)
	{
		if (pthread_join(env->ph[i].thread, NULL) != 0)
		{
			print_error("Pthread join error.");
			return (ret ++);
		}
		i ++;
	}
	if (pthread_join(env->monitor, NULL) != 0)
	{
		print_error("Pthread join error for monitor.");
		return (ret ++);
	}
	return (ret);
}

int	init_dining(t_env *env)
{
	if (make_threads(env, 0, 0) != 0)
		return (destroy_all(env, 1));
	if (join_threads(env, 0, 0) != 0)
		return (destroy_all(env, 1));
	return (destroy_all(env, 0));
}
