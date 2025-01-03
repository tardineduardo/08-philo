/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:36:30 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/02 21:35:42 by eduribei         ###   ########.fr       */
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
	
				pthread_mutex_lock(params->print_mutex);
				printf("grabfork1 about to return true\n");
				pthread_mutex_unlock(params->print_mutex);
	
	return (true);
}

bool	ft_grab_fork_2(t_philos *philo, t_params *params)
{
	t_timeval	now;
	size_t		timedelta;

				pthread_mutex_lock(params->print_mutex);
				printf("grabfork2 just started\n");
				pthread_mutex_unlock(params->print_mutex);


	if (!philo->fork2)
	{

				pthread_mutex_lock(params->print_mutex);
				printf("fork2 is null, about to return false\n");
				pthread_mutex_unlock(params->print_mutex);


		return (false);
	}

				pthread_mutex_lock(params->print_mutex);
				printf("fork2 not null!\n");
				pthread_mutex_unlock(params->print_mutex);


	if (ft_thread_must_stop(params))
	{

				pthread_mutex_lock(params->print_mutex);
				printf("XXX entered must stop!\n");
				pthread_mutex_unlock(params->print_mutex);

		pthread_mutex_unlock(philo->fork1);
		return (false);
	} 

				pthread_mutex_lock(params->print_mutex);
				printf("about to grab fork2!\n");
				pthread_mutex_unlock(params->print_mutex);


	pthread_mutex_lock(philo->fork2);


				pthread_mutex_lock(params->print_mutex);
				printf("graaaaaabed fork2!\n");
				pthread_mutex_unlock(params->print_mutex);


	ft_get_time(&now, params->time_mutex);
	timedelta = ft_t_delta_ms(params->start_time, now);
	if (ft_thread_must_stop(params))
	{

				pthread_mutex_lock(params->print_mutex);
				printf("XXX entered SECOND must stop!\n");
				pthread_mutex_unlock(params->print_mutex);


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
	ft_get_time(&now, params->time_mutex);
	timedelta = ft_t_delta_ms(params->start_time, now);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is eating\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	ft_get_time(&philo->tm_lastmeal, params->time_mutex);
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

	if (ft_thread_must_stop(params))
		return (false);
	ft_get_time(&now, params->time_mutex);
	timedelta = ft_t_delta_ms(params->start_time, now);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is thinking\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	usleep(10);	
	return (true);
}
