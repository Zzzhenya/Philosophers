/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:55:25 by sde-silv          #+#    #+#             */
/*   Updated: 2024/01/09 11:55:27 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

long long get_mili_time(void)
{
	struct timeval	time;
	long long		militime;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	militime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (militime);

}

void print(t_philo *philo, char *msg)
{
	long long currtime;

	pthread_mutex_lock(&philo->print);
	currtime = get_mili_time();
	printf("%lld %d %s\n", currtime - philo->start,  philo->philo_id, msg);
	pthread_mutex_unlock(&philo->print);
}

void setup_philos(t_input *input)
{
	int i;

	i = 0;
	while (i < input->philos)
	{
		input->philo_arr[i].philo_id = i + 1;
		input->philo_arr[i].last_eat_time = 0;
		input->philo_arr[i].eat_times = 0;
		//input->philo_arr[i].status = THINKING;
		input->philo_arr[i].t_die = input->t_die;
		input->philo_arr[i].t_eat = input->t_eat;
		input->philo_arr[i].t_sleep = input->t_sleep;
		input->philo_arr[i].min_eat = input->min_eat;
		input->philo_arr[i].philos = input->philos;
		//input->philo_arr[i].print = &input->printer;
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

void ft_sleep(size_t t)
{
	usleep (t * 1000);
}

void gotosleep(t_philo *philo)
{
	//long long currtime;

	//currtime = get_mili_time();
	if (philo->t_die > philo->t_eat + philo->t_sleep)
	{
		print(philo, "is sleeping");
		//printf("%lld philo %d is sleeping.\n", currtime - philo->start,  philo->philo_id);
		ft_sleep(philo->t_sleep);
	}
}

void think(t_philo *philo)
{
	//long long currtime;

	//currtime = get_mili_time();
	print(philo, "is thinking");
	//printf("%lld philo %d is thinking.\n", currtime - philo->start,  philo->philo_id);
	/*
	if (philo->t_die < philo->t_eat + philo->t_sleep)
		ft_sleep(philo->t_die);
	else
		ft_sleep(rand() % philo->t_die);*/
}

/* if philo id is odd philo picks left fork first, else philo picks right fork */

void *routine(void *arg)
{
	t_philo *philo;
	long long currtime;
	
	philo = (t_philo *)arg;
	currtime = get_mili_time();
	//philo->start = currtime;
	philo->last_eat_time = currtime;
	while (1)
	{
		currtime = get_mili_time();
		if (currtime >= philo->last_eat_time + philo->t_die)
		{
			//break;
			print(philo, "is dead					sjkfnasjfnasojfpsafjoasf");
			//pthread_detach(philo->thread);
			return ((void *)1);
		}
		eat(philo);
		gotosleep(philo);
		think(philo);
	}
	return ((void *)0);
}

// printf("philo %d is thinking. : %lld\n", philo->philo_id ,currtime - philo->start);

void init_threads(t_input *input)
{
	int			i;
	int			ret;
	long long currtime;

	i = 0;
	ret = 0;

	//pthread_mutex_init(&input->printer, NULL);
	while (i < input->philos)
	{
		pthread_mutex_init(&input->mutex[i], NULL);
		pthread_mutex_init(&input->philo_arr[i].print, NULL);
		i ++;
	}
	i = 0;
	while (i < input->philos)
	{
		currtime = get_mili_time();
		input->philo_arr[i].start = currtime;
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
		pthread_mutex_destroy(&input->philo_arr[i].print);
		/*if (ret > 0)
		{
			i = 0;
			while (i < input->philos)
			{
				pthread_detach(input->philo_arr[i].thread);
				i ++;
			}
			//free_all()
			exit(1);
		}*/
		i ++;
	}
	//pthread_mutex_destroy(&input->printer);
}

void	init(t_input *input)
{
	input->mutex = malloc(sizeof(pthread_mutex_t) * input->philos);
	input->philo_arr = malloc(sizeof(t_philo) * input->philos);
	setup_philos(input);
	init_threads(input);
}
