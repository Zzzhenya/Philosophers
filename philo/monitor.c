#include "libphilo.h"

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