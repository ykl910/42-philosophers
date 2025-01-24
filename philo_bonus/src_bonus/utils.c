/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:27:12 by kyang             #+#    #+#             */
/*   Updated: 2025/01/24 19:22:40 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atol(const char *str)
{
	long	i;
	long	s;
	long	r;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - 48);
		i++;
	}
	return (s * r);
}

long	get_current_time(void)
{
	struct timeval	time;
	long			milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

void	safe_print(t_philo *philo, t_data *data, char *string)
{
	sem_wait(data->sem_print);
	sem_wait(data->sem_simulation);
	printf("%ld %i %s\n", get_current_time() - \
	philo->data->start_time, philo->philo_id, string);
	sem_post(data->sem_simulation);
	sem_post(data->sem_print);
	return ;
}

void	safe_sleep(long time, t_data *data)
{
	long	i;

	i = get_current_time();
	while ((get_current_time() - i) < time)
	{
		sem_wait(data->sem_simulation);
		sem_post(data->sem_simulation);
		usleep(50);
	}
}

void	cleanup_data(t_data *data)
{
	sem_close(data->sem_fork);
	sem_close(data->sem_end);
	sem_close(data->sem_full_philo);
	sem_close(data->sem_simulation);
	sem_close(data->sem_ready);
	sem_close(data->sem_print);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_end");
	sem_unlink("/sem_full_philo");
	sem_unlink("/sem_simulation");
	sem_unlink("/sem_ready");
	sem_unlink("/sem_print");
	free(data->philo);
}
