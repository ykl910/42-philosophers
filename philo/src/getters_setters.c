/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:52:09 by kyang             #+#    #+#             */
/*   Updated: 2025/01/17 15:52:40 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
