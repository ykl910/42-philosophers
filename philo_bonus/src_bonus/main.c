/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:32:23 by kyang             #+#    #+#             */
/*   Updated: 2025/01/22 17:53:46 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// long	create_threads(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	pthread_mutex_lock(&data->ready_mutex);
// 	while (i < data->nb_philo)
// 	{
// 		if (pthread_create(&data->philo[i].thread_id, NULL, \
// 		dinner_routine, &data->philo[i]) != 0)
// 			return (1);
// 		i++;
// 	}
// 	usleep(100);
// 	data->all_threads_ready = 1;
// 	data->start_time = get_current_time();
// 	pthread_mutex_unlock(&data->ready_mutex);
// 	return (0);
// }

long	create_processes(t_data *data)
{
	int	i;

	i = 0;
	sem_wait(&data->sem_ready);
	while (i < data->nb_philo)
	{
		data->philo[i].pid = fork();
        if (data->philo[i].pid < 0)
            exit(EXIT_FAILURE);
		i++;
	}
	usleep(100);
	data->all_threads_ready = 1;
	data->start_time = get_current_time();
	sem_post(&data->sem_ready);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	//pthread_t	monitor;
	int			i;

	if (init_data(&data, ac, av))
		return (1);
	i = -1;
	if (create_processes(&data))
		return (1);
	// if (pthread_create(&monitor, NULL, monitor_routine, &data) != 0)
	// 	return (1);
	// pthread_join(monitor, NULL);
	// while (++i < data.nb_philo)
	// 	pthread_join(data.philo[i].thread_id, NULL);
	// i = -1;
	// while (++i < data.nb_philo)
	// 	pthread_mutex_destroy(&data.fork[i].mutex_id);
	// pthread_mutex_destroy(&data.sim_mutex);
	// pthread_mutex_destroy(&data.ready_mutex);
	// pthread_mutex_destroy(&data.print_mutex);
	// free(data.fork);
	// free(data.philo);
	return (0);
}
