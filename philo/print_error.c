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

void	print_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0)
	{
		write (2, str, len);
		write (2, "\n", 1);
	}
	else
		write (2, "Error\n", 6);
}
