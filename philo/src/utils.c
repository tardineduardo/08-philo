/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:39:36 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/02 15:22:18 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + (*nptr - '0');
		nptr++;
	}
	return (nb * sign);
}

// FREE RESOURCES WHEN ONLY WHEN THREADS RETURN.


void	ft_error(char *message, t_main *r)
{
	printf("Error: %s", message);
	ft_free_resources(r);
	exit(1);
}

bool	ft_thread_must_stop(t_params *params)
{
	pthread_mutex_lock(params->stop_mutex);
	if (params->must_stop)
	{
		pthread_mutex_unlock(params->stop_mutex);
		return (true);
	}
	pthread_mutex_unlock(params->stop_mutex);
	return (false);
}
