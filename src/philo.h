/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:25 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/27 14:49:40 by eduribei         ###   ########.fr       */
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

typedef struct timeval	t_chrono;

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
	size_t				total_meals;
	size_t				time_starving;
	bool				detached;
	struct s_resources	*r;
}	t_philo;

typedef struct s_resources
{
	pthread_t		*th;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*stop;
	t_philo			*philo;
	t_chrono		*chrono;
	t_params		*params;
}	t_resources;

int		ft_atoi(const char *nptr);
void	ft_validate_args(int argc, char *argv[], t_resources *r);
void	*ft_philosopher(void *args);
void	ft_alloc_resources(t_resources *r);
void	ft_free_resources(t_resources *r);
void	ft_stop_all_threads(t_resources *r);
void	ft_error(char *message, t_resources *r);
void	ft_init_threads(t_resources *r);
void	ft_join_threads(t_resources *r);


#endif
