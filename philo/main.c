/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:22:49 by hakader           #+#    #+#             */
/*   Updated: 2025/06/18 02:58:26 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo *philo;
	int i;

	init_args(ac, av, &philo);
	pthread_mutex_t	*forks = malloc(sizeof(pthread_mutex_t) * philo->args->num_philos);
	i = 0;
	while (i < philo->args->num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	init_philos(philo, forks);
	return (0);
}
