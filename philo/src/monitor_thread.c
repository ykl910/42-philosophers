/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:14:29 by kyang             #+#    #+#             */
/*   Updated: 2025/01/17 16:51:31 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	monitor_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if ((data->time_to_die < get_current_time() - \
		long_getter(&data->sim_mutex, &data->philo[i].last_eat_time) && \
		long_getter(&data->sim_mutex, &data->philo[i].nb_meals_eaten) > 0) || \
		(data->time_to_die < get_current_time() - \
		long_getter(&data->sim_mutex, &data->start_time) && \
		long_getter(&data->sim_mutex, &data->philo[i].nb_meals_eaten) == 0))
		{
			safe_print(&data->philo[i], "died");
			long_setter(&data->sim_mutex, &data->simulation_running, 0);
			usleep(100);
			return (1);
		}
		pthread_mutex_unlock(&data->sim_mutex);
		i++;
	}
	return (0);
}

long	monitor_full(t_data *data)
{
	int	i;

	if (data->nb_limit_meals)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->sim_mutex);
			if (data->philo[i].nb_meals_eaten >= data->nb_limit_meals && \
			data->philo[i].status == 0)
			{
				data->philo[i].status = 1;
				data->nb_philo_full++;
			}
			pthread_mutex_unlock(&data->sim_mutex);
			i++;
		}
		if (data->nb_philo_full >= data->nb_philo)
		{
			long_setter(&data->sim_mutex, &data->simulation_running, 0);
			usleep(100);
			return (1);
		}
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (monitor_death(data))
			return (NULL);
		if (monitor_full(data))
			return (NULL);
	}
	return (NULL);
}
