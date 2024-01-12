#include "libphilo.h"

void	print_details(t_input *input)
{
	int	i;

	i = 0;
	printf("Philos: %d\n", input->philos);
	printf("t_die: %d\n", input->t_die);
	printf("t_eat: %d\n", input->t_eat);
	printf("t_sleep: %d\n", input->t_sleep);
	if (input->min_eat)
		printf("min_eat: %d\n", input->min_eat);
	while (i < input->philos)
	{
		printf("\nPhilo %d\n", i);
		printf("Philo_id: %d\n", input->philo_arr[i].philo_id);
		printf("Last_eat: %lld\n", input->philo_arr[i].last_eat_time);
		i ++; 
	}
	i = 0;
	printf("Forks\n");
	while (i < input->philos)
	{
		printf("Fork %d: @%p\n", i, &input->mutex[i]);
		i ++;
	}
}