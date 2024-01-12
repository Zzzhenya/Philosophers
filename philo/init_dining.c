#include "libphilo.h"

int is_alive(t_philo *philo)
{
	int status = 0;

	pthread_mutex_lock(philo->mtx_dead);
	status = *philo->dead;
	pthread_mutex_unlock(philo->mtx_dead);
	if (status == 0)
		return (1);
	return (0);
}


void print(t_philo *philo, char *msg)
{
	long long currtime;

	pthread_mutex_lock(philo->mtx_print);
	currtime = get_milli_time();
	printf("%lld %d %s\n", currtime - philo->start,  philo->id, msg);
	pthread_mutex_unlock(philo->mtx_print);
}

void philo_eat(t_philo *philo)
{
	long long currtime;

	print(philo, "is eating");
	usleep(philo->eat_time * 1000);
	currtime = get_milli_time();
	philo->last_eat_time = currtime;
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
	long long currtime;

	philo = (t_philo *)arg;
	while (is_alive(philo))
	{
		currtime = get_milli_time();
		if (currtime >= philo->last_eat_time + philo->life_time)
		{
			pthread_mutex_lock(philo->mtx_dead);
			print(philo, "is dead");
			*philo->dead = 1;
			pthread_mutex_unlock(philo->mtx_dead);
		}
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return ((void *)0);
}

int init_dining(t_env *env)
{
	int 		i;
	long long	time;

	i = 0;
	time = get_milli_time();
	if (time <= 0)
		return (1);
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