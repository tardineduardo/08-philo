/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:09:51 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/01 18:44:52 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_grab_fork_1(t_philos *philo, t_params *params)
{
	size_t	timedelta;

	if (ft_stop(philo, params))
		return (false);
	pthread_mutex_lock(philo->fork1);
	gettimeofday(&philo->curr_time, NULL);
	timedelta = ft_t_delta_ms(params->start_time, philo->curr_time);
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
	gettimeofday(&philo->curr_time, NULL);
	timedelta = ft_t_delta_ms(params->start_time, philo->curr_time);
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
	gettimeofday(&philo->t_of_last_meal, NULL);
	usleep(params->time_eating);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	philo->number_of_meals_had += 1;
	if (philo->number_of_meals_had == params->number_of_meals_to_eat)
		return (false);
	return (true);
}

bool	philo_sleeping(t_philos *philo, t_params *params)
{
	size_t	timedelta;

	if (ft_stop(philo, params))
		return (false);
	gettimeofday(&philo->curr_time, NULL);
	timedelta = ft_t_delta_ms(params->start_time, philo->curr_time);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is sleeping\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	gettimeofday(&philo->curr_time, NULL);
	timedelta = ft_t_delta_us(philo->t_of_last_meal, philo->curr_time);
	if (timedelta + params->time_sleeping > params->time_to_die)
	{
		pthread_mutex_lock(params->stop_mutex);
		params->is_someone_dead = true;
		pthread_mutex_unlock(params->stop_mutex);
		gettimeofday(&philo->curr_time, NULL);
		timedelta = ft_t_delta_ms(params->start_time, philo->curr_time);
		pthread_mutex_lock(params->print_mutex);
		printf("%li %li died\n", timedelta, philo->index + 1);
		pthread_mutex_unlock(params->print_mutex);
		return (true);
	}
	usleep(params->time_sleeping);
	return (true);
}

bool	philo_thinking(t_philos *philo, t_params *params)
{
	size_t	timedelta;

	if (ft_stop(philo, params))
		return (false);
	gettimeofday(&philo->curr_time, NULL);
	timedelta = ft_t_delta_ms(params->start_time, philo->curr_time);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is thinking\n", timedelta, philo->index + 1);
	pthread_mutex_unlock(params->print_mutex);
	usleep(1);
	return (true);
}
