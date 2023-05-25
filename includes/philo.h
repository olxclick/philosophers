/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:27:00 by jbranco-          #+#    #+#             */
/*   Updated: 2023/05/25 15:34:55 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define FORKED "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "is dead"
# define SATISFIED "All Philos have eaten :)"

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_args	*args;
	pthread_t		thread;
	size_t			id;
	size_t			left;
	size_t			times_eaten;
	size_t			right;
	size_t			last_meal;
}					t_philo;

typedef struct s_args
{
	pthread_mutex_t	forks[250];
	pthread_mutex_t	locker;
	pthread_mutex_t	print_locker;
	t_philo			*philo;
	size_t			n_philo;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			eating_number;
	size_t			satisfied;
	size_t			died;
	size_t			start_time;
	size_t			printed;
}					t_args;

int					ft_atoi(const char *str);
int					init_args(t_args *args, char **argv);
int					init_threads(t_args *args);
void				*routine(void *arg);
int					ft_strlen(char *str);
void				init_philo(t_args *args);
int					ft_isdigit(char *str);
int					finisher(t_philo *philo, t_args *args, char *error_msg);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				init_mutexs(t_args *args);
void				print_eating(t_philo *philo);
void				print_sleeping(t_philo *philo);
void				print_fork(t_philo *philo);
void				print_thinking(t_philo *philo);
void				check_death(t_philo *philo);
void				dead_printing(t_philo *philo);
void				print_satisfied(t_philo *philo);
suseconds_t			time_ms(void);

#endif