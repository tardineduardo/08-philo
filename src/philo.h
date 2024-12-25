/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:25 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/25 19:09:21 by eduribei         ###   ########.fr       */
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
	pthread_t	*th;
	t_time		*time;
}	t_resources;

int		ft_atoi(const char *nptr);
void	ft_validate_args(int argc, char *argv[]);

#endif
