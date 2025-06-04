/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:20:59 by hakader           #+#    #+#             */
/*   Updated: 2025/06/04 19:56:02 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	result;

	int (i), (sign);
	i = 0;
	sign = 1;
	result = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > INT_MAX || result < INT_MIN)
			return (fdprintf("Error:\n max int reached.\n", 2), 0);
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (str[i])
		return (fdprintf("Error: non digit argument", 2), 0);
	return ((int)(sign * result));
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	fdprintf(char *str, int fd)
{
	if (!str)
		return (0);
	if (write(fd, str, ft_strlen(str)) < 0)
		return (-1);
	return (ft_strlen(str));
}
