/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:50:00 by kyang             #+#    #+#             */
/*   Updated: 2025/01/15 16:55:23 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, int ac, char **av)
{	
	if (ac == 5 || ac == 6)
	{
		data->nb_philo = ft_atol(av[1]);
		data->time_to_die = ft_atol(av[2]);
		data->time_to_eat = ft_atol(av[3]);
		data->time_to_sleep = ft_atol(av[4]);
		if (ac == 6)
			data->nb_limit_meals = ft_atol(av[5]);
		data->start_time = get_current_time();
		data->fork = init_fork(data);
		data->philo = init_philo(data);
		data->simulation_running = 1;
		data->nb_philo_full = 0;
		pthread_mutex_init(&data->sim_mutex, NULL);
	}
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * (data->nb_philo));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].nb_meals_eaten = 0;
		philo[i].last_eat_time = get_current_time();
		philo[i].data = data;
		philo[i].status = 0;
		if (i % 2 == 0)
		{
			philo[i].first_fork = &data->fork[i];
			philo[i].sec_fork = &data->fork[(i + 1) % data->nb_philo];
		}
		else
		{
			philo[i].first_fork = &data->fork[(i + 1) % data->nb_philo];
			philo[i].sec_fork = &data->fork[i];
		}
		i++;
	}
	return (philo);
}

t_fork	*init_fork(t_data *data)
{
	t_fork	*fork;
	int		i;

	fork = malloc(sizeof(t_fork) * data->nb_philo);
	if (!fork)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		fork[i].fork_id = i;
		if (pthread_mutex_init(&fork[i].mutex_id, NULL) != 0)
			return (NULL);
		i++;
	}
	return (fork);
}
