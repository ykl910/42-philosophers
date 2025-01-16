/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:27:12 by kyang             #+#    #+#             */
/*   Updated: 2025/01/16 16:11:21 by kyang            ###   ########.fr       */
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

void	long_setter(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long	long_getter(pthread_mutex_t *mutex, long *src)
{
	long	val;

	pthread_mutex_lock(mutex);
	val = *src;
	pthread_mutex_unlock(mutex);
	return (val);
}

void	long_incrementer(pthread_mutex_t *mutex, long *dest)
{
	pthread_mutex_lock(mutex);
	(*dest)++;
	pthread_mutex_unlock(mutex);
}
