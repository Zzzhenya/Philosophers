#include "libphilo.h"

int destroy_forks(t_env *env)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (i < env->ph_num)
	{
		if (pthread_mutex_destroy(&env->mtx_forks[i]) != 0)
		{
			print_error ("Fork mutex destroy error.");
			ret += (i + 1);
		}
		if (pthread_mutex_destroy(&env->ph[i].mtx_last_eat) != 0)
		{
			print_error ("Last meal mutex destroy error.");
			ret += (i + 1) + (PHILO_MAX);
		}
		if (pthread_mutex_destroy(&env->ph[i].mtx_status) != 0)
		{
			print_error("philo status mutex destroy error.");
			ret += (i + 1) + (PHILO_MAX * 2);
		}
		i ++;
	}
	return (ret);
}

// Do I have to remove the already initiated threads?

int destroy_all(t_env *env, int type)
{
	int ret;

	ret = 0;
	if (pthread_mutex_destroy(&env->mtx_print) != 0)
	{
		print_error ("Print mutex destroy error.");
		ret ++;
	}
	if (pthread_mutex_destroy(&env->mtx_dead) != 0)
	{
		print_error ("Pthread status check mutex destroy error.");
		ret ++;
	}
	if (env->eat_count >= 0)
	{
		if (pthread_mutex_destroy(&env->mtx_eat_philos) != 0)
		{
			print_error ("Eat count check mutex destroy error.");
			ret ++;
		}
	}
	if (destroy_forks(env) != 0)
		ret ++; 
	if (type == 1)
		return (2);
	else
		return (ret);
}

// if error Destroy previously created mutexes 

int init_forkmtx(t_env *env)
{
	int i;

	i = 0;
	while (i < env->ph_num)
	{
		if (pthread_mutex_init(&env->mtx_forks[i], NULL) != 0)
		{
			print_error("Fork mutex init error.");
			return (i + 1);
		}
		if (pthread_mutex_init(&env->ph[i].mtx_last_eat, NULL) != 0)
		{
			print_error("last meal mutex init error.");
			return ( (i + 1) + PHILO_MAX);
		}
		if (pthread_mutex_init(&env->ph[i].mtx_status, NULL) != 0)
		{
			print_error("philo status mutex init error.");
			return ( (i + 1) + (PHILO_MAX * 2));
		}
		i ++;
	}
	return (0);
}

// if error Destroy previously created mutexes

int	init_mtx(t_env *env)
{
	if (pthread_mutex_init(&env->mtx_print, NULL) != 0)
	{
		print_error("Print mutex init error.");
		return (1);
	}
	if (pthread_mutex_init(&env->mtx_dead, NULL) != 0)
	{
		print_error("Thread status check mutex init error.");
		return (2);
	}
	if (env->eat_count > 0)
	{
		if (pthread_mutex_init(&env->mtx_eat_philos, NULL) != 0)
		{
			print_error("Eat count check mutex init error.");
			return (3);
		}
	}
	if (init_forkmtx(env) != 0)
		return (4);
	return (0);
}