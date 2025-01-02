/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:36:30 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/02 12:59:35 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_grab_fork_1(t_philos *philo, t_params *params)
{
	t_timeval	now;
	size_t		timedelta;

	if (ft_thread_must_stop(params))
		return (false);
	pthread_mutex_lock(philo->fork1);
	gettimeofday(&now, NULL);
	timedelta = ft_t_delta_ms(params->start_time, now);
	if (ft_thread_must_stop(params))
	{
		pthread_mutex_unlock(philo->fork1);
		return (false);
	}
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li has taken a fork\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	return (true);
}

bool	ft_grab_fork_2(t_philos *philo, t_params *params)
{
	t_timeval	now;
	size_t		timedelta;

	if (ft_thread_must_stop(params))
	{
		pthread_mutex_unlock(philo->fork1);
		return (false);
	}
	pthread_mutex_lock(philo->fork2);
	gettimeofday(&now, NULL);
	timedelta = ft_t_delta_ms(params->start_time, now);
	if (ft_thread_must_stop(params))
	{
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (false);
	}
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li has taken a fork\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	return (true);
}

bool	ft_eating(t_philos *philo, t_params *params)
{
	t_timeval	now;
	size_t		timedelta;

	if (ft_thread_must_stop(params))
	{
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
		return (false);
	}
	gettimeofday(&now, NULL);
	timedelta = ft_t_delta_ms(params->start_time, now);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is eating\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	gettimeofday(&philo->tm_lastmeal, NULL);
	usleep(params->tm_eat);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_lock(params->meal_mutex);
	philo->nb_meals_had += 1;
	params->total_meals_ct += 1;
	pthread_mutex_unlock(params->meal_mutex);
	if (philo->nb_meals_had == params->nb_meals_to_eat)
		return (false);
	return (true);
}

bool	ft_sleeping(t_philos *philo, t_params *params)
{
	t_timeval	now;
	size_t		timedelta;

	if (ft_thread_must_stop(params))
		return (false);
	gettimeofday(&now, NULL);
	timedelta = ft_t_delta_ms(params->start_time, now);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is sleeping\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	usleep(params->tm_sleep);
	return (true);
}

bool	ft_thinking(t_philos *philo, t_params *params)
{
	t_timeval	now;
	size_t		timedelta;

	if (ft_thread_must_stop(params))
		return (false);
	gettimeofday(&now, NULL);
	timedelta = ft_t_delta_ms(params->start_time, now);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is thinking\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	if (philo->index % 2 == 0)
		usleep(100);
	else
		usleep(50);
	return (true);
}
