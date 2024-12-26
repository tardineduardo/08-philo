/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:25 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/25 22:39:13 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_chrono;

typedef struct s_params
{
	size_t			nphilos;
	size_t			nforks;
	int			tdie;
	int			teat;
	size_t			tsleep;
	int			nmeals;
}	t_params;

typedef struct s_philo
{
	size_t						index;
	size_t						total_meals;
	size_t						time_starving;	
	struct s_resources			*r;
}	t_philo;

typedef struct s_resources
{
	pthread_t		*th;
	pthread_mutex_t	*mutex;
	t_philo			*philo;
	t_chrono		*chrono;
	t_params		*params;
}	t_resources;

int		ft_atoi(const char *nptr);
void	ft_validate_args(int argc, char *argv[], t_resources *r);
void	*ft_philosopher(void *args);
void	ft_alloc_resources(t_resources *r);
void	ft_free_resources(t_resources *r);
void	psleep(t_resources *r);


#endif
