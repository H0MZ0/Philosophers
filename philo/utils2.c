/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:04:19 by hakader           #+#    #+#             */
/*   Updated: 2025/06/23 16:09:01 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_stop(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop)
		res = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	return (res);
}

void	sleep_ms(t_data *data, int ms)
{
	long long	start;

	start = current_time();
	while (current_time() - start < ms && !is_stop(data))
		usleep(1000);
}

void	take_forks(t_philo *philo)
{
	if (is_stop(philo->data))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo, "has taken a fork");
	}
	else
	{
		usleep(1000);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_action(philo, "has taken a fork");
	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}
