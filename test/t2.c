#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *routine(void *arg)
{
	long long val = 0;
	int i = 0;

	usleep(100);
	val = *(int *)arg;
	while (i < 90000)
	{
		val = val + 1;
		//printf("%d value : %lld \n",i, val);
		usleep(10);
		i ++;
	}
	arg = (void *)val;
	return (arg);
}

int main (void)
{
	pthread_t th[3];
	int val1 = 12;
	int val2 = 11;
	long long ret1, ret2, ret3;

	pthread_create(&th[0], NULL, &routine, (void *)&val1);
	pthread_create(&th[1], NULL, &routine, (void *)&val1);
	pthread_create(&th[2], NULL, &routine, (void *)&val1);

	pthread_join(th[0], (void *)&ret1);
	pthread_join(th[1], (void *)&ret2);
	pthread_join(th[2], (void *)&ret3);

	if (ret1 == ret2 && ret2 == ret3)
		printf("Same\n");
	else
		printf("NOT\n");
	return (0);
}