#include "libphilo.h"

static void	*threadfunc(void *arg)
{
	long *s;

	s = (long *)arg;
	printf("Message from t%ld\n", *s);
	sleep(1);
	printf("End...t%ld\n", *s);
	return ((void *)s);
}

int main(void)
{
	pthread_t t1, t2;
	void	*res;
	long val1 = 1;
	long val2 = 2;

	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
	if (pthread_create(&t1, NULL, threadfunc, &val1) != 0)
		err_exit("pthread_create() error.");
	if (pthread_create(&t2, NULL, threadfunc, &val2) != 0)
		err_exit("pthread_create() error.");
	if (pthread_join(t1, &res) != 0)
		err_exit("pthread_join() error.");
	printf("Thread t1 returned %ld\n", *(long *)res);
	if (pthread_join(t2, &res) != 0)
		err_exit("pthread_join() error.");
	printf("Thread t2 returned %ld\n", *(long *)res);
	return (0);
}