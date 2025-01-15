/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:46:08 by kyang             #+#    #+#             */
/*   Updated: 2025/01/15 16:26:43 by kyang            ###   ########.fr       */
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

typedef struct s_data t_data;

typedef struct s_fork
{
	pthread_mutex_t	mutex_id;
	int				fork_id;
	//int				status;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread_id; 
	t_fork		*first_fork;
	t_fork		*sec_fork;
	int			philo_id;
	long		nb_meals_eaten;
	long 		last_eat_time;
	long		status;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	long	nb_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_limit_meals;
	long	start_time;
	pthread_mutex_t	sim_mutex;
	int		simulation_running;
	long	nb_philo_full;
	t_fork	*fork;
	t_philo	*philo;
}	t_data;

// initiate data
t_philo	*init_philo(t_data *data);
t_fork	*init_fork(t_data *data);
void	init_data(t_data *data, int ac, char **av);
long	ft_atol(const char *str);

// initiate the threads
long	create_threads(t_data *data);
long	get_current_time(void);
void	*dinner_routine(void *arg);
void	*monitor_routine(void *arg);

#endif