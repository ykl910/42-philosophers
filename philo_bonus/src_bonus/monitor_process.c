/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:14:29 by kyang             #+#    #+#             */
/*   Updated: 2025/01/25 15:22:37 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_death_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	sem_wait(data->sem_end);
	while (++i < data->nb_philo)
	{
		if (kill(data->philo[i].pid, SIGKILL) == -1)
			exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	//sem_wait(data->sem_simulation);
	return (NULL);
}

void	*monitor_full_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	while (++i < data->nb_philo)
		sem_wait(data->sem_full_philo);
	printf("All philosophers are full");
	i = -1;
	while (++i < data->nb_philo)
	{
		if (kill(data->philo[i].pid, SIGKILL) == -1)
			exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	//sem_wait(data->sem_simulation);
	return (NULL);
}

void	*monitor_routine(t_data *data)
{
	pthread_t	death_thread;
	pthread_t	full_thread;

	pthread_create(&death_thread, NULL, monitor_death_routine, data);
	pthread_create(&full_thread, NULL, monitor_full_routine, data);
	pthread_join(death_thread, NULL);
	pthread_join(full_thread, NULL);
	return (NULL);
}
