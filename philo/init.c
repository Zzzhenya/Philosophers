#include "libphilo.h"

void setup_philos(t_input *input)
{
	int i;

	i = 0;
	while (i < input->philos)
	{
		input->philo_arr[i].philo_id = i + 1;
		input->philo_arr[i].last_eat_time = 0;
		input->philo_arr[i].eat_times = 0;
		input->philo_arr[i].status = THINKING;
		input->philo_arr[i].t_die = input->t_die;
		input->philo_arr[i].t_eat = input->t_eat;
		input->philo_arr[i].t_sleep = input->t_sleep;
		input->philo_arr[i].min_eat = input->min_eat;
		input->philo_arr[i].philos = input->philos;
		if (i == input->philos - 1)
			input->philo_arr[i].fork_r = &input->mutex[0];
		else
			input->philo_arr[i].fork_r = &input->mutex[i];
		if (i == 0)
			input->philo_arr[i].fork_l = &input->mutex[input->philos - 1];
		else
			input->philo_arr[i].fork_l = &input->mutex[i - 1];
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

void ft_sleep(size_t t)
{
	usleep (t * 1000);
}

void pick_fork(t_philo *philo, char d)
{
	long long currtime;

	currtime = get_mili_time();
	if (d == 'l')
	{
		pthread_mutex_lock(philo->fork_l);
			printf("philo %d picked l fork. : %lld\n", philo->philo_id , currtime - philo->start);
	}
	else
	{
		pthread_mutex_lock(philo->fork_r);
			printf("philo %d picked r fork. : %lld\n", philo->philo_id ,currtime - philo->start);
	}
}

void return_fork(t_philo *philo, char d)
{
	long long currtime;

	currtime = get_mili_time();
	if (d == 'l')
	{
		pthread_mutex_unlock(philo->fork_l);
			printf("philo %d put down l fork. : %lld\n", philo->philo_id ,currtime - philo->start);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_r);
			printf("philo %d put down r fork. : %lld\n", philo->philo_id ,currtime - philo->start);
	}

}

/* if philo id is odd philo picks left fork first, else philo picks right fork */

void *routine(void *arg)
{
	t_philo *philo;
	long long currtime;
	
	philo = (t_philo *)arg;
	currtime = get_mili_time();
	philo->start = currtime;
	philo->last_eat_time = currtime;
	while (1)
	{
		if (philo->philo_id % 2 != 0)
		{
			pick_fork(philo, 'l');
			pick_fork(philo, 'r');
			currtime = get_mili_time();
			philo->last_eat_time = currtime;
			ft_sleep(philo->t_eat);
			return_fork(philo, 'l');
			return_fork(philo, 'r');
		}
		else
		{
			pick_fork(philo, 'r');
			pick_fork(philo, 'l');
			currtime = get_mili_time();
			philo->last_eat_time = currtime;
			ft_sleep(philo->t_eat);
			currtime = get_mili_time();
			return_fork(philo, 'r');
			return_fork(philo, 'l');
		}
	}
	return ((void *)0);
}

// printf("philo %d is thinking. : %lld\n", philo->philo_id ,currtime - philo->start);

void init_threads(t_input *input)
{
	int			i;
	int			ret;

	i = 0;
	ret = 0;

	while (i < input->philos)
	{
		pthread_mutex_init(&input->mutex[i], NULL);
		if (pthread_create(&input->philo_arr[i].thread, NULL, routine, &input->philo_arr[i]) != 0)
			print_message("Pthread create error.", 2);
		i ++;
	}
	i = 0;
	while (i < input->philos)
	{
		if (pthread_join(input->philo_arr[i].thread, (void **)&ret) != 0)
			print_message("Pthread join error.", 2);
		pthread_mutex_destroy(&input->mutex[i]);
		if (ret > 0)
		{
			//free_all()
			exit(1);
		}
		i ++;
	}
}

void init(t_input *input)
{
	input->mutex = malloc(sizeof(pthread_mutex_t) * input->philos);
	input->philo_arr = malloc(sizeof(t_philo) * input->philos);
	setup_philos(input);
	init_threads(input);
}