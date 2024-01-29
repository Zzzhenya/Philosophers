/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:32:06 by sde-silv          #+#    #+#             */
/*   Updated: 2024/01/23 17:32:09 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	print_forks(t_env *env)
{
	int	i;

	i = 0;
	printf("\nmtx_Forks\n");
	while (i < env->ph_num)
	{
		printf("%p ", &env->mtx_forks[i]);
		i ++;
	}
	printf("\nForks\n");
	i = 0;
	while (i < env->ph_num)
	{
		printf("%p : %d ", &env->forks[i], env->forks[i]);
		i ++;
	}
	printf("\nFinal Forks \n");
	i = 0;
	while (i < env->ph_num)
	{
		printf("%p %p : ", env->ph[i].ptr_lfork, env->ph[i].ptr_rfork);
		printf("%p %p\n", env->ph[i].ptr_mtx_lfork, env->ph[i].ptr_mtx_rfork);
		i ++;
	}
}

void	print_status(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->ph_num)
	{
		printf("%p %d, ", &env->status[i], env->status[i]);
		i ++;
	}
	printf("\n");
	i = 0;
	while (i < env->ph_num)
	{
		printf("%p %d, ", env->ph[i].status, *env->ph[i].status);
		i ++;
	}
	printf("\n");
}
