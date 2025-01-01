/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:39:36 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/01 20:39:02 by eduribei         ###   ########.fr       */
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

void	ft_alloc_resources(t_resources *main)
{
	t_params	*params;

	params = main->params;
	params->is_someone_dead = false;
	gettimeofday(&params->start_time, NULL);
	main->forks = calloc(params->nb_of_forks + 1, sizeof(pthread_mutex_t));
	main->th = calloc(params->number_of_philos, sizeof(pthread_t));
	main->philo = calloc(params->number_of_philos, sizeof(t_philos));
	main->stop_mutex = calloc(1, sizeof(pthread_mutex_t));
	main->print_mutex = calloc(1, sizeof(pthread_mutex_t));
	if (!main->forks || !main->th || !main->philo || !main->print_mutex)
	{
		printf("malloc error.\n");
		ft_free_resources(main);
		exit(1);
	}
	return ;
}

// FREE RESOURCES WHEN ONLY WHEN THREADS RETURN.
void	ft_free_resources(t_resources *main)
{
	if (!main)
		return ;
	if (main->th)
		free(main->th);
	if (main->forks)
	{
		//ft pthread_mutex_destroy(...)
		free(main->forks);
	}
	if (main->philo)
		free(main->philo);
	if (main->params)
		free(main->params);
	if (main->stop_mutex)
	{
		pthread_mutex_destroy(main->stop_mutex);
		free(main->stop_mutex);
	}
	if (main->print_mutex)
	{
		pthread_mutex_destroy(main->print_mutex);
		free(main->print_mutex);
	}	
	free(main);
	return ;
}

void	ft_error(char *message, t_resources *r)
{
	printf("Error: %s", message);
	ft_free_resources(r);
	exit(1);
}

size_t	ft_t_delta_ms(timeval start, timeval end)
{
	ssize_t	seconds;
	ssize_t	microseconds;

	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	if (microseconds < 0)
	{
		seconds -= 1;
		microseconds += 1000000;
	}
	return (seconds * 1000 + microseconds / 1000);
}

size_t	ft_t_delta_us(timeval start, timeval end)
{
	ssize_t	seconds;
	ssize_t	microseconds;

	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	if (microseconds < 0)
	{
		seconds -= 1;
		microseconds += 1000000;
	}
	return (seconds * 1000000 + microseconds);
}
