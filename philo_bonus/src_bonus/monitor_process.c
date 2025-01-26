/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:14:29 by kyang             #+#    #+#             */
/*   Updated: 2025/01/26 10:35:03 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_full_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	while (++i < data->nb_philo)
	{
		sem_wait(data->sem_full_philo);
	}
	//sem_post(data->sem_end);
	sem_post(data->sem_kill);
	return (NULL);
}

void	monitor_routine(t_data *data)
{
	pthread_t	full_thread;

	pthread_create(&full_thread, NULL, monitor_full_routine, data);
	pthread_detach(full_thread);
}
