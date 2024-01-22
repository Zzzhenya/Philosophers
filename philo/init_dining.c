#include "libphilo.h"

void pick_fork(t_philo *philo, char d)
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

void return_fork(t_philo *philo, char d)
{
	if (d == 'l')
	{
		*philo->ptr_lfork = 0;
		pthread_mutex_unlock(philo->ptr_mtx_lfork);
		//print(philo, "put down a fork");
	}
	else
	{
		*philo->ptr_rfork = 0;
		pthread_mutex_unlock(philo->ptr_mtx_rfork);
		//print(philo, "put down a fork");
	}

}

void update_meal_time(t_philo *philo)
{
	long long currtime;

	pthread_mutex_lock(&philo->mtx_last_eat);
	currtime = get_milli_time();
	philo->last_eat_time = currtime;
	pthread_mutex_unlock(&philo->mtx_last_eat);
}

void philo_eat(t_philo *philo)
{
	//if (philo->t_die > philo->t_eat + philo->t_sleep)
	if ((philo->id % 2))
	{

		pick_fork(philo, 'l');
		pick_fork(philo, 'r');
		update_meal_time(philo);
		print(philo, "is eating");
		custom_sleep(philo->eat_len);
		//usleep(philo->eat_len * 1000);
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
		//usleep(philo->eat_len * 1000);
		return_fork(philo, 'r');
		return_fork(philo, 'l');
	}
}

void philo_sleep(t_philo *philo)
{
	print(philo, "is sleeping");
	//usleep(philo->sleep_len * 1000);
	custom_sleep(philo->sleep_len);
}

void philo_think(t_philo *philo)
{
	print(philo, "is thinking");
	custom_sleep(1);
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo_think(philo);
	while (is_alive(philo))
	{
		philo_eat(philo);
		if (philo->eat_count > -1)
			philo->eat_count --;
		if (philo->eat_count == 0)
		{
			pthread_mutex_lock(&philo->mtx_status);
			*philo->status = 1;
			pthread_mutex_unlock(&philo->mtx_status);
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return ((void *)0);
}

int make_threads(t_env *env, int i, int ret)
{
	long long time;

	while (i < env->ph_num)
	{
		time = get_milli_time();
		//if (time <= 0)
		//	return ((void *)1);
		env->ph[i].start_time = time;
		//printf("Start time %lld\n", env->ph[i].start_time);
		env->ph[i].last_eat_time = time;
		if (pthread_create(&env->ph[i].thread, NULL, &routine, (void *)&env->ph[i]) != 0)
		{
			print_error("Pthread create error.");
			return (ret ++);
		}
		i ++;
	}
	if (pthread_create(&env->monitor, NULL, &checker, env) != 0)
	{
		print_error("Pthread create error for monitor.");
		return (ret ++);
	}
	return (ret);
}

int join_threads(t_env *env, int i, int ret)
{
	while (i < env->ph_num )
	{
		if (pthread_join(env->ph[i].thread, NULL) != 0)
		{
			print_error("Pthread join error.");
			return (ret ++);
		}
		i ++;
	}
	if (pthread_join(env->monitor, NULL) != 0)
	{
		print_error("Pthread join error for monitor.");
		return (ret ++);
	}
	return (ret);
}

int init_dining(t_env *env)
{
	//long long	time;
	//pthread_t	monitor;

	/*time = get_milli_time();
	if (time <= 0)
		return (1);*/
	if (make_threads(env, 0, 0) != 0)
		return (destroy_all(env, 1));
	if (join_threads(env, 0, 0) != 0)
		return (destroy_all(env, 1));
	return (destroy_all(env, 0) != 0);
}