#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void routine(void *arg)
{
    (void)arg;
    printf("pid %d\n", getpid());
    printf("ppid %d\n", getppid());
}

int main (void)
{
    pthread_t th[2];
    int i = 0;

    while (i < 2)
    {
        pthread_create(&th[i], NULL, (void *)&routine, NULL);
        i ++;
    }
    i = 0;
    while (i < 2)
    {
        pthread_join(th[i], NULL);
        i ++;
    }
    printf("ppid %d\n", getppid());
    return (0);
}