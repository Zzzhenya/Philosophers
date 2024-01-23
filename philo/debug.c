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
/*
void	print_details(t_env *input)
{
	int	i;

	i = 0;
	printf("Philos: %d\n", input->philos);
	printf("t_die: %d\n", input->t_die);
	printf("t_eat: %d\n", input->t_eat);
	printf("t_sleep: %d\n", input->t_sleep);
	if (input->min_eat)
		printf("min_eat: %d\n", input->min_eat);
	while (i < input->philos)
	{
		printf("\nPhilo %d\n", i);
		printf("Philo_id: %d\n", input->philo_arr[i].philo_id);
		printf("Last_eat: %lld\n", input->philo_arr[i].last_eat_time);
		i ++; 
	}
	i = 0;
	printf("Forks\n");
	while (i < input->philos)
	{
		printf("Fork %d: @%p\n", i, &input->mutex[i]);
		i ++;
	}
}*/

void  print_forks(t_env *env)
{
	int i;

	
	printf("\nmtx_Forks\n");
	i = 0;
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

void print_status(t_env *env)
{
	int i = 0;
	
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
