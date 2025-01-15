/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:07:47 by kyang             #+#    #+#             */
/*   Updated: 2025/01/15 17:49:08 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	create_threads(t_data *data)
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

long		death_check(t_philo *philo)
{
	long	simulation_running;

	pthread_mutex_lock(&philo->data->sim_mutex);
	simulation_running = philo->data->simulation_running;
	pthread_mutex_unlock(&philo->data->sim_mutex);
	return (simulation_running);
}

void	*dinner_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;

	while (1)
	{
		if (!death_check(philo))
			return (NULL);

		pthread_mutex_lock(&philo->first_fork->mutex_id);
		printf("%ld %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->philo_id);

		if (!death_check(philo))
		{
			pthread_mutex_unlock(&philo->first_fork->mutex_id);
			return (NULL);
		}

		pthread_mutex_lock(&philo->sec_fork->mutex_id);
		printf("%ld %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->philo_id);

		if (!death_check(philo))
		{
			pthread_mutex_unlock(&philo->first_fork->mutex_id);
			pthread_mutex_unlock(&philo->sec_fork->mutex_id);
			return (NULL);
		}

		pthread_mutex_lock(&philo->data->sim_mutex);
		philo->last_eat_time = get_current_time();
		pthread_mutex_unlock(&philo->data->sim_mutex);

		printf("%ld %d is eating\n", get_current_time() - philo->data->start_time, philo->philo_id);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_lock(&philo->data->sim_mutex);
		philo->nb_meals_eaten++;
		pthread_mutex_unlock(&philo->data->sim_mutex);

		if (!death_check(philo))
		{
			pthread_mutex_unlock(&philo->first_fork->mutex_id);
			pthread_mutex_unlock(&philo->sec_fork->mutex_id);
			return (NULL);
		}

		pthread_mutex_lock(&philo->data->sim_mutex);
		printf("%ld %d is done eating %ld meals\n", get_current_time() - philo->data->start_time, philo->philo_id, philo->nb_meals_eaten);
		pthread_mutex_unlock(&philo->data->sim_mutex);

		pthread_mutex_unlock(&philo->first_fork->mutex_id);
		pthread_mutex_unlock(&philo->sec_fork->mutex_id);
		
		if (!death_check(philo))
			return (NULL);

		printf("%ld %d is sleeping\n", get_current_time() - philo->data->start_time, philo->philo_id);
		
		usleep(philo->data->time_to_sleep * 1000);
		if (!death_check(philo))
			return (NULL);
		
		printf("%ld %d is thinking\n", get_current_time() - philo->data->start_time, philo->philo_id);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data *data;
	int		i;
	long	time_since_last_meal;
	long	time_since_start;
	long	nb_meals_eaten;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->sim_mutex);
			time_since_last_meal = get_current_time() - data->philo[i].last_eat_time;
			time_since_start = get_current_time() - data->start_time;
			nb_meals_eaten = data->philo[i].nb_meals_eaten;
			pthread_mutex_unlock(&data->sim_mutex);
			if ((data->time_to_die < time_since_last_meal && nb_meals_eaten > 0)
			||	(data->time_to_die < time_since_start && nb_meals_eaten == 0))
			{
				printf("%d died after starving for %ld or %ld after %ld meal\n", \
				data->philo[i].philo_id, time_since_last_meal, time_since_start, nb_meals_eaten);
				pthread_mutex_lock(&data->sim_mutex);
				data->simulation_running = 0;
				pthread_mutex_unlock(&data->sim_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->sim_mutex);
			i++;
		}
		if (data->nb_limit_meals)
		{
			i = 0;
			while (i < data->nb_philo)
			{
				pthread_mutex_lock(&data->sim_mutex);
				if (data->philo[i].nb_meals_eaten >= data->nb_limit_meals && data->philo[i].status == 0)
				{
					data->philo[i].status = 1;
					data->nb_philo_full++;
				}
				pthread_mutex_unlock(&data->sim_mutex);
				i++;
			}
			if (data->nb_philo_full >= data->nb_philo)
			{
				printf("simulation ended, everyone is full\n");
				pthread_mutex_lock(&data->sim_mutex);
				data->simulation_running = 0;
				pthread_mutex_unlock(&data->sim_mutex);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}

