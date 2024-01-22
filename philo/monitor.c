#include "libphilo.h"

void kill_all_threads(t_env *env)
{
	int i = 0;
	while (i < env->ph_num)
	{
		pthread_mutex_lock(&env->ph[i].mtx_status);
		*env->ph[i].status = 1;
		pthread_mutex_unlock(&env->ph[i].mtx_status);
		i ++;
	}
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
			pthread_mutex_lock(&env->ph[i].mtx_last_eat);
			time = get_milli_time();
			if (time >= env->ph[i].last_eat_time + env->life_len)
			{
				pthread_mutex_unlock(&env->ph[i].mtx_last_eat);
				print(&env->ph[i], "is dead");
				pthread_mutex_lock(&env->mtx_dead);
				env->dead = 1;
				pthread_mutex_unlock(&env->mtx_dead);
				kill_all_threads(env);
				return ((void *)1);
			}
			pthread_mutex_unlock(&env->ph[i].mtx_last_eat);
			i ++;
		}
	}
	return ((void *)0);
}