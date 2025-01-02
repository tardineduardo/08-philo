/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:09:51 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/01 22:01:13 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_grab_fork_1(t_philos *philo, t_params *params)
{
	size_t	timedelta;

	if (ft_stop(philo, params))
		return (false);
	pthread_mutex_lock(philo->fork1);
	pthread_mutex_lock(params->meal_mutex);
	gettimeofday(&philo->curr_time, NULL);
	timedelta = ft_t_delta_ms(params->start_time, philo->curr_time);
	pthread_mutex_unlock(params->meal_mutex);
	if (ft_stop(philo, params))
	{
		pthread_mutex_unlock(philo->fork1);
		return (false);
	}
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li has taken a fork\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	return (true);
}

bool	philo_grab_fork_2(t_philos *philo, t_params *params)
{
	size_t	timedelta;

	if (ft_stop(philo, params))
	{
		pthread_mutex_unlock(philo->fork1);
		return (false);
	}
	pthread_mutex_lock(philo->fork2);
	pthread_mutex_lock(params->meal_mutex);
	gettimeofday(&philo->curr_time, NULL);
	timedelta = ft_t_delta_ms(params->start_time, philo->curr_time);
	pthread_mutex_unlock(params->meal_mutex);
	if (ft_stop(philo, params))
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

bool	philo_eating(t_philos *philo, t_params *params)
{
	size_t	timedelta;

	if (ft_stop(philo, params))
	{
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
		return (false);
	}
	gettimeofday(&philo->curr_time, NULL);
	timedelta = ft_t_delta_ms(params->start_time, philo->curr_time);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is eating\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	pthread_mutex_lock(params->meal_mutex);
	gettimeofday(&philo->t_of_last_meal, NULL);
	pthread_mutex_unlock(params->meal_mutex);
	usleep(params->time_eating);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_lock(params->meal_mutex);
	philo->number_of_meals_had += 1;
	pthread_mutex_unlock(params->meal_mutex);
	if (philo->number_of_meals_had == params->number_of_meals_to_eat)
		return (false);
	return (true);
}

bool	philo_sleeping(t_philos *philo, t_params *params)
{
	size_t	timedelta;

	if (ft_stop(philo, params))
		return (false);
	pthread_mutex_lock(params->meal_mutex);
	gettimeofday(&philo->curr_time, NULL);
	timedelta = ft_t_delta_ms(params->start_time, philo->curr_time);
	pthread_mutex_unlock(params->meal_mutex);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is sleeping\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	usleep(params->time_sleeping);
	return (true);
}

bool	philo_thinking(t_philos *philo, t_params *params)
{
	size_t	timedelta;

	if (ft_stop(philo, params))
		return (false);
	pthread_mutex_lock(params->meal_mutex);
	gettimeofday(&philo->curr_time, NULL);
	timedelta = ft_t_delta_ms(params->start_time, philo->curr_time);
	pthread_mutex_unlock(params->meal_mutex);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is thinking\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	if (philo->index % 2 == 0)
		usleep(2000);
	else
		usleep(500);
	return (true);
}
