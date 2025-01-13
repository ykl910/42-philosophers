/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:46:08 by kyang             #+#    #+#             */
/*   Updated: 2025/01/13 23:13:19 by kyang            ###   ########.fr       */
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

typedef struct s_fork
{
	pthread_mutex_t	mutex_id;
	int				fork_id;
	int				status;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread_id; 
	t_fork		first_fork;
	t_fork		sec_fork;
	int			nb_meals_eat;
	int 		last_eat_time;
	int			status;
}	t_philo;

typedef struct s_monitor
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_limit_meals;
	t_fork	*fork;
	t_philo	*philo;
}	t_monitor;

#endif