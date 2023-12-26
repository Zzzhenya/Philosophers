#include "libphilo.h"

long i = 0;

static void	*threadfunc()
{
	int count = 0;
	
	while (count < 10)
	{
		printf("Message from thread: i:%ld\n", i ++);
		count ++;
		usleep(1000);
	}
	printf("End...i: %ld\n", i);
	return ((void *)i);
}

int main(void)
{
	pthread_t t1, t2;
	void	*res;

	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
	if (pthread_create(&t1, NULL, threadfunc, NULL) != 0)
		err_exit("pthread_create() error.");
	if (pthread_create(&t2, NULL, threadfunc, NULL) != 0)
		err_exit("pthread_create() error.");
	if (pthread_join(t1, &res) != 0)
		err_exit("pthread_join() error.");
	printf("Thread t1 returned %ld\n", *(long *)res);
	if (pthread_join(t2, &res) != 0)
		err_exit("pthread_join() error.");
	printf("Thread t2 returned %ld\n", *(long *)res);
	return (0);
}