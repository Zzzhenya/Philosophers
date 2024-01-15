#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define PHILO_MAX 201

typedef struct s_philo
{
	pthread_t 			thread;
	int 				ph_num;
	int 				id;
	int 				eat_time;
	int 				sleep_time;
	int 				life_time;
	long long			start;
	long long 			last_eat_time;
	int 				*dead;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	pthread_mutex_t		*mtx_print;
	pthread_mutex_t		*mtx_dead;
	pthread_mutex_t		mtx_last_meal;
	
} t_philo;

typedef struct s_env
{
	int 				ph_num;
	int 				dead;
	int 				eat_time;
	int 				sleep_time;
	int 				life_time;
	pthread_t 			monitor;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mtx_print;
	pthread_mutex_t		mtx_dead;
	t_philo				*ph;
} t_env;

#endif