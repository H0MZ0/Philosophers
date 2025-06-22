/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:27:31 by hakader           #+#    #+#             */
/*   Updated: 2025/06/22 20:27:45 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_die(t_data *data, int i)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (!data->stop)
		data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	print_action(&data->philos[i], "died");
	return (NULL);
}

void	*set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	return (NULL);
}

void	get_meal(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].meal_mutex);
	data->time_since_meal = current_time() - data->philos[i].last_meal_time;
	data->meals = data->philos[i].meals_eaten;
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
}
