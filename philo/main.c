/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:56:18 by hakader           #+#    #+#             */
/*   Updated: 2025/06/03 18:10:15 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	(void)av;
	t_philo	*philosophers;
	if (ac < 5 || ac > 6)
	{
		fdprintf("Error: Invalid number of arguments.\n", 2);
		return (1);
	}
	philosophers = malloc(sizeof(t_philo) * (ac - 1));
	if (!philosophers)
	{
		fdprintf("Error: Memory allocation failed.\n", 2);
		return (1);
	}
	memset(philosophers, 0, sizeof(t_philo) * (ac - 1));
	printf("Philosophers initialized successfully.\n");
	return (0);
}
