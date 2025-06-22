/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:26:36 by hakader           #+#    #+#             */
/*   Updated: 2025/06/22 20:52:33 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	result;

	int (i), (sign);
	sign = 1;
	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result > 2147483647 || result * sign < 0)
			return (-1);
	}
	if (str[i])
		return (put_error("Invalid characters in number"), -1);
	return (sign * result);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void	put_error(char *message)
{
	write(2, "Error: ", 7);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(1);
}

void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_stop(philo->data) || !strcmp(msg, "died"))
		printf("%lld %d %s\n", current_time() - philo->data->start_time,
			philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->philos);
	free(data->forks);
}
