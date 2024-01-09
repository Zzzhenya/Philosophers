#include "libphilo.h"

void pick_fork(t_philo *philo, char d)
{
	//long long currtime;

	//currtime = get_mili_time();
	if (d == 'l')
	{
		pthread_mutex_lock(philo->fork_l);
		print(philo, "picked a fork");
		//currtime = get_mili_time();
		//printf("%lld %d picked l fork.\n", currtime - philo->start, philo->philo_id);
	}
	else
	{
		pthread_mutex_lock(philo->fork_r);
		print(philo, "picked a fork");
		//currtime = get_mili_time();
		//printf("%lld %d picked r fork.\n", currtime - philo->start, philo->philo_id);
	}
}

void return_fork(t_philo *philo, char d)
{
	/*long long currtime;

	currtime = get_mili_time();*/
	if (d == 'l')
	{
		pthread_mutex_unlock(philo->fork_l);
		//currtime = get_mili_time();
		print(philo, "put down a fork");
	}
	else
	{
		pthread_mutex_unlock(philo->fork_r);
		//currtime = get_mili_time();
		print(philo, "put down a fork");
	}

}

void eat(t_philo *philo)
{
	long long currtime;

	if (philo->t_die > philo->t_eat + philo->t_sleep)
	{
		//if (philo->philo_id % 2 != 0)
		{

			pick_fork(philo, 'l');
			pick_fork(philo, 'r');
			print(philo, "is eating");
			ft_sleep(philo->t_eat);
			currtime = get_mili_time();
			philo->last_eat_time = currtime;
			return_fork(philo, 'l');
			return_fork(philo, 'r');
		}
		/*else
		{
			pick_fork(philo, 'r');
			pick_fork(philo, 'l');
			print(philo, "is eating");
			ft_sleep(philo->t_eat);
			currtime = get_mili_time();
			philo->last_eat_time = currtime;
			return_fork(philo, 'r');
			return_fork(philo, 'l');
		}*/
	}

}