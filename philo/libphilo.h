#ifndef LIBPHILO_H
# define LIBPHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include "errors.h"

typedef struct s_input
{
	int 	philos;
	int 	t_die;
	int 	t_eat;
	int 	t_sleep;
	int 	min_eat;
} t_input;
/* main.c */

#endif