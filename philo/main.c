/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:22:49 by hakader           #+#    #+#             */
/*   Updated: 2025/06/19 14:02:51 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void sleep_ms(int ms)
{
	long long start = current_time();
	while (current_time() - start < ms)
		usleep(100);
}

void take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_action(philo, "has taken a fork");
}

void	init_data(t_data *data)
{
	int	i;
	int	n;

	n = data->args.num_philos;
	data->philos = malloc(sizeof(t_philo) * n);
	if (!data->philos)
		put_error("Malloc failed (philos)");
	data->forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!data->forks)
		put_error("Malloc failed (forks)");
	i = -1;
	while (++i < n)
		if (pthread_mutex_init(&data->forks[i], NULL) == -1)
			put_error("pthread_mutex_init failed");
	pthread_mutex_init(&data->print_mutex, NULL);
	i = -1;
	while (++i < n)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % n;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
	}
	data->stop = 0;
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		put_error("pthread_mutex_init failed (stop_mutex)");
}

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
		if (args->num_meals < 0)
			put_error("Invalid number of meals");
	}
}

long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", current_time() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	int should_stop;
	pthread_mutex_lock(&philo->data->stop_mutex);
	should_stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	while (!philo->data->stop)
	{
		print_action(philo, "is thinking");
		take_forks(philo);
		print_action(philo, "is eating");
		philo->last_meal_time = current_time();
		philo->meals_eaten++;
		sleep_ms(philo->data->args.time_to_eat);
		put_down_forks(philo);
		print_action(philo, "is sleeping");
		sleep_ms(philo->data->args.time_to_eat);
	}
	return NULL;
}

void *monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int i, done;
	while (!data->stop)
	{
		for (i = 0; i < data->args.num_philos; i++)
		{
			if (current_time() - data->philos[i].last_meal_time > data->args.time_to_die)
			{
				print_action(&data->philos[i], "died");
				data->stop = 1;
				break;
			}
		}
		if (data->args.num_meals > 0)
		{
			done = 1;
			for (i = 0; i < data->args.num_philos; i++)
				if (data->philos[i].meals_eaten < data->args.num_meals)
					done = 0;
			if (done)
				data->stop = 1;
		}
		usleep(1000);
	}
	return NULL;
}

int	main(int ac, char **av)
{
	int		i;
	t_data	data;

	init_args(ac, av, &data.args);
	init_data(&data);
	data.start_time = current_time();
	i = 0;
	while (i < data.args.num_philos)
	{
		if (pthread_create((pthread_t *)&data.philos[i].thread_id, NULL, philo_routine, &data.philos[i]) != 0)
			put_error("Failed to create thread");
		i++;
	}
	i = 0;
	while (i < data.args.num_philos)
		pthread_join(*(pthread_t *)&data.philos[i++].thread_id, NULL);
	return (0);
}
