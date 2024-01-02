#include "libphilo.h"

void setup_philos(t_input *input)
{
	int i;

	i = 0;
	while (i < input->philos)
	{
		input->forks_arr[i] = 0;
		i ++;
	}
	i = 0;
	while (i < input->philos)
	{
		input->philo_arr[i].philo_id = i + 1;
		input->philo_arr[i].last_eat_time = 0;
		input->philo_arr[i].eat_times = 0;
		input->philo_arr[i].status = 0;
		input->philo_arr[i].t_die = input->t_die;
		input->philo_arr[i].t_eat = input->t_eat;
		input->philo_arr[i].t_sleep = input->t_sleep;
		input->philo_arr[i].min_eat = input->min_eat;
		input->philo_arr[i].philos = input->philos;
		if (i == input->philos - 1)
			input->philo_arr[i].fork_r = &input->forks_arr[0];
		else
			input->philo_arr[i].fork_r = &input->forks_arr[i];
		if (i == 0)
			input->philo_arr[i].fork_l = &input->forks_arr[input->philos - 1];
		else
			input->philo_arr[i].fork_l = &input->forks_arr[i - 1];
		i ++;
	}
}

long long get_mili_time(void)
{
	struct timeval	time;
	long long		militime;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	militime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (militime);

}

void *routine(void *arg)
{
	t_philo *philo;
	long long time;
	

	philo = (t_philo *)arg;
	time = get_mili_time();
	while (1)
	{
		time = get_mili_time();
		if (time < philo->last_eat_time + philo->t_die)
		{
			printf("%lld : Philo %d Eating\n",time, philo->philo_id); 
			usleep(philo->t_eat * 1000);
		}
		time = get_mili_time();
		philo->last_eat_time = time;
		if (time < philo->last_eat_time + philo->t_die)
		{
			printf("%lld : Philo %d Sleeping\n",time, philo->philo_id);
			usleep(philo->t_sleep * 1000);
		}
		time = get_mili_time();
		if (time >= philo->last_eat_time + philo->t_die)
			break;
	}
	return ((void *)0);
}

void init_threads(t_input *input)
{
	int i = 0;
	long long time;

	while (i < input->philos)
	{
		time = get_mili_time();
		input->philo_arr[i].start = time;
		printf("%lld : Philo %d Started\n", time, input->philo_arr[i].philo_id);
		if (pthread_create(&input->philo_arr[i].thread, NULL, routine, &input->philo_arr[i]) != 0)
			print_message("Pthread create error.", 2);
		i ++;
	}
	i = 0;
	while (i < input->philos)
	{
		if (pthread_join(input->philo_arr[i].thread, NULL) != 0)
			print_message("Pthread join error.", 2);
		i ++;
	}
}

void init(t_input *input)
{
	input->forks_arr = malloc(sizeof(int) * input->philos);
	input->philo_arr = malloc(sizeof(t_philo) * input->philos);
	setup_philos(input);
	init_threads(input);
}