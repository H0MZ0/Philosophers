/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 02:09:36 by hakader           #+#    #+#             */
/*   Updated: 2025/06/22 19:11:19 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(int ac, char **av, t_args *args)
{
	if (ac < 5 || ac > 6)
		put_error("Invalid number of arguments");
	args->num_philos = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (args->num_philos < 1 || args->time_to_die < 1
		|| args->time_to_eat < 1 || args->time_to_sleep < 1)
		put_error("Invalid argument values");
	args->num_meals = -1;
	if (ac == 6)
	{
		args->num_meals = ft_atoi(av[5]);
		if (args->num_meals <= 0)
			put_error("Invalid number of meals");
	}
}

void	init_data(t_data *data)
{
	int (i), (n);
	n = data->args.num_philos;
	data->philos = malloc(sizeof(t_philo) * n);
	data->forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!data->philos || !data->forks)
		put_error("Malloc failed)");
	i = -1;
	while (++i < n)
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			put_error("pthread_mutex_init failed");
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	i = -1;
	while (++i < n)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % n;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
	}
	data->stop = 0;
	pthread_barrier_init(&data->start_barrier, NULL, data->args.num_philos + 1);
}
