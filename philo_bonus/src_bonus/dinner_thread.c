/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:07:47 by kyang             #+#    #+#             */
/*   Updated: 2025/01/23 17:35:57 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_all_processes(t_philo *philo)
{
	while (1)
	{
		if (long_getter(philo->data->sem_ready, \
		&philo->data->all_threads_ready))
		{
			break ;
		}
		usleep(100);
	}
}

long	death_check(t_philo *philo)
{
	long	simulation_running;

	sem_wait(philo->data->sem_simulation);
	simulation_running = philo->data->simulation_running;
	sem_post(philo->data->sem_simulation);
	return (simulation_running);
}

long	monitor_philo_death(t_philo *philo, int i)
{
	if ((philo->data->time_to_die < get_current_time() - \
	long_getter(philo->data->sem_simulation, &philo->last_eat_time) && \
	long_getter(philo->data->sem_simulation, &philo->nb_meals_eaten) > 0) || \
	(philo->data->time_to_die < get_current_time() - \
	long_getter(philo->data->sem_simulation, &philo->data->start_time) && \
	long_getter(philo->data->sem_simulation, &philo->nb_meals_eaten) == 0))
	{
		long_setter(philo->data->sem_simulation, &philo->data->simulation_running, 0);
		printf("%ld,%ld, %d\n",get_current_time() - philo->last_eat_time, philo->nb_meals_eaten, i+1);
		return (0);
	}
	return (1);
}

long	monitor_philo_full(t_philo *philo, int i)
{
	i = 0;
	if (philo->data->nb_limit_meals)
	{
		if (long_getter(philo->data->sem_simulation, &philo->nb_meals_eaten) == \
		long_getter(philo->data->sem_simulation, &philo->data->nb_limit_meals))
		{
			long_incrementer(philo->data->sem_simulation, &philo->data->nb_philo_full);
		}
		if (long_getter(philo->data->sem_simulation, &philo->data->nb_philo_full) >= \
		philo->data->nb_philo)
		{
			safe_print(philo, "all philos are full");
			long_setter(philo->data->sem_simulation, &philo->data->simulation_running, 0);
			usleep(100);
			return (0);
		}
	}
	return (1);
}

long	eat(t_philo *philo, int i)
{	
	if (!death_check(philo))
		return (0);
	sem_wait(philo->data->sem_fork);
	safe_print(philo, "has taken a fork");
	if (!monitor_philo_death(philo, i))
		return (0);
	sem_wait(philo->data->sem_fork);
	if (!monitor_philo_death(philo, i))
		return (0);	
	safe_print(philo, "has taken a fork");
	// long_setter(philo->data->sem_simulation, &philo->data->last_eat_time[i], \
	// get_current_time());
	long_setter(philo->data->sem_simulation, &philo->last_eat_time, \
	get_current_time());
	if (!monitor_philo_death(philo, i))
		return (0);	safe_print(philo, "is eating");
	safe_sleep(philo->data->time_to_eat, philo->data);
	//long_incrementer(philo->data->sem_simulation, &philo->data->nb_meals_eaten[i]);
	long_incrementer(philo->data->sem_simulation, &philo->nb_meals_eaten);
	if (!monitor_philo_full(philo, i))
		return (0);	
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

void	*dinner_routine(t_philo	*philo, int i)
{
	if (philo->philo_id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (!death_check(philo))
			break ;
		if (eat(philo, i))
			return (NULL);
		if (!death_check(philo))
			break ;
		if (sleep_and_think(philo))
			return (NULL);
	}
	return (NULL);
}
