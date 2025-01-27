/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:07:47 by kyang             #+#    #+#             */
/*   Updated: 2025/01/27 16:56:43 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_death_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(100);
		if ((philo->data->time_to_die < get_current_time() - \
		long_getter(philo->data->sem_simulation, &philo->last_eat_time)))
		{
			safe_print(philo, "died");
			sem_wait(philo->data->sem_simulation);
			sem_post(philo->data->sem_kill);
			sem_post(philo->data->sem_died);
		}
	}
	return (NULL);
}

long	monitor_philo_full(t_philo *philo)
{
	if (philo->data->nb_limit_meals)
	{
		if (long_getter(philo->data->sem_simulation, &philo->nb_meals_eaten) == \
		long_getter(philo->data->sem_simulation, &philo->data->nb_limit_meals) \
		&& long_getter(philo->data->sem_simulation, &philo->status) == 0)
		{
			long_setter(philo->data->sem_simulation, &philo->status, 1);
			sem_post(philo->data->sem_full_philo);
		}
	}
	return (1);
}

long	eat(t_philo *philo)
{
	sem_wait(philo->data->sem_max_fork);
	sem_wait(philo->data->sem_fork);
	safe_print(philo, "has taken a fork");
	sem_wait(philo->data->sem_fork);
	safe_print(philo, "has taken a fork");
	long_setter(philo->data->sem_simulation, &philo->last_eat_time, \
	get_current_time());
	safe_print(philo, "is eating");
	sem_post(philo->data->sem_max_fork);
	safe_sleep(philo->data->time_to_eat, philo->data);
	long_incrementer(philo->data->sem_meals, &philo->nb_meals_eaten);
	if (!monitor_philo_full(philo))
		return (1);
	sem_post(philo->data->sem_fork);
	sem_post(philo->data->sem_fork);
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

void	*dinner_routine(t_philo	*philo)
{
	pthread_t	philo_thread;

	if (philo->philo_id % 2 == 0)
		usleep(100);
	pthread_create(&philo_thread, NULL, monitor_death_thread, philo);
	pthread_detach(philo_thread);
	while (1)
	{	
		if (eat(philo))
			return (NULL);
		if (sleep_and_think(philo))
			return (NULL);
	}
	return (NULL);
}
