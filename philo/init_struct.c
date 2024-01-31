/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:55:25 by sde-silv          #+#    #+#             */
/*   Updated: 2024/01/09 11:55:27 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	setup_env(t_env *env, int argc, char **argv)
{
	env->ph_num = ft_atol(argv[1]);
	env->eat_len = ft_atol(argv[3]);
	env->sleep_len = ft_atol(argv[4]);
	env->life_len = ft_atol(argv[2]);
	if (argc == 6)
		env->eat_count = ft_atol(argv[5]);
	else
		env->eat_count = -1;
	env->eat_philo_count = env->ph_num;
	env->dead = 0;
	env->forks = NULL;
	env->status = NULL;
	env->ph = NULL;
	env->mtx_forks = NULL;
	env->ready = 0;
}

void	setup_philos(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->ph_num)
	{
		env->ph[i].ph_num = env->ph_num;
		env->ph[i].id = i + 1;
		env->ph[i].eat_len = env->eat_len;
		env->ph[i].sleep_len = env->sleep_len;
		env->ph[i].life_len = env->life_len;
		env->ph[i].eat_count = env->eat_count;
		env->ph[i].start_time = 0;
		env->ph[i].last_eat_time = 0;
		env->ph[i].status = &env->status[i];
		env->ph[i].eat_philo_count = &env->eat_philo_count;
		env->ph[i].mtx_print = &env->mtx_print;
		env->ph[i].mtx_eat_philos = &env->mtx_eat_philos;
		env->ph[i].ready = &env->ready;
		env->ph[i].mtx_ready = &env->mtx_ready;
		env->forks[i] = 0;
		env->status[i] = 0;
		i ++;
	}
}

void	setup_forks(t_env *env, int i)
{
	while (i < env->ph_num)
	{
		if (i == 0)
		{
			env->ph[i].ptr_lfork = &env->forks[env->ph_num - 1];
			env->ph[i].ptr_mtx_lfork = &env->mtx_forks[env->ph_num - 1];
		}
		else
		{
			env->ph[i].ptr_lfork = &env->forks[i - 1];
			env->ph[i].ptr_mtx_lfork = &env->mtx_forks[i - 1];
		}
		env->ph[i].ptr_rfork = &env->forks[i];
		env->ph[i].ptr_mtx_rfork = &env->mtx_forks[i];
		i ++;
	}
}

void	init_struct(t_env *env)
{
	setup_philos(env);
	setup_forks(env, 0);
}
