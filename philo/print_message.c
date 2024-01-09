/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:55:49 by sde-silv          #+#    #+#             */
/*   Updated: 2024/01/09 11:55:50 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len])
		len ++;
	return (len);
}

void	print_message(char *str, int fd)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0)
	{
		write (fd, str, len);
		write (fd, "\n", 1);
	}
	else
		write (2, "Error\n", 6);
}
