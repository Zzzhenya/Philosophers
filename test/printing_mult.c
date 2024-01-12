#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mult.h"

/* get time and print from multiple threads 
*/

long long get_mili_time(void)
{
	struct timeval	time;
	long long		militime;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	militime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (militime);

}

void print_status(long long time, t_th th, int status)
{
	if (pthread_mutex_lock(th.mutex) != 0)
			printf("Print mutex lock error\n");
	if (status == 't')
		printf("%lld %d is thinking\n", time, th.index);
	else if (status == 'd')
		printf("%lld %d is dead\n", time, th.index);
	else if (status == 'o')
		printf("%lld %d is alive\n", time, th.index);
	if (pthread_mutex_unlock(th.mutex) != 0)
			printf("Print mutex unlock error\n");
}

void philo_think(t_th th)
{
	long long time;

	time = get_mili_time();
	if (time < 0)
		printf("Time error");
	print_status(time, th, 't');
}

void routine(void *arg)
{
	t_th th;
	long long time;

	th = *(t_th *)arg;
	time = get_mili_time();
	if (time < 0)
		printf("Time error");
	th.start = time;
	th.last_meal = time;
	while (1)
	{
		/*if (th.index == 6)
			printf("STATUS : %d\n", *th.dead);*/
		time = get_mili_time();
		if (time < 0)
			printf("Time error");
		if (time >= th.last_meal + th.life_time)
		{
			print_status(time, th, 'd');
			*th.dead = 1;
			//killallthreads();
		}
		//philo_eat(th);
		//philo_sleep(th);
		philo_think(th);
		if (th.index % 2)
			usleep(10000);
		else
			usleep(1000000);
		time = get_mili_time();
		if (time < 0)
			printf("Time error");
		else
			print_status(time, th, 'o');
	}
}

void	*health(void *arg)
{
	t_env checker;
	checker = *(t_env *)arg;

	while (1)
	{
		printf("	STatus : %d\n", checker.dead);
	}
	return ((void *)0);
}

int main(void)
{
	int i = 0;
	int count = 10;
	int sleep = 100;
	int eat = 200;
	int life = 800;
	int ret = 0;
	t_env env;

	env.count = count;
	while (i < count)
	{
		env.threads[i].index = i + 1;
		env.threads[i].t = &env.th[i];
		env.threads[i].mutex = &env.mutex;
		env.threads[i].eat_time = eat;
		env.threads[i].sleep_time = sleep;
		env.threads[i].life_time = life;
		env.threads[i].dead = &env.dead;
		env.ret[i]=0;
		i ++;
	}
	i = 0;
	pthread_mutex_init(&env.mutex, NULL);

	if (pthread_create(&env.health_checker, NULL, (void *)health, (void *)&env) != 0)
		return (printf("Pthread create error\n"));
	while (i < count)
	{
		if (pthread_create(&env.th[i], NULL, (void *)routine, (void *)&env.threads[i]) != 0)
			return (printf("Pthread create error\n"));
		i ++;
	}
	if (pthread_join(env.health_checker, (void *)(void *)&ret) != 0)
			return (printf("Pthread join error\n"));
	if (ret)
	{
		printf("RET %d\n", ret);
		return (1);
	}
	
	i = 0;
	while (i < count)
	{
		if (pthread_join(env.th[i], (void *)&env.ret[i]) != 0)
			return (printf("Pthread join error\n"));
		i ++;
	}
	return (0);
}