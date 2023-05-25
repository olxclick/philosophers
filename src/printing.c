/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:14:07 by jbranco-          #+#    #+#             */
/*   Updated: 2023/05/25 15:39:54 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->locker);
	if (philo->args->printed)
	{
		pthread_mutex_unlock(&philo->args->locker);
		return ;
	}
	pthread_mutex_lock(&philo->args->print_locker);
	printf("%ld ms %ld %s\n", (time_ms() - philo->args->start_time), philo->id,
		EATING);
	pthread_mutex_unlock(&philo->args->print_locker);
	pthread_mutex_unlock(&philo->args->locker);
}

void	print_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->locker);
	if (philo->args->printed)
	{
		pthread_mutex_unlock(&philo->args->locker);
		return ;
	}
	pthread_mutex_lock(&philo->args->print_locker);
	printf("%ld ms %ld %s\n", (time_ms() - philo->args->start_time), philo->id,
		SLEEPING);
	pthread_mutex_unlock(&philo->args->print_locker);
	pthread_mutex_unlock(&philo->args->locker);
}

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->locker);
	if (philo->args->printed)
	{
		pthread_mutex_unlock(&philo->args->locker);
		return ;
	}
	pthread_mutex_lock(&philo->args->print_locker);
	printf("%ld ms %ld %s\n", (time_ms() - philo->args->start_time), philo->id,
		FORKED);
	printf("%ld ms %ld %s\n", (time_ms() - philo->args->start_time), philo->id,
		FORKED);
	pthread_mutex_unlock(&philo->args->print_locker);
	pthread_mutex_unlock(&philo->args->locker);
}

void	print_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->locker);
	if (philo->args->printed)
	{
		pthread_mutex_unlock(&philo->args->locker);
		return ;
	}
	pthread_mutex_lock(&philo->args->print_locker);
	printf("%ld ms %ld %s\n", (time_ms() - philo->args->start_time), philo->id,
		THINKING);
	pthread_mutex_unlock(&philo->args->print_locker);
	pthread_mutex_unlock(&philo->args->locker);
}

void	print_satisfied(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->locker);
	if (!philo->args->printed)
	{
		philo->args->printed = 1;
		pthread_mutex_lock(&philo->args->print_locker);
		printf(SATISFIED"\n");
		pthread_mutex_unlock(&philo->args->print_locker);
	}
	pthread_mutex_unlock(&philo->args->locker);
}
