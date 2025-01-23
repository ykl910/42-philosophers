/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:14:29 by kyang             #+#    #+#             */
/*   Updated: 2025/01/23 17:23:19 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	monitor_death(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_philo)
	{
		// if ((data->time_to_die < get_current_time() - \
		// long_getter(data->sem_simulation, &data->last_eat_time[i]) && \
		// long_getter(data->sem_simulation, &data->nb_meals_eaten[i]) > 0) || \
		// (data->time_to_die < get_current_time() - \
		// long_getter(data->sem_simulation, &data->start_time) && \
		// long_getter(data->sem_simulation, &data->nb_meals_eaten[i]) == 0))
		if (!long_getter(data->sem_simulation, &data->simulation_running))
		{
//			printf("%ld,%ld, %d\n",get_current_time() - data->last_eat_time[i],data->nb_meals_eaten[i], i);
			safe_print(&data->philo[i], "died");
			j = -1;
			while (++j < data->nb_philo)
			{
				if (kill(data->philo[i].pid, SIGKILL) == -1)
					perror("Failed to kill process");
			}
			long_setter(data->sem_simulation, &data->simulation_running, 0);
			usleep(100);
			return (1);
		}
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
			if (long_getter(data->sem_simulation, &data->nb_meals_eaten[i]) \
			>= data->nb_limit_meals && long_getter(data->sem_simulation, \
			&data->philo[i].status) == 0)
			{
				long_setter(data->sem_simulation, &data->philo[i].status, 1);
				long_incrementer(data->sem_simulation, &data->nb_philo_full);
			}
			i++;
		}
		if (long_getter(data->sem_simulation, &data->nb_philo_full) >= \
		data->nb_philo)
		{
			safe_print(&data->philo[i], "all philos are full");
			i = -1;
			while (++i < data->nb_philo)
			{
				if (kill(data->philo[i].pid, SIGKILL) == -1)
					perror("Failed to kill process");
			}
			long_setter(data->sem_simulation, &data->simulation_running, 0);
			usleep(100);
			return (1);
		}
	}
	return (0);
}

void	*monitor_routine(t_data	*data)
{
	while (1)
	{
		if (monitor_death(data))
			return (NULL);
		if (monitor_full(data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
