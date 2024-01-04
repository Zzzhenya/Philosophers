#ifndef LIBPHILO_H
# define LIBPHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4
# define AVAILABLE 0

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread;
	long long int		last_eat_time;
	int 			eat_times;
	int 			status;
	pthread_mutex_t 			*fork_l;
	pthread_mutex_t 			*fork_r;
	int 	t_die;
	int 	t_eat;
	int 	t_sleep;
	int 	min_eat;
	int philos;
	long long int start;
} t_philo;

typedef struct s_input
{
	int 	philos;
	int 	t_die;
	int 	t_eat;
	int 	t_sleep;
	int 	min_eat;
	pthread_mutex_t 	*mutex;
	t_philo	*philo_arr;
} t_input;

/* main.c */

/* print_message.c */

void	print_message(char *str, int fd);

/* parse_and_store.c */

int parse(char **argv);
int store(char **argv, int type, t_input *input);

/* init.c */
void init(t_input *input);

#endif