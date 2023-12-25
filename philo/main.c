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
	int 	s;

	s = pthread_create(&t1, NULL, threadfunc, "Hello World!");
	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
	if (s != 0)
		err_exit("pthread_create() error.");
	printf("This is the main func\n");
	s = pthread_join(t1, &res);
	if (s != 0)
		err_exit("pthread_join() error.");
	printf("Thread returned %ld\n", (long)res);
	return (0);
}