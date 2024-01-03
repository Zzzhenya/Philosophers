#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int glob = 0;

static void incr(void *arg)
{
    int loc, j;
    int loops = 5;
    pthread_mutex_t *mutex;

    mutex = (pthread_mutex_t *)arg;
    while (j < loops)
    for (j = 0; j < loops; j ++)
    {
        sleep(1);
        pthread_mutex_lock(mutex);
        loc = glob;
        loc ++;
        glob = loc;
        printf("%d: glob %d loc %d\n", j, glob, loc);
        pthread_mutex_unlock(mutex);
    }
}

int main (int argc, char **argv)
{
    int thread_c = 0;
    int i = 0;
    pthread_t th[10];
    pthread_mutex_t m[10];

    if (argc != 2)
        return (0);
    thread_c = atoi(argv[1]);
    if (thread_c > 0 && thread_c <= 10)
    {
        while (i < thread_c) 
        {
            if (pthread_mutex_init(&m[i], NULL) != 0)
                printf("Mutex %d init error\n", i);
            if (pthread_create(&th[i], NULL, (void *)incr, (void *)&m[i]) != 0)
            {
                printf("Pthread create error\n");
                return (1);
            }
            i ++;
        }
        i = 0;
        while (i < thread_c)
        {
            if (pthread_join(th[i], NULL) != 0)
            {
                printf("Pthread join error\n");
                return (2);
            }
            if (pthread_mutex_destroy(&m[i]) != 0)
            {
                printf("Pthread mutex destroy error\n");
            }
            i ++;
        }
    }
    return (0);
}