/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:25 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/25 21:30:08 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_time;

typedef struct s_resources
{
	pthread_t		*th;
	pthread_mutex_t	*mutex;
	t_time			*time;
}	t_resources;

typedef struct s_philo
{
	size_t			index;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*mutex_right;
	t_resources		*r;
}	t_philo;

int		ft_atoi(const char *nptr);
void	ft_validate_args(int argc, char *argv[]);

#endif
