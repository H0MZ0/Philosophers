/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 02:09:36 by hakader           #+#    #+#             */
/*   Updated: 2025/06/18 02:42:28 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(int ac, char **av, t_philo **philo)
{
	if (ac < 5 || ac > 6)
		return (put_error("Invalid number of arguments"));
	*philo = malloc(sizeof(t_philo));
	if (!*philo)
		return (put_error("Memory allocation failed"));
	(*philo)->args = malloc(sizeof(t_args));
	if (!(*philo)->args)
		return (put_error("Memory allocation failed"));
	memset((*philo)->args, 0, sizeof(t_philo));
	(*philo)->args->num_philos = ft_atoi(av[1]);
	(*philo)->args->time_to_die = ft_atoi(av[2]);
	(*philo)->args->time_to_eat = ft_atoi(av[3]);
	(*philo)->args->time_to_sleep = ft_atoi(av[4]);
	if ((*philo)->args->num_philos < 1 || (*philo)->args->time_to_die < 1 ||
		(*philo)->args->time_to_eat < 1 || (*philo)->args->time_to_sleep < 1)
		put_error("Invalid argument values");
	if (ac == 6)
	{
		(*philo)->args->num_meals = ft_atoi(av[5]);
		if ((*philo)->args->num_meals < 0)
			put_error("Invalid number of meals");
		if ((*philo)->args->num_meals == 0)
			(*philo)->args->num_meals = -1;
	}
}

