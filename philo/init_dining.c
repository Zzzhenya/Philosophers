#include "libphilo.h"

void print(t_philo *philo, char *msg)
{
	long long currtime;

	pthread_mutex_lock(philo->mtx_print);
	currtime = get_milli_time();
	printf("%lld %d %s\n", currtime - philo->start,  philo->id, msg);
	pthread_mutex_unlock(philo->mtx_print);
}

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

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (is_alive(philo))
	{
		print(philo, "Alive");
		if (philo->id == 1)
		{
			sleep(1);
			pthread_mutex_lock(philo->mtx_dead);
			print(philo, "Dead");
			*philo->dead = 1;
			pthread_mutex_unlock(philo->mtx_dead);
		}
		else
			sleep(1);
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