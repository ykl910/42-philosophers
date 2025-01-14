/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:07:47 by kyang             #+#    #+#             */
/*   Updated: 2025/01/14 17:16:01 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, dinner_routine, &data->philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	*dinner_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;

	pthread_mutex_lock(&philo->first_fork.mutex_id);
	printf("%ld %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->philo_id);
	pthread_mutex_lock(&philo->sec_fork.mutex_id);
	printf("%ld %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->philo_id);

	philo->last_eat_time = get_current_time();
	printf("%ld %d is eating\n", get_current_time() - philo->data->start_time, philo->philo_id);
	usleep(philo->data->time_to_eat * 1000);
	philo->nb_meals_eaten++;

	pthread_mutex_unlock(&philo->first_fork.mutex_id);
	pthread_mutex_unlock(&philo->sec_fork.mutex_id);
	
	printf("%ld %d is sleeping\n", get_current_time() - philo->data->start_time, philo->philo_id);
	usleep(philo->data->time_to_sleep * 1000);

	printf("%ld %d is thinking\n", get_current_time() - philo->data->start_time, philo->philo_id);
}

void	*monitor_routine(void *arg)
{
	t_data *data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->nb_philo)
	{
		if (data->time_to_die < get_current_time() - data->philo[i].last_eat_time ||
			(data->time_to_die < get_current_time() - data->start_time && data->philo[i].nb_meals_eaten == 0))
		{
			printf("%d died\n", data->philo[i].philo_id);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

