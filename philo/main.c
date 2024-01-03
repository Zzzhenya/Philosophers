#include "libphilo.h"
/*
long i = 0;
pthread_mutex_t mutex;

static void	*threadfunc()
{
	int count = 0;
	
	while (count < 10)
	{
		pthread_mutex_lock(&mutex);
		printf("Message from thread: i:%ld\n", i ++);
		count ++;
		pthread_mutex_unlock(&mutex);
		usleep(1000);
	}
	printf("End...\n");
	return ((void *)i);
}

int main(void)
{
	pthread_t t1, t2;
	void	*res;

	pthread_mutex_init(&mutex, NULL);
	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
	if (pthread_create(&t1, NULL, threadfunc, NULL) != 0)
		err_exit("pthread_create() error.");
	if (pthread_create(&t2, NULL, threadfunc, NULL) != 0)
		err_exit("pthread_create() error.");
	if (pthread_join(t1, &res) != 0)
		err_exit("pthread_join() error.");
	if (pthread_join(t2, &res) != 0)
		err_exit("pthread_join() error.");
	pthread_mutex_destroy(&mutex);
	return (0);
}*/

void print_details(t_input *input)
{
	int i = 0;
	printf("Philos: %d\n", input->philos);
	printf("t_die: %d\n", input->t_die);
	printf("t_eat: %d\n", input->t_eat);
	printf("t_sleep: %d\n", input->t_sleep);
	if (input->min_eat)
		printf("min_eat: %d\n", input->min_eat);
	while (i < input->philos)
	{
		printf("\nPhilo %d\n", i);
		printf("Philo_id: %d\n", input->philo_arr[i].philo_id);
		printf("Thread: %ld\n", input->philo_arr[i].thread);
		printf("Last_eat: %lld\n", input->philo_arr[i].last_eat_time);
		//printf("Fork_l: @%p : %d\n", input->philo_arr[i].fork_l, *input->philo_arr[i].fork_l);
		//printf("Fork_r: @%p : %d\n", input->philo_arr[i].fork_r, *input->philo_arr[i].fork_r);
		i ++; 
	}
	i = 0;
	printf("Forks\n");
	while (i < input->philos)
	{
		printf("Fork %d: @%p : %d\n", i, &input->forks_arr[i], input->forks_arr[i]);
		i ++;
	}
}

int	main(int argc, char **argv)
{
	t_input	 *input;

	input = NULL;
	if (argc == 5 || argc == 6)
	{
		if (!parse(argv))
			return (1);
		input = malloc(sizeof(t_input));
		if (!input)
		{
			print_message("Malloc failed.", 2);
			return (1);
		}
		if (!store(argv, argc, input))
		{
			print_message("Values should be larger than 0.", 2);
			free (input);
			return (1);
		}
		init(input);
		//print_details(input);
		free (input);
	}
	else
		write(1, "Usage: #philo t_die t_eat t_sleep [min_eat_times]\n", 50);

	return (0);
}








