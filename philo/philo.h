/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:23:59 by hakader           #+#    #+#             */
/*   Updated: 2025/06/19 19:01:19 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_meals;
}	t_args;

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long			last_meal_time;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	t_args			args;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	long long		start_time;
	int				stop;
	pthread_mutex_t stop_mutex;
}	t_data;

long long	current_time(void);
void	print_action(t_philo *philo, char *msg);
int		ft_atoi(const char *str);
void	put_error(char *message);
void	init_data(t_data *data);
void	init_args(int ac, char **av, t_args *args);

#endif