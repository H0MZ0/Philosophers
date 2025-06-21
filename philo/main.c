/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:22:49 by hakader           #+#    #+#             */
/*   Updated: 2025/06/21 18:37:07 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void sleep_ms(int ms)
{
	int start = current_time();
	while (current_time() - start < ms)
		usleep(1000);
}

void take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_action(philo, "has taken a fork");
	}
}

void put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->stop || !strcmp(msg, "died"))
		printf("%d %d %s\n", current_time() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int current_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_action(philo, "has taken a fork");
	sleep_ms(philo->data->args.time_to_die);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void init_data(t_data *data)
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
}

void init_args(int ac, char **av, t_args *args)
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

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->data->args.num_philos == 1)
		return (one_philo(philo), NULL);
	while (1)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		int stop = philo->data->stop;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		if (stop)
			break;
		pthread_mutex_lock(&philo->meal_mutex);
		if (philo->data->args.num_meals > 0 &&
			philo->meals_eaten >= philo->data->args.num_meals)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		print_action(philo, "is thinking");
		take_forks(philo);
		print_action(philo, "is eating");
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal_time = current_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		sleep_ms(philo->data->args.time_to_eat);
		put_down_forks(philo);
		print_action(philo, "is sleeping");
		sleep_ms(philo->data->args.time_to_sleep);
	}
	return NULL;
}

void *monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int	i;
	int	done;

	while (1)
	{
		usleep(1000);
		done = 1;
		i = 0;
		while (i < data->args.num_philos)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			long long time_since_meal = current_time() - data->philos[i].last_meal_time;
			int meals = data->philos[i].meals_eaten;
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			pthread_mutex_lock(&data->stop_mutex);
			int stop = data->stop;
			pthread_mutex_unlock(&data->stop_mutex);
			if (stop)
				return (NULL);
			if (time_since_meal > data->args.time_to_die)
			{
				if (!data->stop)
					data->stop = 1;
				pthread_mutex_lock(&data->stop_mutex);
				print_action(&data->philos[i], "died");
				pthread_mutex_unlock(&data->stop_mutex);
				return (NULL);
			}
			if (data->args.num_meals > 0 && meals < data->args.num_meals)
				done = 0;
			i++;
		}
		if (data->args.num_meals > 0 && done)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (NULL);
		}
	}
	return (NULL);
}

int main(int ac, char **av)
{
	int			i;
	t_data		data;
	pthread_t	monitor_thread;

	init_args(ac, av, &data.args);
	init_data(&data);

	data.start_time = current_time();
	for (i = 0; i < data.args.num_philos; i++)
	{
		pthread_mutex_lock(&data.philos[i].meal_mutex);
		data.philos[i].last_meal_time = data.start_time;
		pthread_mutex_unlock(&data.philos[i].meal_mutex);
	}

	i = 0;
	while (i < data.args.num_philos)
	{
		if (pthread_create(&data.philos[i].thread_id, NULL, philo_routine, &data.philos[i]) != 0)
			put_error("Failed to create thread");
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, &data) != 0)
		put_error("Failed to create monitor thread");

	i = 0;
	while (i < data.args.num_philos)
		pthread_join(data.philos[i++].thread_id, NULL);
	pthread_join(monitor_thread, NULL);

	cleanup(&data);
	return (0);
}
