#include "philo.h"

/*4 Philosophers and 4 forks*/

void    setup_env(int n, int life, int eat, int sleep, t_env *env)
{
    env->ph_num = n;
    env->dead = 0;
    env->eat_time = eat;
    env->sleep_time = sleep;
    env->life_time = life;
}

void    setup_philos(t_env *env)
{
    int i = 0;

    while (i < env->ph_num)
    {
        env->ph[i].ph_num = env->ph_num;
        env->ph[i].id = i + 1;
        env->ph[i].eat_time = env->eat_time;
        env->ph[i].sleep_time = env->sleep_time;
        env->ph[i].life_time = env->life_time;
        env->ph[i].start = 0;
        env->ph[i].last_eat_time = 0;
        env->ph[i].dead = &env->dead;
        env->ph[i].mtx_print = &env->mtx_print;
        env->ph[i].mtx_dead = &env->mtx_dead;
        i ++;
    }
}

void    setup_forks(t_env *env)
{
    int i = 0;

    while (i < env->ph_num)
    {
        if (i == 0)
            env->ph[i].lfork = &env->forks[env->ph_num - 1];
        else
            env->ph[i].lfork = &env->forks[i - 1];
        if (i == env->ph_num - 1)
            env->ph[i].rfork = &env->forks[0];
        else
            env->ph[i].rfork = &env->forks[i];
        i ++;
    }
}

void init_mtx(t_env *env)
{
    int i = 0;

    pthread_mutex_init(&env->mtx_dead, NULL);
    pthread_mutex_init(&env->mtx_print, NULL);
    while (i < env->ph_num)
    {
        pthread_mutex_init(&env->forks[i], NULL);
        pthread_mutex_init(&env->ph[i].mtx_last_meal, NULL);
        i ++;
    }
}

void    *monitor(void *arg)
{
    t_env   *env;
    int i = 0;

    env = (t_env *)arg;
    while (1)
    {
        i = 0;
        while (i < env->ph_num)
        {
            pthread_mutex_lock(&env->ph[i].mtx_last_meal);
            if (env->ph[i].last_eat_time == 10)
            {
                printf("meal count %lld completed\n", env->ph[i].last_eat_time);
                pthread_mutex_unlock(&env->ph[i].mtx_last_meal);
                return (arg);
            }
            pthread_mutex_unlock(&env->ph[i].mtx_last_meal);
            i ++;
        }
    }
    return (arg);
}

int all_alive(t_philo *philo)
{
    pthread_mutex_lock(philo->mtx_dead);
    if (*philo->dead == 0)
    {
        pthread_mutex_unlock(philo->mtx_dead);
        return (1);
    }
    else
    {
        pthread_mutex_unlock(philo->mtx_dead);
        return (0);
    }
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        pthread_mutex_lock(&philo->mtx_last_meal);
        if (all_alive(philo))
            printf("%d: %lld  Hello World\n",philo->id, philo->last_eat_time);
        else
            break;
        philo->last_eat_time ++;
        if (philo->last_eat_time == 10)
        {
            pthread_mutex_lock(philo->mtx_dead);
            *philo->dead = 1;
            pthread_mutex_unlock(philo->mtx_dead); 
        }
        pthread_mutex_unlock(&philo->mtx_last_meal);
        sleep(1);
    }
    return ((void *)1);
}

void init_threads(t_env *env)
{
    int i = 0;
    int ret;

    pthread_create(&env->monitor, NULL, (void *)&monitor, env);
    while (i < env->ph_num)
    {
        pthread_create(&env->ph[i].thread, NULL, (void *)&routine, &env->ph[i]);
        i ++;
    }
    pthread_join(env->monitor, (void **)&ret);
    //if (ret)
    //    return ;
    i = 0;
    while (i < env->ph_num)
    {
        pthread_join(env->ph[i].thread, NULL);
        i ++;
    }
}

void destroy_mtx(t_env *env)
{
    int i = 0;

    pthread_mutex_destroy(&env->mtx_print);
    pthread_mutex_destroy(&env->mtx_dead);
    while (i < env->ph_num)
    {
        pthread_mutex_destroy(&env->forks[i]);
        pthread_mutex_destroy(&env->ph[i].mtx_last_meal);
        i ++;
    }
}

int main (void)
{
    t_philo             philo_arr[PHILO_MAX];
    pthread_mutex_t     mtx_arr[PHILO_MAX];
    t_env               env;

    setup_env(4, 410, 200, 100, &env);
    env.ph = philo_arr;
    env.forks = mtx_arr;
    setup_philos(&env);
    setup_forks(&env);
    init_mtx(&env);
    init_threads(&env);
    destroy_mtx(&env);
    return (0);
}