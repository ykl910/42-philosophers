/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:32:23 by kyang             #+#    #+#             */
/*   Updated: 2025/01/25 15:09:52 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_processes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid < 0)
			exit(EXIT_FAILURE);
		else if (data->philo[i].pid == 0)
		{
			sem_wait(data->sem_ready);
			data->philo[i].data->start_time = get_current_time();
			data->philo[i].last_eat_time = get_current_time();
			dinner_routine(&data->philo[i]);
			exit(EXIT_SUCCESS);
		}
	}
	data->start_time = get_current_time();
}

void	run_processes(t_data *data)
{
	int	j;

	j = -1;
	while (++j < data->nb_philo)
		sem_post(data->sem_ready);
	usleep(100);
	monitor_routine(data);
	j = -1;
	while (++j < data->nb_philo)
	{
		if (kill(data->philo[j].pid, SIGKILL) == -1)
			exit(EXIT_FAILURE);
		waitpid(data->philo[j].pid, NULL, 0);
	}
}

int	main(int ac, char **av)
{
	t_data		data;

	if (init_data(&data, ac, av))
		return (1);
	create_processes(&data);
	run_processes(&data);
	cleanup_data(&data);
	return (0);
}
