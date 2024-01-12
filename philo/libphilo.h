/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:56:07 by sde-silv          #+#    #+#             */
/*   Updated: 2024/01/09 11:56:09 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPHILO_H
# define LIBPHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define PHILO_MAX 201
/*# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4
# define AVAILABLE 0*/

typedef struct s_philo
{
	pthread_t 			thread;
	int 				id;
	int 				eat_time;
	int 				sleep_time;
	int 				life_time;
	int 				min_eat;
	long long			start;
	long long 			last_eat_time;
	int 				*dead;
	int 				*all_eat;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	pthread_mutex_t		*mtx_print;
	pthread_mutex_t		*mtx_dead;
	pthread_mutex_t		*mtx_ecount;
	
} t_philo;

typedef struct s_env
{
	int 				ph_num;
	int 				dead;
	int 				eat_time;
	int 				sleep_time;
	int 				life_time;
	int 				min_eat;
	int 				all_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mtx_print;
	pthread_mutex_t		mtx_dead;
	pthread_mutex_t		mtx_ecount;
	t_philo				*ph;
} t_env;

/* main.c */

/* input_check.c */

int			bad_input(char **argv);
int			ft_atoi(const char *nptr);

/* init_struct.c */

void		init_struct(t_env *env, int argc, char **argv);

/* init_dining.c */

int 		init_dining(t_env *env);
void 		*routine(void *arg);
void 		print(t_philo *philo, char *msg);

/* mtx_actions.c */

int			init_mtx(t_env *env);
int 		destroy_all(t_env *env, int type);

/* print_message.c */

void		print_error(char *str);

/* get_milli_time.c */

long long 	get_milli_time(void);

#endif
