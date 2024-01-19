/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
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
	env->ph_num	= ft_atoi(argv[1]);
	env->eat_len = ft_atoi(argv[3]);
	env->sleep_len = ft_atoi(argv[4]);
	env->life_len = ft_atoi(argv[2]);
	if (argc == 6)
		env->eat_count = ft_atoi(argv[5]);
	else
		env->eat_count = -1;
	env->eat_philos = env->ph_num;
	env->dead = 0;
}

void	setup_philos(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->ph_num)
	{
		env->ph[i].id = i + 1;
		env->ph[i].ph_num = env->ph_num;
		env->ph[i].eat_time = env->eat_time;
		env->ph[i].sleep_time = env->sleep_time;
		env->ph[i].life_time = env->life_time;
		env->ph[i].min_eat = env->min_eat;
		env->ph[i].start = 0; // Start here or when thread created?
		env->ph[i].last_eat_time = 0;
		env->ph[i].dead = &env->dead;
		env->ph[i].all_eat = &env->all_eat;
		env->ph[i].mtx_print = &env->mtx_print;
		env->ph[i].mtx_dead = &env->mtx_dead;
		env->ph[i].mtx_ecount = &env->mtx_ecount;
		i ++;
	}
}

void	setup_forks(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->ph_num)
	{
		if (i == env->ph_num - 1)
			env->ph[i].rfork = &env->forks[0];
		else
			env->ph[i].rfork = &env->forks[i];
		if (i == 0)
			env->ph[i].lfork = &env->forks[env->ph_num - 1];
		else
			env->ph[i].lfork = &env->forks[i - 1];
		i ++;
	}
}

void	init_struct(t_env *env, int argc, char **argv)
{
	setup_env(env, argc, argv);
	setup_philos(env);
	setup_forks(env);
}
