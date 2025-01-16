/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:07:47 by kyang             #+#    #+#             */
/*   Updated: 2025/01/16 16:36:33 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->ready_mutex);
		if (philo->data->all_threads_ready)
		{
			pthread_mutex_unlock(&philo->data->ready_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->ready_mutex);
	}
}

long	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->mutex_id);
	printf("%ld %d has taken a fork\n", get_current_time() - \
	philo->data->start_time, philo->philo_id);
	if (!death_check(philo))
	{
		pthread_mutex_unlock(&philo->first_fork->mutex_id);
		return (1);
	}
	pthread_mutex_lock(&philo->sec_fork->mutex_id);
	printf("%ld %d has taken a fork\n", get_current_time() - \
	philo->data->start_time, philo->philo_id);
	if (!death_check(philo))
	{
		pthread_mutex_unlock(&philo->first_fork->mutex_id);
		pthread_mutex_unlock(&philo->sec_fork->mutex_id);
		return (1);
	}
	return (0);
}

long	eat(t_philo *philo)
{
	long_setter(&philo->data->sim_mutex, &philo->last_eat_time, \
	get_current_time());
	printf("%ld %d is eating\n", get_current_time() - \
	philo->data->start_time, philo->philo_id);
	usleep(philo->data->time_to_eat * 1000);
	long_incrementer(&philo->data->sim_mutex, &philo->nb_meals_eaten);
	if (!death_check(philo))
	{
		pthread_mutex_unlock(&philo->first_fork->mutex_id);
		pthread_mutex_unlock(&philo->sec_fork->mutex_id);
		return (1);
	}
	pthread_mutex_unlock(&philo->first_fork->mutex_id);
	pthread_mutex_unlock(&philo->sec_fork->mutex_id);
	return (0);
}

long	sleep_and_think(t_philo *philo)
{
	if (!death_check(philo))
		return (1);
	printf("%ld %d is sleeping\n", get_current_time() - \
	philo->data->start_time, philo->philo_id);
	usleep(philo->data->time_to_sleep * 1000);
	if (!death_check(philo))
		return (1);
	printf("%ld %d is thinking\n", get_current_time() - \
	philo->data->start_time, philo->philo_id);
	//if (philo->data->nb_philo % 2 == 1)
	usleep((philo->data->time_to_eat * 2 - \
	philo->data->time_to_sleep) * 1000);
	return (0);
}

void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo);
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!death_check(philo))
			return (NULL);
		if (take_forks(philo))
			return (NULL);
		if (eat(philo))
			return (NULL);
		if (sleep_and_think(philo))
			return (NULL);
	}
	return (NULL);
}
