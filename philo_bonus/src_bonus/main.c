/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:32:23 by kyang             #+#    #+#             */
/*   Updated: 2025/01/23 17:09:50 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	create_processes(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].pid = fork();
        if (data->philo[i].pid < 0)
            exit(EXIT_FAILURE);
		else if (data->philo[i].pid == 0)
		{
			sem_wait(data->sem_ready);
			data->start_time = get_current_time();
			dinner_routine(&data->philo[i], i);
		}
	}
	usleep(100);
	data->start_time = get_current_time();
	j = -1;
	while (++j < data->nb_philo)
		sem_post(data->sem_ready);
	usleep(100);
	monitor_routine(data);
    j = -1;
    while (++j < data->nb_philo)
    {
        if (kill(data->philo[j].pid, SIGKILL) == -1)
            perror("Failed to kill process");
        waitpid(data->philo[j].pid, NULL, 0);
    }
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	int			i;

	if (init_data(&data, ac, av))
		return (1);
	i = -1;
	if (create_processes(&data))
		return (1);
	sem_close(data.sem_fork);
	sem_unlink("/sem_fork");
	sem_close(data.sem_simulation);
	sem_unlink("/sem_simulation"); 
	sem_close(data.sem_ready);
	sem_unlink("/sem_ready"); 
	sem_close(data.sem_print);
	sem_unlink("/sem_print"); 
	free(data.philo);
	return (0);
}
