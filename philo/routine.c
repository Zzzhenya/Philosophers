/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:09:51 by sde-silv          #+#    #+#             */
/*   Updated: 2024/01/30 15:09:53 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	philo_sleep(t_philo *philo)
{
	print(philo, "is sleeping");
	custom_sleep(philo->sleep_len);
}

void	philo_think(t_philo *philo)
{
	print(philo, "is thinking");
}

void	optional_counter(t_philo *philo)
{
	if (philo->eat_count > -1)
		philo->eat_count --;
	if (philo->eat_count == 0)
	{
		pthread_mutex_lock(philo->mtx_eat_philos);
		*philo->eat_philo_count -= 1;
		pthread_mutex_unlock(philo->mtx_eat_philos);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->mtx_ready);
		if (*philo->ready == 1)
		{
			pthread_mutex_unlock(philo->mtx_ready);
			break;
		}
		pthread_mutex_unlock(philo->mtx_ready);
		usleep (100);
	}
	philo_think(philo);
	if (philo->ph_num == 1)
	{
		routine_for_one (philo);
		return ((void *)0);
	}
	if (philo->id % 2 == 0)
		usleep (100);
	while (is_alive(philo))
	{
		philo_eat(philo);
		optional_counter(philo);
		philo_sleep(philo);
		philo_think(philo);
		/*if (philo->ph_num % 2 != 0)
			custom_sleep(philo->eat_len);*/
		custom_sleep(1);
		if (philo->ph_num % 2 != 0 && philo->id % 2 == 0)
			usleep (100);
	}
	return ((void *)0);
}
