/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:50:00 by kyang             #+#    #+#             */
/*   Updated: 2025/01/24 19:27:09 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	data->nb_philo_full = 0;
	init_semaphore(data, av);
	data->philo = init_philo(data);
	return (0);
}

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

void	init_semaphore(t_data *data, char **av)
{
	sem_unlink("/sem_fork");
	sem_unlink("/sem_end");
	sem_unlink("/sem_full_philo");
	sem_unlink("/sem_simulation");
	sem_unlink("/sem_ready");
	sem_unlink("/sem_print");
	data->sem_fork = sem_open("/sem_fork", O_CREAT, 0644, ft_atol(av[1]));
	if (data->sem_fork == SEM_FAILED)
		exit(EXIT_FAILURE);
	data->sem_end = sem_open("/sem_end", O_CREAT, 0644, 0);
	if (data->sem_end == SEM_FAILED)
		exit(EXIT_FAILURE);
	data->sem_full_philo = sem_open("/sem_full_philo", O_CREAT, 0644, 0);
	if (data->sem_full_philo == SEM_FAILED)
		exit(EXIT_FAILURE);
	data->sem_simulation = sem_open("/sem_simulation", O_CREAT, 0644, 1);
	if (data->sem_simulation == SEM_FAILED)
		exit(EXIT_FAILURE);
	data->sem_ready = sem_open("/sem_ready", O_CREAT, 0644, 0);
	if (data->sem_ready == SEM_FAILED)
		exit(EXIT_FAILURE);
	data->sem_print = sem_open("/sem_print", O_CREAT, 0644, 1);
	if (data->sem_print == SEM_FAILED)
		exit(EXIT_FAILURE);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * (data->nb_philo));
	if (!philo)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < data->nb_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].nb_meals_eaten = 0;
		philo[i].last_eat_time = get_current_time();
		philo[i].data = data;
		philo[i].status = 0;
	}
	return (philo);
}
