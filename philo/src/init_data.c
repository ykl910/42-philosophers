/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:50:00 by kyang             #+#    #+#             */
/*   Updated: 2025/01/20 15:54:52 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	check_input(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if ((ac == 6 && ft_atol(av[5]) <= 0))
		{
			printf("wrong input\n");
			return (1);
		}
		if (ft_atol(av[1]) <= 0 || ft_atol(av[1]) > 200 || ft_atol(av[2]) < 60 \
		|| ft_atol(av[3]) < 60 || ft_atol(av[4]) < 60)
		{
			printf("wrong input\n");
			return (1);
		}
		if (ft_atol(av[1]) == 1)
		{
			printf("0 1 has taken a fork\n");
			usleep(ft_atol(av[1]) * 1000);
			printf("%ld 1 has died\n", ft_atol(av[2]));
			return (1);
		}
		return (0);
	}
	printf("wrong input\n");
	return (1);
}

long	init_data(t_data *data, int ac, char **av)
{
	if (check_input(ac, av))
		return (1);
	data->nb_philo = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->nb_limit_meals = ft_atol(av[5]);
	else
		data->nb_limit_meals = 0;
	data->fork = init_fork(data);
	data->philo = init_philo(data);
	data->simulation_running = 1;
	data->all_threads_ready = 0;
	data->nb_philo_full = 0;
	if (pthread_mutex_init(&data->ready_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->sim_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	return (0);
}

void	assign_fork(t_data *data, t_philo *philo, int i)
{
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
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * (data->nb_philo));
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].nb_meals_eaten = 0;
		philo[i].last_eat_time = get_current_time();
		philo[i].data = data;
		philo[i].status = 0;
		assign_fork(data, philo, i);
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
	i = -1;
	while (++i < data->nb_philo)
	{
		fork[i].fork_id = i;
		if (pthread_mutex_init(&fork[i].mutex_id, NULL) != 0)
			return (NULL);
	}
	return (fork);
}
