/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:32:23 by kyang             #+#    #+#             */
/*   Updated: 2025/01/16 15:37:36 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, \
		dinner_routine, &data->philo[i]) != 0)
			return (1);
		i++;
	}
	usleep(100);
	pthread_mutex_lock(&data->ready_mutex);
	data->all_threads_ready = 1;
	pthread_mutex_unlock(&data->ready_mutex);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	monitor;
	int			i;

	if (init_data(&data, ac, av))
		return (1);
	i = 0;
	if (create_threads(&data))
		return (1);
	pthread_create(&monitor, NULL, monitor_routine, &data);
	pthread_join(monitor, NULL);
	while (i < data.nb_philo)
	{
		pthread_join(data.philo[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_mutex_destroy(&data.fork[i].mutex_id);
		i++;
	}
	pthread_mutex_destroy(&data.sim_mutex);
	free(data.fork);
	free(data.philo);
	return (0);
}
