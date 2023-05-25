/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:37:50 by jbranco-          #+#    #+#             */
/*   Updated: 2023/05/25 15:43:35 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_args	*args;
	t_philo	*philo;

	philo = (t_philo *)arg;
	args = philo->args;
	while (1)
	{
		pthread_mutex_lock(&args->locker);
		if (args->printed || args->n_philo <= 1)
		{
			pthread_mutex_unlock(&args->locker);
			break ;
		}
		pthread_mutex_unlock(&args->locker);
		eating(philo);
		sleeping(philo);
		print_thinking(philo);
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&args->forks[philo->left]);
	pthread_mutex_lock(&args->forks[philo->right]);
	print_fork(philo);
	print_eating(philo);
	pthread_mutex_lock(&args->locker);
	philo->last_meal = time_ms();
	philo->times_eaten++;
	if (philo->times_eaten == args->eating_number)
		args->satisfied++;
	pthread_mutex_unlock(&args->locker);
	usleep(philo->args->eat_time * 1000);
	pthread_mutex_unlock(&args->forks[philo->left]);
	pthread_mutex_unlock(&args->forks[philo->right]);
}

void	sleeping(t_philo *philo)
{
	print_sleeping(philo);
	usleep(philo->args->sleep_time * 1000);
}

void	check_death(t_philo *philo)
{
	t_args	*args;
	size_t	i;

	args = philo->args;
	while (1)
	{
		i = -1;
		pthread_mutex_lock(&args->locker);
		while (++i < args->n_philo)
		{
			if ((time_ms() - philo[i].last_meal) > philo[i].args->die_time)
			{
				pthread_mutex_unlock(&args->locker);
				dead_printing(philo);
				return ;
			}
			if ((args->satisfied == args->n_philo) && args->eating_number)
			{
				pthread_mutex_unlock(&args->locker);
				print_satisfied(philo);
				return ;
			}
		}
		pthread_mutex_unlock(&args->locker);
	}
}

void	dead_printing(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->locker);
	if (!philo->args->printed)
	{
		philo->args->printed = 1;
		pthread_mutex_lock(&philo->args->print_locker);
		printf("%ld ms %ld %s\n", (time_ms() - philo->args->start_time),
			philo->id, DIED);
		pthread_mutex_unlock(&philo->args->print_locker);
	}
	pthread_mutex_unlock(&philo->args->locker);
}
