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

void	get_forks(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->ptr_mtx_lfork);
		if (*philo->ptr_lfork == 0)
		{
			pthread_mutex_lock(philo->ptr_mtx_rfork);
			if (*philo->ptr_rfork == 0)
			{
				print(philo, "got forks");
				*philo->ptr_lfork = philo->id;
				*philo->ptr_rfork = philo->id;
				pthread_mutex_unlock(philo->ptr_mtx_rfork);
				pthread_mutex_unlock(philo->ptr_mtx_lfork);
				return ;
			}
			else
			{
				pthread_mutex_unlock(philo->ptr_mtx_rfork);
				pthread_mutex_unlock(philo->ptr_mtx_lfork);
				usleep(10);
			}
		}
		else
		{
			pthread_mutex_unlock(philo->ptr_mtx_lfork);
			usleep(10);
		}
	}
}

void drop_forks(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->ptr_mtx_lfork);
		if (*philo->ptr_lfork == philo->id)
		{
			pthread_mutex_lock(philo->ptr_mtx_rfork);
			if (*philo->ptr_rfork == philo->id)
			{
				print(philo, "released forks");
				*philo->ptr_lfork = 0;
				*philo->ptr_rfork = 0;
				pthread_mutex_unlock(philo->ptr_mtx_rfork);
				pthread_mutex_unlock(philo->ptr_mtx_lfork);
				return ;
			}
			else
			{
				pthread_mutex_unlock(philo->ptr_mtx_rfork);
				pthread_mutex_unlock(philo->ptr_mtx_lfork);
				usleep (10);
			}
		}
		else
		{
			pthread_mutex_unlock(philo->ptr_mtx_lfork);
			usleep(10);
		}
	}
}

void	philo_eat(t_philo *philo)
{
	get_forks(philo);
	update_meal_time(philo);
	print(philo, "is eating");
	custom_sleep(philo->eat_len);
	if ((philo->id % 2) == 0)
		drop_forks(philo);
	else
	{
		usleep (1000);
		drop_forks(philo);
	}
}
