/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:07:47 by kyang             #+#    #+#             */
/*   Updated: 2025/01/20 12:28:08 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_philo *philo)
{
	while (1)
	{
		if (long_getter(&philo->data->ready_mutex, \
		&philo->data->all_threads_ready))
		{
			break ;
		}
	}
}

long	death_check(t_philo *philo)
{
	long	simulation_running;

	pthread_mutex_lock(&philo->data->sim_mutex);
	simulation_running = philo->data->simulation_running;
	pthread_mutex_unlock(&philo->data->sim_mutex);
	return (simulation_running);
}

long	eat(t_philo *philo)
{
	if (!death_check(philo))
		return (0);
	pthread_mutex_lock(&philo->first_fork->mutex_id);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->sec_fork->mutex_id);
	safe_print(philo, "has taken a fork");
	long_setter(&philo->data->sim_mutex, &philo->last_eat_time, \
	get_current_time());
	safe_print(philo, "is eating");
	safe_sleep(philo->data->time_to_eat, philo->data);
	long_incrementer(&philo->data->sim_mutex, &philo->nb_meals_eaten);
	pthread_mutex_unlock(&philo->first_fork->mutex_id);
	pthread_mutex_unlock(&philo->sec_fork->mutex_id);
	return (0);
}

long	sleep_and_think(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	safe_sleep(philo->data->time_to_sleep, philo->data);
	safe_print(philo, "is thinking");
	if (philo->data->nb_philo % 2 == 1)
		safe_sleep((philo->data->time_to_eat * 2 - \
		philo->data->time_to_sleep), philo->data);
	return (0);
}

void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo);
	if (philo->philo_id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (!death_check(philo))
			break ;
		if (eat(philo))
			return (NULL);
		if (!death_check(philo))
			break ;
		if (sleep_and_think(philo))
			return (NULL);
	}
	return (NULL);
}
