#ifndef MULT_H
# define MULT_H

typedef struct s_th
{
	pthread_t 		*t;
	int 			index;
	pthread_mutex_t *mutex;
	int 		sleep_time;
	int 		eat_time;
	int  		life_time;
	long long 	start;
	long long   last_meal;
	int 		*dead;
} t_th;

typedef struct s_env
{
	pthread_t 	th[201];
	pthread_t 	health_checker;
	t_th		threads[201];
	pthread_mutex_t mutex;
	int 		ret[201];
	int 		count;
	int dead;

} t_env;

#endif