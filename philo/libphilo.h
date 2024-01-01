#ifndef LIBPHILO_H
# define LIBPHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_input
{
	int 	philos;
	int 	t_die;
	int 	t_eat;
	int 	t_sleep;
	int 	min_eat;
} t_input;

/* main.c */

/* print_message.c */

void	print_message(char *str, int fd);

/* parse_and_store.c */

int parse(char **argv);
int store(char **argv, int type, t_input *input);

#endif