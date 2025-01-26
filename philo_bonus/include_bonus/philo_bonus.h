/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:46:08 by kyang             #+#    #+#             */
/*   Updated: 2025/01/26 10:44:05 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pid_t		pid;
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
	sem_t			*sem_simulation;
	long			process_killed;
	sem_t			*sem_died;
	long			nb_philo_full;
	sem_t			*sem_ready;
	sem_t			*sem_meals;
	sem_t			*sem_print;
	sem_t			*sem_fork;
	sem_t			*sem_max_fork;
	sem_t			*sem_sleep;
	sem_t			*sem_full_philo;
	sem_t			*sem_kill;
	sem_t			*sem_end;
	t_philo			*philo;
}	t_data;

// initiate data
long	check_input(int ac, char **av);
void	init_semaphore_one(t_data *data, char **av);
void	init_semaphore_two(t_data *data);
t_philo	*init_philo(t_data *data);
long	init_data(t_data *data, int ac, char **av);

// dinner thread
void	create_processes(t_data *data);
void	run_processes(t_data *data);
long	eat(t_philo *philo);
long	sleep_and_think(t_philo *philo);
void	*dinner_routine(t_philo	*philo);

// monitor thread
long	monitor_philo_death(t_philo *philo);
long	monitor_philo_full(t_philo *philo);
void	*monitor_death_routine(void *arg);
void	*monitor_full_routine(void *arg);
void	monitor_routine(t_data	*data);

// helper
long	ft_atol(const char *str);
long	get_current_time(void);
void	long_setter(sem_t *semaphore, long *dest, long value);
long	long_getter(sem_t *semaphore, long *src);
void	long_incrementer(sem_t *semaphore, long *dest);
void	safe_print(t_philo *philo, char *string);
void	safe_sleep(long time, t_data *data);
void	cleanup_data(t_data *data);

#endif