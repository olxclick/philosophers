/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:15:04 by jbranco-          #+#    #+#             */
/*   Updated: 2023/06/06 15:23:52 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_mutexs(t_args *args)
{
	size_t	i;

	i = 0;
	pthread_mutex_init(&args->locker, NULL);
	pthread_mutex_init(&args->print_locker, NULL);
	while (i < args->n_philo)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
}

void	init_philo(t_args *args)
{
	size_t	i;

	i = 0;
	args->philo = malloc(args->n_philo * sizeof(t_philo));
	while (i < args->n_philo)
	{
		args->philo[i].id = i + 1;
		if (i == args->n_philo - 1)
		{
			args->philo[i].right = i;
			args->philo[i].left = (i + 1) % args->n_philo;
		}
		else
		{
			args->philo[i].left = i;
			args->philo[i].right = (i + 1) % args->n_philo;
		}
		args->philo[i].times_eaten = 0;
		args->philo[i].last_meal = time_ms();
		args->philo[i].args = args;
		i++;
	}
}

int	init_args(t_args *args, char **argv)
{
	if (!ft_isdigit(argv[1]) || !ft_isdigit(argv[2]) || \
	!ft_isdigit(argv[3]) || !ft_isdigit(argv[4]))
		return (0);
	args->n_philo = ft_atoi(argv[1]);
	args->die_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (!argv[5])
		args->eating_number = 0;
	else
	{
		if (argv[5] && ft_atoi(argv[5]) < 0)
			return (0);
		else if (argv[5] && ft_isdigit(argv[5]))
			args->eating_number = ft_atoi(argv[5]);
	}
	args->satisfied = 0;
	args->printed = 0;
	args->died = 0;
	return (1);
}

int	init_threads(t_args *args)
{
	size_t	i;
	t_philo	*philo;

	args->start_time = time_ms();
	philo = args->philo;
	i = -1;
	while (++i < args->n_philo)
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (1);
	check_death(philo);
	i = -1;
	while (++i < args->n_philo)
		if (pthread_join(philo[i].thread, NULL))
			return (1);
	return (1);
}
