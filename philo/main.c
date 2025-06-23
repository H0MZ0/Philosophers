/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:22:49 by hakader           #+#    #+#             */
/*   Updated: 2025/06/23 16:04:55 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	main_helper(t_data data)
{
	int	i;

	i = 0;
	while (i < data.args.num_philos)
	{
		pthread_mutex_lock(&data.philos[i].meal_mutex);
		data.philos[i].last_meal_time = data.start_time;
		pthread_mutex_unlock(&data.philos[i].meal_mutex);
		i++;
	}
	i = 0;
	while (i < data.args.num_philos)
	{
		if (pthread_create(&data.philos[i].thread_id,
				NULL, philo_routine, &data.philos[i]) != 0)
			put_error("Failed to create thread");
		i++;
	}
}

int	main(int ac, char **av)
{
	int			i;
	t_data		data;
	pthread_t	monitor_thread;

	init_args(ac, av, &data.args);
	init_data(&data);
	data.start_time = current_time();
	main_helper(data);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, &data) != 0)
		put_error("Failed to create monitor thread");
	i = 0;
	while (i < data.args.num_philos)
		pthread_join(data.philos[i++].thread_id, NULL);
	pthread_join(monitor_thread, NULL);
	cleanup(&data);
	return (0);
}
