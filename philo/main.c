/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:55:33 by sde-silv          #+#    #+#             */
/*   Updated: 2024/01/09 11:55:35 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	main(int argc, char **argv)
{
	t_input	input;

	if (argc == 5 || argc == 6)
	{
		if (!parse(argv))
			return (1);
		if (!store(argv, argc, &input))
		{
			print_message("Values should be larger than 0.", 2);
			return (1);
		}
		init(&input);
		//print_details(input);
	}
	else
		write(1, "Usage: #philo t_die t_eat t_sleep [min_eat_times]\n", 50);
	return (0);
}
