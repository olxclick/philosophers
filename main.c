/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:30:11 by jbranco-          #+#    #+#             */
/*   Updated: 2023/05/25 15:49:25 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	destroy(t_args *args, t_philo *philo)
{
	if (args)
	{
		free(args->philo);
		free(args);
	}
	if (philo)
		free(philo);
	return ;
}

int	finisher(t_philo *philo, t_args *args, char *error_msg)
{
	size_t	i;

	i = 0;
	while (i < args->n_philo)
		pthread_mutex_destroy(&args->forks[i++]);
	pthread_mutex_destroy(&args->locker);
	pthread_mutex_destroy(&args->print_locker);
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	destroy(args, philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	*args;
	t_philo	*philo;

	if (argc == 5 || argc == 6)
	{
		args = malloc(sizeof(t_args));
		if (!init_args(args, argv))
			return (finisher(NULL, args, "Wrong Arguments!\n"));
		philo = malloc(sizeof(t_philo) * args->n_philo);
		init_philo(args);
		init_mutexs(args);
		init_threads(args);
		finisher(philo, args, "");
	}
	return (0);
}
