#include "libphilo.h"

static void	*threadfunc(void *arg)
{
	char *s;

	s = (char *)arg;
	printf("%s\n", s);
	return ((void *) strlen(s));
}

int main(void)
{
	pthread_t t1;
	void	*res;

	if (pthread_create(&t1, NULL, threadfunc, "Hello World!") != 0)
	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
		err_exit("pthread_create() error.");
	if (pthread_join(t1, &res) != 0)
		err_exit("pthread_join() error.");
	printf("Thread returned %ld\n", (long)res);
	system("leaks ./philo");
	return (0);
}