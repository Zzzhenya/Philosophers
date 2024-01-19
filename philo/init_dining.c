#include "libphilo.h"

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->mtx_dead);
	if (*philo->dead == 0)
	{
		pthread_mutex_unlock(philo->mtx_dead);
		return (1);
	}
	pthread_mutex_unlock(philo->mtx_dead);
	return (0);
}

void print(t_philo *philo, char *msg)
{
	long long currtime;

	pthread_mutex_lock(philo->mtx_print);
	currtime = get_milli_time();
	//printf("%lld %d %s\n", currtime - philo->start,  philo->id, msg);
	if (is_alive(philo))
		printf("%lld %d %s\n", currtime,  philo->id, msg);
	pthread_mutex_unlock(philo->mtx_print);
}

void pick_fork(t_philo *philo, char d)
{
	if (d == 'l')
	{
		pthread_mutex_lock(philo->lfork);
		print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		print(philo, "has taken a fork");
	}
}

void return_fork(t_philo *philo, char d)
{
	if (d == 'l')
	{
		pthread_mutex_unlock(philo->lfork);
		//print(philo, "put down a fork");
	}
	else
	{
		pthread_mutex_unlock(philo->rfork);
		//print(philo, "put down a fork");
	}

}

void update_meal_time(t_philo *philo)
{
	long long currtime;

	pthread_mutex_lock(&philo->mtx_last_meal);
	currtime = get_milli_time();
	philo->last_eat_time = currtime;
	pthread_mutex_unlock(&philo->mtx_last_meal);

}

void philo_eat(t_philo *philo)
{
	//if (philo->t_die > philo->t_eat + philo->t_sleep)
	if (!(philo->id % 2))
	{

		pick_fork(philo, 'l');
		pick_fork(philo, 'r');
		print(philo, "is eating");
		update_meal_time(philo);
		usleep(philo->eat_time * 1000);
		return_fork(philo, 'l');
		return_fork(philo, 'r');
	}
	else
	{
		pick_fork(philo, 'r');
		pick_fork(philo, 'l');
		print(philo, "is eating");
		update_meal_time(philo);
		usleep(philo->eat_time * 1000);
		return_fork(philo, 'r');
		return_fork(philo, 'l');
	}
}

void philo_sleep(t_philo *philo)
{
	print(philo, "is sleeping");
	usleep(philo->sleep_time * 1000);
}

void philo_think(t_philo *philo)
{
	print(philo, "is thinking");
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo_think(philo);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return ((void *)0);
}

void *checker(void *arg)
{
	t_env	*env;
	int		i;
	long long time;

	env = (t_env *)arg;
	while (1)
	{
		i = 0;
		while (i < env->ph_num)
		{
			pthread_mutex_lock(&env->ph[i].mtx_last_meal);
			time = get_milli_time();
			if (time >= env->ph[i].last_eat_time + env->life_time)
			{
				pthread_mutex_lock(&env->mtx_dead);
				env->dead = 1;
				pthread_mutex_unlock(&env->mtx_dead);
				pthread_mutex_unlock(&env->ph[i].mtx_last_meal);
				return ((void *)1);
			}
			pthread_mutex_unlock(&env->ph[i].mtx_last_meal);
			i ++;
		}
	}
	return ((void *)0);
}

int init_dining(t_env *env)
{
	int 		i;
	long long	time;
	pthread_t	monitor;

	i = 0;
	time = get_milli_time();
	if (time <= 0)
		return (1);
	pthread_create(&monitor, NULL, &checker, env);
	while (i < env->ph_num)
	{
		env->ph[i].start = time;
		env->ph[i].last_eat_time = time;
		if (pthread_create(&env->ph[i].thread, NULL, &routine, (void *)&env->ph[i]) != 0)
		{
			print_error("Pthread create error.");
			return (destroy_all(env, 1));
		}
		i ++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < env->ph_num)
	{
		if (pthread_join(env->ph[i].thread, NULL) != 0)
		{
			print_error("Pthread join error.");
			return (destroy_all(env, 1));
		}
		i ++;
	}
	return (destroy_all(env, 0) != 0);
}