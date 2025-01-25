/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:07:47 by kyang             #+#    #+#             */
/*   Updated: 2025/01/25 14:15:35 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	monitor_philo_death(t_philo *philo, t_data *data, int i)
{
	i = 0;
	if ((philo->data->time_to_die < get_current_time() - \
	long_getter(philo->data->sem_simulation, &philo->last_eat_time)))
	{
		safe_print(philo, data, "died");
		sem_wait(philo->data->sem_simulation);
		sem_post(philo->data->sem_end);
		return (0);
	}
	return (1);
}

void	monitor_philo_full(t_philo *philo, t_data *data)
{
	data->nb_limit_meals = 10;
	if (philo->data->nb_limit_meals)
	{
		if (long_getter(philo->data->sem_simulation, &philo->nb_meals_eaten) == \
		long_getter(philo->data->sem_simulation, &philo->data->nb_limit_meals) && \
		long_getter(philo->data->sem_simulation, &philo->status) == 0)
		{
			long_setter(philo->data->sem_simulation, &philo->status, 1);
			sem_post(philo->data->sem_full_philo);
		}
	}
}

long	eat(t_philo *philo, int i, t_data *data)
{
	i = 0;
	sem_wait(philo->data->sem_fork);
	safe_print(philo, data, "has taken a fork");
	if (!monitor_philo_death(philo, data, i))
		return (0);
	sem_wait(philo->data->sem_fork);
	if (!monitor_philo_death(philo, data, i))
		return (0);
	safe_print(philo, data, "has taken a fork");
	long_setter(philo->data->sem_simulation, &philo->last_eat_time, \
	get_current_time());
	if (!monitor_philo_death(philo, data, i))
		return (0);
	safe_print(philo, data, "is eating");
	safe_sleep(philo->data->time_to_eat, philo->data);
	long_incrementer(philo->data->sem_simulation, &philo->nb_meals_eaten);
	monitor_philo_full(philo, data);
	sem_post(philo->data->sem_fork);
	sem_post(philo->data->sem_fork);
	return (0);
}

long	sleep_and_think(t_philo *philo, t_data *data)
{
	safe_print(philo, data, "is sleeping");
	safe_sleep(philo->data->time_to_sleep, philo->data);
	safe_print(philo, data, "is thinking");
	if (philo->data->nb_philo % 2 == 1)
		safe_sleep((philo->data->time_to_eat * 2 - \
		philo->data->time_to_sleep), philo->data);
	return (0);
}

void	*dinner_routine(t_philo	*philo, t_data *data, int i)
{
	if (philo->philo_id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (!monitor_philo_death(philo, data, i))
			break ;
		if (eat(philo, i, data))
			return (NULL);
		if (!monitor_philo_death(philo, data, i))
			break ;
		if (sleep_and_think(philo, data))
			return (NULL);
	}
	return (NULL);
}
