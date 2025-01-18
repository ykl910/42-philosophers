/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:27:12 by kyang             #+#    #+#             */
/*   Updated: 2025/01/18 20:01:39 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	safe_print(t_philo *philo, char *string)
{
	pthread_mutex_lock(&(philo->data->print_mutex));
	if (long_getter(&philo->data->sim_mutex, &philo->data->simulation_running))
	{
		printf("%ld %i %s\n", get_current_time() - \
		philo->data->start_time, philo->philo_id, string);
	}
	pthread_mutex_unlock(&(philo->data->print_mutex));
	return ;
}

void	safe_sleep(long time, t_data *data)
{
	long	i;

	i = get_current_time();
	while ((data->simulation_running))
	{
		if ((get_current_time() - i) >= time)
			break ;
		usleep(50);
	}
}
