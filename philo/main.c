#include "libphilo.h"

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
}