/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:33:22 by sde-silv          #+#    #+#             */
/*   Updated: 2024/01/23 17:33:24 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void kill_all_threads(t_env *env)
{
	int i = 0;
	while (i < env->ph_num)
	{
		pthread_mutex_lock(&env->ph[i].mtx_status);
		*env->ph[i].status = 1;
		pthread_mutex_unlock(&env->ph[i].mtx_status);
		i ++;
	}
}

int time_to_die(t_env *env, int i)
{
	long long time;

	pthread_mutex_lock(&env->ph[i].mtx_last_eat);
	time = get_milli_time();
	if (time >= env->ph[i].last_eat_time + env->life_len)
	{
		pthread_mutex_unlock(&env->ph[i].mtx_last_eat);
		print(&env->ph[i], "is dead");
		pthread_mutex_lock(&env->mtx_dead);
		env->dead = 1;
		pthread_mutex_unlock(&env->mtx_dead);
		return (1);
	}
	pthread_mutex_unlock(&env->ph[i].mtx_last_eat);
	return (0);
}	

int eat_count_complete(t_env *env)
{
	pthread_mutex_lock(&env->mtx_eat_philos);
	if (env->eat_philo_count <= 0)
	{
		pthread_mutex_unlock(&env->mtx_eat_philos);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&env->mtx_eat_philos);
		return (0);
	} 
}

void *checker(void *arg)
{
	t_env	*env;
	int		i;

	env = (t_env *)arg;
	if (env->ph_num == 1)
		return((void *)0);
	while (1)
	{
		i = 0;
		while (i < env->ph_num)
		{
			if (time_to_die(env, i) || eat_count_complete(env))
			{
				kill_all_threads(env);
				return ((void *)1);
			}
			i ++;
		}
	}
	return ((void *)0);
}	
