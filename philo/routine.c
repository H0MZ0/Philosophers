/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:02:04 by hakader           #+#    #+#             */
/*   Updated: 2025/06/23 16:05:58 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	print_action(philo, "has taken a fork");
	sleep_ms(philo->data, philo->data->args.time_to_die);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->args.num_philos == 1)
		return (one_philo(philo), NULL);
	while (!is_stop(philo->data))
	{
		print_action(philo, "is thinking");
		take_forks(philo);
		print_action(philo, "is eating");
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal_time = current_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		sleep_ms(philo->data, philo->data->args.time_to_eat);
		put_down_forks(philo);
		print_action(philo, "is sleeping");
		sleep_ms(philo->data, philo->data->args.time_to_sleep);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data		*data;

	data = (t_data *)arg;
	int (i), (done);
	while (1)
	{
		done = 1;
		i = 0;
		while (i < data->args.num_philos)
		{
			get_meal(data, i);
			if (is_stop(data))
				return (NULL);
			if (data->time_since_meal > data->args.time_to_die)
				return (check_die(data, i));
			if (data->args.num_meals > 0 && data->meals < data->args.num_meals)
				done = 0;
			i++;
		}
		if (data->args.num_meals > 0 && done)
			return (set_stop(data));
	}
	return (NULL);
}
