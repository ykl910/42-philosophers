/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:46:08 by kyang             #+#    #+#             */
/*   Updated: 2025/01/18 19:50:58 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	mutex_id;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread_id;
	t_fork		*first_fork;
	t_fork		*sec_fork;
	int			philo_id;
	long		nb_meals_eaten;
	long		last_eat_time;
	long		status;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_limit_meals;
	long			start_time;
	pthread_mutex_t	sim_mutex;
	long			simulation_running;
	long			nb_philo_full;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	print_mutex;
	long			all_threads_ready;
	t_fork			*fork;
	t_philo			*philo;
}	t_data;

// initiate data
long	check_input(int ac, char **av);
t_philo	*init_philo(t_data *data);
t_fork	*init_fork(t_data *data);
long	init_data(t_data *data, int ac, char **av);

// dinner thread
long	create_threads(t_data *data);
void	wait_all_threads(t_philo *philo);
long	eat(t_philo *philo);
long	sleep_and_think(t_philo *philo);
void	*dinner_routine(void *arg);
long	death_check(t_philo *philo);

// monitor thread
long	monitor_death(t_data *data);
long	monitor_full(t_data *data);
void	*monitor_routine(void *arg);

// helper
long	ft_atol(const char *str);
long	get_current_time(void);
void	long_setter(pthread_mutex_t *mutex, long *dest, long value);
long	long_getter(pthread_mutex_t *mutex, long *src);
void	long_incrementer(pthread_mutex_t *mutex, long *dest);
void	safe_print(t_philo *philo, char *string);
void	safe_sleep(long time, t_data *data);

#endif