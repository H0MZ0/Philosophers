/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:54:57 by hakader           #+#    #+#             */
/*   Updated: 2025/06/23 16:05:46 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_meals;
}	t_args;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	long long		last_meal_time;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread_id;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	t_args				args;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		access_mutex;
	int					stop;
	long long			start_time;
	int					time_since_meal;
	int					meals;
}	t_data;

// Utility functions
int			ft_atoi(const char *str);
void		put_error(char *msg);
long long	current_time(void);
void		print_action(t_philo *philo, char *msg);
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);
void		init_args(int ac, char **av, t_args *args);
void		init_data(t_data *data);
void		cleanup(t_data *data);
void		put_down_forks(t_philo *philo);
void		sleep_ms(t_data *data, int ms);
void		one_philo(t_philo *philo);
void		take_forks(t_philo *philo);
int			is_stop(t_data *data);
void		*check_die(t_data *data, int i);
void		*set_stop(t_data *data);
void		get_meal(t_data *data, int i);

#endif