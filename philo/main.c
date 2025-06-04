/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:56:18 by hakader           #+#    #+#             */
/*   Updated: 2025/06/04 19:55:03 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*init_philosophers(int ac, char **av)
{
	t_philo	*philosophers;
	int		i;

	philosophers = malloc(sizeof(t_philo) * (ac - 1));
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < ac - 1)
	{
		philosophers[i].id = i + 1;
		philosophers[i].time_to_die = ft_atoi(av[1]);
		philosophers[i].time_to_eat = ft_atoi(av[2]);
		philosophers[i].time_to_sleep = ft_atoi(av[3]);
		if (ac == 6)
			philosophers[i].num_of_meals = ft_atoi(av[4]);
		else
			philosophers[i].num_of_meals = -1; // Infinite meals
		i++;
	}
	return (philosophers);
}

int	main(int ac, char **av)
{
	t_philo	*philosophers;

	(void)av;
	if (ac < 5 || ac > 6)
		return (fdprintf("Error: Invalid number of arguments.\n", 2), 1);
	if (check_nums(&av[1]))
		return (fdprintf("Error: non digit argument.\n", 2), 1);
	philosophers = init_philosophers(ac, av);
	if (!philosophers)
		return (fdprintf("Error: Memory allocation failed.\n", 2), 1);
	return (0);
}
