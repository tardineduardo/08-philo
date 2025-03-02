/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:36:30 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/03 13:19:17 by eduribei         ###   ########.fr       */
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
	ft_get_time(&now, params->time_mutex);
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

	if (!philo->fork2 || ft_thread_must_stop(params))
	{
		pthread_mutex_unlock(philo->fork1);
		return (false);
	}
	pthread_mutex_lock(philo->fork2);
	ft_get_time(&now, params->time_mutex);
	timedelta = ft_t_delta_ms(params->start_time, now);
	if (ft_thread_must_stop(params))
	{
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
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
	ft_get_time(&now, params->time_mutex);
	timedelta = ft_t_delta_ms(params->start_time, now);
	pthread_mutex_lock(params->print_mutex);
	printf(GREEN "%li %li is eating\n" RST, timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	ft_get_time(&philo->tm_lastmeal, params->time_mutex);
	usleep(params->tm_eat);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_unlock(philo->fork1);
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
	ft_get_time(&now, params->time_mutex);
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
	size_t		think_time;

	if (ft_thread_must_stop(params))
		return (false);
	ft_get_time(&now, params->time_mutex);
	timedelta = ft_t_delta_ms(params->start_time, now);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is thinking\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	think_time = (params->tm_die - philo->tm_starv) / 2;
	if (think_time > params->tm_eat)
		think_time = params->tm_eat / 2;
	if (think_time < 1000)
		think_time = 100;
	usleep(think_time);
	return (true);
}
