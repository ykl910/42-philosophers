/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:32:23 by kyang             #+#    #+#             */
/*   Updated: 2025/01/14 17:25:11 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	monitor;
	int	i;

	init_data(&data, ac, av);
	i = 0;
	if (create_threads(&data))
		return (1);
	pthread_create(&monitor, NULL, monitor_routine, &data);
	while (i < data.nb_philo)
	{
		pthread_join(data.philo[i].thread_id, NULL);
		i++;
	}
	pthread_join(monitor, NULL);

	return (0);
}
