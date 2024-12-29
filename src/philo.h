/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:25 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/28 17:06:59 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct timeval	timeval;

typedef struct s_params
{
	size_t		nphilos;
	size_t		nforks;
	size_t		tsleep;
	int			tdie;
	int			teat;
	int			nmeals;
	bool		stop;
}	t_params;

typedef struct s_philo
{
	size_t				index;
	pthread_mutex_t		*fork1;
	pthread_mutex_t		*fork2;
	size_t				total_meals;
	size_t				time_starving;
	timeval				tlog;
	bool				detached;
	struct s_resources	*r;
}	t_philo;

typedef struct s_resources
{
	pthread_t		*th;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*stop;
	int				(*print)(char *, ...);
	t_philo			*philo;
	t_params		*params;
}	t_resources;

//Validation
int		ft_atoi(const char *nptr);
void	ft_validate_args(int argc, char *argv[], t_resources *r);

//Inits
void	ft_init_threads(t_resources *r);
void	ft_init_mutexes(t_resources *r);
void	ft_alloc_resources(t_resources *r);

//Philosopher
void	*ft_philosopher(void *args);

//Actions
void	grab_fork_1(t_philo *philo);
void	grab_fork_2(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

//exiting
void	ft_stop_all_threads(t_resources *r);
void	ft_join_threads(t_resources *r);
void	ft_free_resources(t_resources *r);

//Error
void	ft_error(char *message, t_resources *r);

#endif
