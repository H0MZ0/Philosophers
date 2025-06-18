/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:23:59 by hakader           #+#    #+#             */
/*   Updated: 2025/06/18 03:05:57 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#define true 1
#define false 0	

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>


typedef struct s_args
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_meals;
}	t_args;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	t_args	*args;
}	t_philo;

int		ft_atoi(const char *str);
void	put_error(char *message);
void	init_args(int ac, char **av, t_philo **philo);

#endif