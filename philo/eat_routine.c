/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:09:42 by sde-silv          #+#    #+#             */
/*   Updated: 2024/01/30 15:09:44 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	update_meal_time(t_philo *philo)
{
	long long	currtime;

	pthread_mutex_lock(&philo->mtx_last_eat);
	currtime = get_milli_time();
	philo->last_eat_time = currtime;
	pthread_mutex_unlock(&philo->mtx_last_eat);
}

void	pick_fork(t_philo *philo, char d)
{
	if (d == 'l')
	{
		pthread_mutex_lock(philo->ptr_mtx_lfork);
		print(philo, "has taken a fork");
		*philo->ptr_lfork = philo->id;
	}
	else
	{
		pthread_mutex_lock(philo->ptr_mtx_rfork);
		print(philo, "has taken a fork");
		*philo->ptr_rfork = philo->id;
	}
}

void	return_fork(t_philo *philo, char d)
{
	if (d == 'l')
	{
		*philo->ptr_lfork = 0;
		pthread_mutex_unlock(philo->ptr_mtx_lfork);
	}
	else if (d == 'r')
	{
		*philo->ptr_rfork = 0;
		pthread_mutex_unlock(philo->ptr_mtx_rfork);
	}
}

int	routine_for_one(t_philo *philo)
{
	pthread_mutex_lock(philo->ptr_mtx_lfork);
	print(philo, "has taken a fork");
	*philo->ptr_lfork = philo->id;
	*philo->ptr_lfork = 0;
	pthread_mutex_unlock(philo->ptr_mtx_lfork);
	print(philo, "put down a fork");
	custom_sleep(philo->life_len);
	print(philo, "is dead");
	return (0);
}

void	philo_eat(t_philo *philo)
{
	if ((philo->id % 2) == 0)
	{
		pick_fork(philo, 'l');
		pick_fork(philo, 'r');
		update_meal_time(philo);
		print(philo, "is eating");
		custom_sleep(philo->eat_len);
		return_fork(philo, 'l');
		return_fork(philo, 'r');
	}
	else
	{
		pick_fork(philo, 'r');
		pick_fork(philo, 'l');
		update_meal_time(philo);
		print(philo, "is eating");
		custom_sleep(philo->eat_len);
		return_fork(philo, 'l');
		return_fork(philo, 'r');
	}
}
