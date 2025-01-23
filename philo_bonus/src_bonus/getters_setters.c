/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:52:09 by kyang             #+#    #+#             */
/*   Updated: 2025/01/23 10:35:36 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	long_setter(sem_t *semaphore, long *dest, long value)
{
	sem_wait(semaphore);
	*dest = value;
	sem_post(semaphore);
}

long	long_getter(sem_t *semaphore, long *src)
{
	long	val;

	sem_wait(semaphore);
	val = *src;
	sem_post(semaphore);
	return (val);
}

void	long_incrementer(sem_t *semaphore, long *dest)
{
	sem_wait(semaphore);
	(*dest)++;
	sem_post(semaphore);
}
